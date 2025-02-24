// 5_fetchTimeMultithreaded_01.cpp

/*
// # Install the library for #include <curl/curl.h>
$ sudo apt-get install libcurl4-openssl-dev
// # Install the library for #include <nlohmann/json.hpp>
$ sudo apt-get install nlohmann-json3-dev
$ g++ 5_fetchTimeMultithreaded_01.cpp -o 5_fetchTimeMultithreaded_01 -pthread -lcurl
*/

#include <iostream>
#include <thread>
#include <chrono>
#include <curl/curl.h> // Make sure this library is included and set up
#include <mutex>
#include <nlohmann/json.hpp> // Make sure this library is included and set up
#include <sstream>
#include <ctime>
using namespace std;

mutex dataMutex;          // Mutex for synchronizing access to sharedTimeData
string sharedTimeData;    // Global variable to store the shared time data

// This is a callback function used by libcurl for storing fetched data
size_t WriteCallback(void *contents, size_t size, size_t nmemb, string *userp) {
    userp->append((char*)contents, size * nmemb);
    return size * nmemb;
}

// Function to fetch the current time from an API

string fetchCurrentTime() {
    CURL *curl;
    CURLcode res;
    string readBuffer;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://worldtimeapi.org/api/timezone/Japan");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        // Parse the response to extract the time
        try {
            auto jsonResponse = nlohmann::json::parse(readBuffer);
            return jsonResponse["datetime"];
        } catch(const exception& e) {
            cerr << "JSON parse error: " << e.what() << '\n';
            return "";
        }
    }
    return "";
}

void updateTimeData() {
    while (true) {
        string currentTime = fetchCurrentTime();

        // Critical section 01
        {
            lock_guard<mutex> guard(dataMutex);
            sharedTimeData = currentTime;
        }

        this_thread::sleep_for(chrono::seconds(10));
    }
}

// Simulated function to display time data
void displayTimeData() {
    while (true) {
        string currentTime;
        
        // Critical section 02
        {
            lock_guard<mutex> guard(dataMutex);
            currentTime = sharedTimeData;
        }

        if (!currentTime.empty()) {
            cout << "Current time is: " << currentTime << endl;
        }
        this_thread::sleep_for(chrono::seconds(5));
    }
}

int main() {
    thread timeUpdater(updateTimeData);
    thread timeDisplayer(displayTimeData);

    timeUpdater.join();
    timeDisplayer.join();

    return 0;
}