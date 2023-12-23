#include <iostream>
#include <thread>
#include <chrono>
#include <curl/curl.h>

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

        // Parse the response to extract the time (this part depends on the response format)
        // ...

        return readBuffer; // This should be replaced with the parsed time
    }
    return "";
}

void updateWeatherData() {
    while (true) {
        std::string currentTime = fetchCurrentTime();
        std::cout << "Current time is: " << currentTime << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}

// Simulated function to display weather data
void displayWeatherData() {
    while (true) { // Infinite loop to keep displaying data
        // Display the latest available weather data
        std::cout << "Displaying weather data..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate the display action
    }
}

int main() {
    // Create a thread for updating weather data
    std::thread weatherUpdater(updateWeatherData);

    // Create a thread for displaying weather data
    std::thread weatherDisplayer(displayWeatherData);

    // Join threads to the main thread (in a real-world application, you might not join these threads)
    weatherUpdater.join();
    weatherDisplayer.join();

    return 0;
}

