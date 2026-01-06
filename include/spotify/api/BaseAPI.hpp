//
// Created by Harry Skerritt on 22/12/2025.
//

#ifndef BASEAPI_HPP
#define BASEAPI_HPP

#pragma once
#include <optional>
#include <string>
#include <iostream>
#include <ArduinoJson.h>

#include "spotify/core/Errors.hpp"
#include "../util/web/Http.hpp"
#include "../util/common/Tools.hpp"
#include "../util/parse/JsonMapping.hpp"



namespace Spotify {
    class Client;

    class BaseAPI {
    protected:
        Client* m_client;
        explicit BaseAPI(Client* client) : m_client(client) {}



        // --- GET + Parse Helper ---
        template <typename T>
        T fetchAndParse(const std::string& url, const std::string& wrapperKey = "") const {
            auto result = fetchAndParseOptional<T>(url, wrapperKey);
            if (!result.has_value()) {
                throw Spotify::ParseException("API returned 204 No Content or empty body where data was expected.", "");
            }
            return *result;
        }

        template <typename T>
        std::optional<T> fetchAndParseOptional(const std::string& url, const std::string& wrapperKey = "") const {
            if (!m_client) throw std::runtime_error("SpotifyAPI: Attempted to fetch data without an initialized HTTP client.");

            std::string token = tryGetAccessToken();
            auto result = HTTP::get(url, token);

            if (result.code == HTTPStatus_Code::NO_CONTENT || (result.code == HTTPStatus_Code::OK && result.body.empty())) {
                return std::nullopt;
            }

            // Error Handling
            ErrorHandler::verifyResponse(result);

            // Allocate the JSON document on the Heap for large Spotify responses
            // Spotify's default limit is 20 items, so we need a decent-sized buffer.
            auto doc = std::make_unique<JsonDocument>();
            DeserializationError error = deserializeJson(*doc, result.body);

            if (error) {
                throw Spotify::ParseException("JSON Parse Error: " + std::string(error.c_str()), result.body);
            }

            try {
                T target;
                JsonVariantConst data = doc->as<JsonVariantConst>();

                // Handle Spotify's "Wrapper" pattern (e.g., search results or category lists)
                if (!wrapperKey.empty()) {
                    if (data.containsKey(wrapperKey)) {
                        from_json(data[wrapperKey], target);
                    } else {
                        throw Spotify::ParseException("Wrapper key '" + wrapperKey + "' not found.", result.body);
                    }
                } else {
                    from_json(data, target);
                }

                return target;
            } catch (const std::exception& e) {
                throw Spotify::ParseException("Mapping Error: " + std::string(e.what()), result.body);
            }
        }

        // --- PUT/DELETE/POST Helper ---
        [[nodiscard]] std::optional<std::string> sendAction(const std::string& method, const std::string& url, const std::string& body = "", const HTTP::HeaderMap& extra_headers = {}) const {
            if (!m_client) return std::nullopt;

            std::string token = tryGetAccessToken();
            HTTP::Result result = {};

            if (method == "GET") result = HTTP::get(url, token);
            else if (method == "PUT") result = HTTP::put(url, token, body, extra_headers);
            else if (method == "DELETE") result = HTTP::remove(url, token, body, extra_headers);
            else if (method == "POST") result = HTTP::post(url, token, body, extra_headers);
            else {
               throw std::invalid_argument("Unsupported HTTP method: " + method);
            }

            ErrorHandler::verifyResponse(result);

            return result.body;
        }

        [[nodiscard]] std::string tryGetAccessToken() const;



    };
}
#endif //BASEAPI_HPP