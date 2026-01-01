//
// Created by Harry Skerritt on 29/12/2025.
//

#ifndef AUTHMODELS_HPP
#define AUTHMODELS_HPP

#pragma once


#include <string>
#include <vector>
#include <optional>
#include <variant>
#include <chrono>

namespace Spotify {

    // Enum
    enum class HTTPStatus_Code {
        OK = 200,
        CREATED = 201,
        ACCEPTED = 202,
        NO_CONTENT = 204,
        NOT_MODIFIED = 304,
        BAD_REQUEST = 400,
        UNAUTHORIZED = 401,
        FORBIDDEN = 403,
        NOT_FOUND = 404,
        TOO_MANY_REQUESTS = 429,
        INTERNAL_SERVER_ERROR = 500,
        NOT_IMPLEMENTED = 501,
        BAD_GATEWAY = 502,
        SERVICE_UNAVAILABLE = 503,
        UNKNOWN_ERROR = -2,
    };

    // Auth
    struct ClientCredentials {
        std::string client_id;
        std::string client_secret;
    };

    struct AuthResponse {
        std::string access_token;
        std::string token_type;
        std::string scope;
        std::chrono::time_point<std::chrono::system_clock> expire_time;
        std::string refresh_token;
        HTTPStatus_Code response_code;
    };

}

#endif //AUTHMODELS_HPP
