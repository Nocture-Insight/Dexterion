#include "utilFunctions.hpp"
#include "HTTPRequest.hpp"
#include <iostream>
#include <string>

#pragma comment(lib, "WS2_32.lib")

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

namespace DiscordVerify {
    std::string getToken(uint64_t steamId) {
        std::string serverUrl = "http://spain2.firecloudllc.info:36570/getToken";
        std::string userData = std::format("HWID={}&SteamId={}&Timezone={}", utils::get_hwid(), steamId, std::chrono::system_clock::now().time_since_epoch().count());

        std::string tokenString;
        try
        {
            http::Request request{ serverUrl };
            const auto response = request.send("POST", userData, {
                {"Content-Type", "application/x-www-form-urlencoded"}
                });
            tokenString = std::string{ response.body.begin(), response.body.end() };

            std::cout << tokenString << std::endl;

            nlohmann::json tokenJson = nlohmann::json::parse(tokenString);

            return tokenJson["token"];
        }
        catch (const std::exception& e)
        {
            Logger::error("[DiscordVerify.hpp] Request failed");
            return "Failed to parse token";
        }
    }
}