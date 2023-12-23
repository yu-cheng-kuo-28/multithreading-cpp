#include <iostream>
#include <thread>
#include <chrono>
#include <curl/curl.h>
#include <mutex>
#include <nlohmann/json.hpp> // Make sure this library is included and set up

std::mutex dataMutex;          // Mutex for synchronizing access to sharedTimeData
std::string sharedTimeData;    // Global variable to store the shared time data

// This is a callback function used by libcurl for storing fetched data
size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *userp) {
    userp->append((char*)contents, size * nmemb);
    return size * nmemb;
}

// Function to fetch the current time from an API
std::string fetchCurrentTime() {
    CURL *curl;
    CURLcode res;
    std::string readBuffer;

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
        } catch(const std::exception& e) {
            std::cerr << "JSON parse error: " << e.what() << '\n';
            return "";
        }
    }
    return "";
}

void updateTimeData() {
    while (true) {
        std::string currentTime = fetchCurrentTime();
        {
            std::lock_guard<std::mutex> guard(dataMutex);
            sharedTimeData = currentTime;
        }
        std::this_thread::sleep_for(std::chrono::seconds(6));
    }
}

// Simulated function to display weather data
void displayTimeData() {
    while (true) {
        std::string currentTime;
        {
            std::lock_guard<std::mutex> guard(dataMutex);
            currentTime = sharedTimeData;
        }
        if (!currentTime.empty()) {
            std::cout << "Current time is: " << currentTime << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }
}

int main() {
    std::thread timeUpdater(updateTimeData);
    std::thread timeDisplayer(displayTimeData);

    timeUpdater.join();
    timeDisplayer.join();

    return 0;
}
