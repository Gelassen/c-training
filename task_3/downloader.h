#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <iostream>
#include <string>
#include <curl/curl.h>

class Downloader {
public:
    Downloader() {
    }
    
    ~Downloader() {
    }
    
    std::byte download(const std::string& url) {
        CURL* curl = curl_easy_init();
        if (!curl) {
            throw std::runtime_error("Failed to initialize curl");
        }
        
        std::string response;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        
        CURLcode res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        
        if (res != CURLE_OK) {
            throw std::runtime_error("Failed to download: " + url);
        }
        
        return static_cast<T>(response);
    }

private:
    static size_t writeCallback(void* contents, size_t size, size_t nmemb, void* userp) {
        size_t totalSize = size * nmemb;
        static_cast<std::string*>(userp)->append(static_cast<char*>(contents), totalSize);
        return totalSize;
    }
};

#endif