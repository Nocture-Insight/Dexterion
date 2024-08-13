#include "utilFunctions.hpp"
#include "cpr/cpr.h"
#include <iostream>
#include <string>

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

namespace DiscordVerify {
    bool getToken(uint64_t steamId) {
        std::string serverUrl = "http://spain2.firecloudllc.info:36570/getToken";
        std::string userData = std::format("HWID={}&SteamId={}&Timezone={}", utils::get_hwid(), steamId, std::chrono::system_clock::now().time_since_epoch());

        std::string token;
        try
        {
            CURL* curl;
            CURLcode res;

            curl = curl_easy_init();
            if (curl) {
                curl_easy_setopt(curl, CURLOPT_URL, serverUrl.c_str());
                curl_easy_setopt(curl, CURLOPT_POSTFIELDS, userData.c_str());

                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, &token);

                res = curl_easy_perform(curl);
                curl_easy_cleanup(curl);
            }

            Logger::info("[DiscordVerify.hpp] " + token); // print the result
            return true;
        }
        catch (const std::exception& e)
        {
            Logger::error("[DiscordVerify.hpp] Request failed");
            return false;
        }
    }
}