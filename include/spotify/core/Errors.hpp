//
// Created by Harry Skerritt on 28/12/2025.
//

#ifndef ERRORS_HPP
#define ERRORS_HPP

#pragma once

#include <string>
#include <stdexcept>
#include <optional>
#include <ArduinoJson.h>

#include "spotify/models/AuthModels.hpp"
#include "../util/web/Http.hpp"

// Note: Briefs are AI generated - Replace before deployment

namespace Spotify {

    struct ErrorDetails {
        int status;
        std::string message;
        std::string reason;
    };


    /// @class Exception
    /// @brief Base exception for all Spotify library errors.
    class Exception : public std::runtime_error {
    public:
        explicit Exception(const std::string &message) : std::runtime_error(message) {}
    };


    /// @class APIException
    /// @brief Thrown when the Spotify API returns a non-success status code (4xx or 5xx).
    class APIException : public Exception {
        ErrorDetails m_details;
    public:
        APIException(const ErrorDetails &details)
        : Exception("Spotify API [" + std::to_string(details.status) + "]: " + details.message),
          m_details(details) {}

        [[nodiscard]] int status() const { return m_details.status; }
        [[nodiscard]] std::string message() const { return m_details.message; }
        [[nodiscard]] std::string reason() const { return m_details.reason; }
    };

    /// @class RateLimitException
    /// @brief Specifically thrown on HTTP 429 errors. Includes cooldown timing.
    class RateLimitException : public APIException {
        int m_retry_after_seconds;
    public:
        RateLimitException(const ErrorDetails& details, int retry_after)
            : APIException(details), m_retry_after_seconds(retry_after) {}

        [[nodiscard]] int retryAfter() const { return m_retry_after_seconds; }
    };


     /// @class ParseException
     /// @brief Thrown when JSON deserialization fails or the API returns malformed data.
    class ParseException : public Exception {
        std::string m_raw_body;
    public:
        ParseException(const std::string& msg, const std::string& body)
            : Exception("Parse Error: " + msg), m_raw_body(body) {}

        [[nodiscard]] std::string getRawBody() const { return m_raw_body; }
    };


    /// @class LogicException
    /// @brief Thrown for programmer errors (e.g., bad arguments or uninitialized state).
    class LogicException : public Exception {
    public:
        using Exception::Exception;
    };


    ///@class NetworkException
    ///@brief Thrown when a low-level network failure occurs (e.g., DNS failure,
    ///    connection timeout, or port binding issues).
    class NetworkException : public Exception {
        int m_libcurl_code;
    public:

        explicit NetworkException(const std::string& msg, int curl_code = 0)
            : Exception("Network Error: " + msg), m_libcurl_code(curl_code) {}

        [[nodiscard]] int libcurlCode() const { return m_libcurl_code; }
    };

    /// @class InvalidIDException
    /// @brief Thrown when a Spotify ID is invalid or does not match the expected 22-character Base62 format.
    /// @details Inherits from std::invalid_argument.
    class InvalidIDException : public std::invalid_argument {
    public:
        explicit InvalidIDException(const std::string& msg)
            : std::invalid_argument("Invalid ID: " + msg) {}
    };


   /// @class InvalidResourceException
   /// @brief Thrown when a Spotify resource type (track, album, playlist, etc.) is invalid or unsupported.
   /// @details Inherits from std::invalid_argument.
    class InvalidResourceException : public std::invalid_argument {
    public:
        explicit InvalidResourceException(const std::string& msg)
            : std::invalid_argument("Invalid Resource: " + msg) {}
    };


    // Todo: Add more



    class ErrorHandler {
    public:
        static void verifyResponse(const HTTP::Result& result) {
            int code = static_cast<int>(result.code);

            // Success: 2xx range
            if (code >= 200 && code < 300) return;

            // If body is empty, throw a generic API exception
            if (result.body.empty()) {
                Spotify::ErrorDetails details { code, "Empty response body", "UNKNOWN_REASON" };
                throw Spotify::APIException(details);
            }

            // Use a small JsonDocument for error parsing (error messages are typically < 1KB)
            JsonDocument doc;
            DeserializationError error = deserializeJson(doc, result.body);

            if (error) {
                // If it's not valid JSON, it's likely a raw server error or HTML
                throw Spotify::ParseException("Non-JSON response: " + result.body, result.body);
            }

            // Spotify error format is usually: {"error": {"status": 401, "message": "..."}}
            if (doc.containsKey("error")) {
                JsonVariantConst error_obj = doc["error"];

                std::string msg;
                if (error_obj.is<std::string>()) {
                    msg = error_obj.as<std::string>();
                } else {
                    msg = error_obj["message"] | "Unknown API Error";
                }

                Spotify::ErrorDetails details {
                    code,
                    msg,
                    doc["reason"] | "UNKNOWN_REASON"
                };

                if (result.code == HTTPStatus_Code::TOO_MANY_REQUESTS) {
                    // Spotify usually provides a 'Retry-After' header, but for now we'll keep your 30s default
                    throw Spotify::RateLimitException(details, 30);
                }
                throw Spotify::APIException(details);
            }

            // Fallback for unexpected JSON structures
            throw Spotify::ParseException("Unexpected JSON format", result.body);
        }
    };

}

#endif //ERRORS_HPP
