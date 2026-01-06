//
// Created by Harry Skerritt on 21/12/2025.
//

#include <iostream>

#include <Arduino.h>
#include <WiFi.h>               // Basic WiFi functionality
#include <HTTPClient.h>         // Simplifies the HTTP requests (curl replacement)
#include <WiFiClientSecure.h>   // Handles SSL/TLS (Required for Spotify)

#include "../../include/spotify/util/web/Http.hpp"
#include "../../include/spotify/util/web/base64.hpp"
#include "spotify/core/Errors.hpp"


namespace Spotify {
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
        ((std::string*)userp)->append((char*)contents, size * nmemb);
        return size * nmemb;
    }

    static void applyHeaders(HTTPClient &http, const std::string& bearer, const HTTP::HeaderMap &extra, bool is_auth) {
        if (!is_auth && !bearer.empty()) {
            http.addHeader("Authorization", ("Bearer " + bearer).c_str());
        }

        // Spotify User-Agent
        http.addHeader("User-Agent", "spotify-cpp-esp-client");

        for (const auto& [key, calue] : extra) {
            http.addHeader(key.c_str(), calue.c_str());
        }
    }

    // For API
    HTTP::Result HTTP::get(const std::string &url, const std::string &bearer, const HeaderMap &extra_headers) {
        WiFiClientSecure client;
        client.setInsecure();

        HTTPClient http;
        HTTP:Result result { Spotify::HTTPStatus_Code::NOT_IMPLEMENTED, "" };

        if (http.begin(client, url.c_str())) {
            applyHeaders(http, bearer, extra_headers, false);

            int httpCode = http.GET();
            if (httpCode > 0) {
                result.code = static_cast<Spotify::HTTPStatus_Code>(httpCode);
                result.body = http.getString().c_str();
            } else {
                throw Spotify::NetworkException(http.errorToString(httpCode).c_str());
            }
            http.end();
        }
        return result;
    }

    HTTP::Result HTTP::post(const std::string &url, const std::string &bearer, const std::string &body, const HeaderMap &extra_headers, bool is_auth) {
        WiFiClientSecure client;
        client.setInsecure();
        HTTPClient http;
        HTTP::Result result { Spotify::HTTPStatus_Code::NOT_IMPLEMENTED, "" };

        if (http.begin(client, url.c_str())) {
            applyHeaders(http, bearer, extra_headers, is_auth);

            if (!body.empty() && extra_headers.find("Content-Type") == extra_headers.end()) {
                http.addHeader("Content-Type", "application/json");
            }

            int httpCode = http.POST(body.c_str());
            if (httpCode > 0) {
                result.code = static_cast<Spotify::HTTPStatus_Code>(httpCode);
                result.body = http.getString().c_str();
            } else {
                throw Spotify::NetworkException(http.errorToString(httpCode).c_str());
            }
            http.end();
        }
        return result;
    }

    HTTP::Result HTTP::put(const std::string &url, const std::string &bearer, const std::string &body, const HeaderMap &extra_headers) {
        WiFiClientSecure client;
        client.setInsecure();
        HTTPClient http;
        HTTP::Result result { Spotify::HTTPStatus_Code::NOT_IMPLEMENTED, "" };

        if (http.begin(client, url.c_str())) {
            applyHeaders(http, bearer, extra_headers, false);

            // Use sendRequest for PUT
            int httpCode = http.sendRequest("PUT", (uint8_t*)body.c_str(), body.length());

            if (httpCode > 0) {
                result.code = static_cast<Spotify::HTTPStatus_Code>(httpCode);
                result.body = http.getString().c_str();
            }
            http.end();
        }
        return result;
    }

    HTTP::Result HTTP::remove(const std::string &url, const std::string &bearer, const std::string &body, const HeaderMap &extra_headers) {
        WiFiClientSecure client;
        client.setInsecure();
        HTTPClient http;
        HTTP::Result result { Spotify::HTTPStatus_Code::NOT_IMPLEMENTED, "" };

        if (http.begin(client, url.c_str())) {
            applyHeaders(http, bearer, extra_headers, false);

            int httpCode = http.sendRequest("DELETE", (uint8_t*)body.c_str(), body.length());

            if (httpCode > 0) {
                result.code = static_cast<Spotify::HTTPStatus_Code>(httpCode);
                result.body = http.getString().c_str();
            }
            http.end();
        }
        return result;
    }

    // Other
    HTTP::Result HTTP::getImage(const std::string &url) {
        WiFiClientSecure client;
        client.setInsecure();

        HTTPClient http;
        HTTP::Result result { Spotify::HTTPStatus_Code::NOT_IMPLEMENTED, "" };

        http.setTimeout(10000);

        if (http.begin(client, url.c_str())) {
            http.addHeader("User-Agent", "spotify-cpp-esp-client");

            int httpCode = http.GET();

            if (httpCode > 0) {
                result.code = static_cast<Spotify::HTTPStatus_Code>(httpCode);
                result.body = http.getString().c_str();
            } else {
                throw Spotify::NetworkException(http.errorToString(httpCode).c_str());
            }
            http.end();
        }
        return result;
    }

}
