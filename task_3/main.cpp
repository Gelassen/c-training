#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <mutex>
#include <curl/curl.h>
#include <string>
#include <map>
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/beast/http.hpp>

// Mutex for thread-safety when accessing shared resources
std::mutex log_mutex;

// Function to log messages in a thread-safe way
void logMessage(const std::string& message) {
    std::lock_guard<std::mutex> guard(log_mutex);
    std::cout << message << std::endl;
}

// Write callback for libcurl to save downloaded data to a file
size_t writeCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    std::ofstream* outFile = reinterpret_cast<std::ofstream*>(userp);
    size_t totalSize = size * nmemb;
    outFile->write(reinterpret_cast<char*>(contents), totalSize);
    return totalSize;
}

class FileDownloader {
public:
    FileDownloader(const std::vector<std::pair<std::string, std::string>>& fileUrls)
        : fileUrls(fileUrls) {}

    void downloadFile(const std::string& url, const std::string& filename) {
        CURL* curl;
        CURLcode res;
        std::ofstream outFile(filename, std::ios::binary);

        curl_global_init(CURL_GLOBAL_DEFAULT);  // Initialize libcurl
        curl = curl_easy_init();

        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &outFile);
            curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);  // Follow redirects

            // Perform the download
            res = curl_easy_perform(curl);

            if (res != CURLE_OK) {
                logMessage("Error downloading " + url + ": " + curl_easy_strerror(res));
            } else {
                logMessage("Successfully downloaded " + url + " to " + filename);
            }

            // Cleanup
            curl_easy_cleanup(curl);
        } else {
            logMessage("Failed to initialize curl for " + url);
        }

        curl_global_cleanup();  // Cleanup global curl state
    }

    void downloadFilesConcurrently() {
        std::vector<std::thread> threads;

        for (const auto& file : fileUrls) {
            const std::string& url = file.first;
            const std::string& filename = file.second;

            // Create a thread to download the file
            threads.push_back(std::thread(&FileDownloader::downloadFile, this, url, filename));
        }

        // Join all threads
        for (auto& t : threads) {
            t.join();
        }
    }

private:
    std::vector<std::pair<std::string, std::string>> fileUrls;
};

int main() {
    // List of URLs and corresponding filenames
    std::vector<std::pair<std::string, std::string>> fileUrls = {
        {"https://example.com/file1.txt", "file1.txt"},
        {"https://example.com/file2.txt", "file2.txt"},
        {"https://example.com/file3.txt", "file3.txt"}
    };

    logMessage("Starting file downloads...");

    FileDownloader downloader(fileUrls);
    downloader.downloadFilesConcurrently();

    logMessage("File downloads completed.");

    return 0;
}
