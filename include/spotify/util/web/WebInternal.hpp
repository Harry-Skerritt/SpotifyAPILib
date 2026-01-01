//
// Created by Harry Skerritt on 30/12/2025.
//

#ifndef WEBINTERAL_H
#define WEBINTERAL_H

#include <string>
#include <random>
#include <sstream>
#include <iomanip>

#include "spotify/models/Types.hpp"
#include "spotify/core/Errors.hpp"

namespace Spotify::detail {

    // --- WEB TOOLS ---
    inline std::string generateRandomState(const size_t length = 16) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 255);

        std::ostringstream oss;
        for (size_t i = 0; i < length; ++i) {
            oss << std::hex << std::setw(2) << std::setfill('0') << dis(gen);
        }
        return oss.str();
    }

    inline std::string urlEncode(const std::string &value) {
        std::ostringstream escaped;
        escaped.fill('0');
        escaped << std::hex;

        for (char c : value) {
            if (isalnum(static_cast<unsigned char>(c)) || c == '-' || c == '_' || c == '.' || c == '~') {
                escaped << c;
            } else {
                escaped << '%' << std::uppercase << std::setw(2) << static_cast<int>(static_cast<unsigned char>(c)) << std::nouppercase;
            }
        }

        return escaped.str();
    }


    inline std::string getHttpStatusText(int code)
    {
        switch (auto response_code = static_cast<HTTPStatus_Code>(code)) {
            case (HTTPStatus_Code::OK):
                return "OK";

            case (HTTPStatus_Code::CREATED):
                return "Created";

            case (HTTPStatus_Code::ACCEPTED):
                return "Accepted";

            case (HTTPStatus_Code::NO_CONTENT):
                return "No Content";

            case (HTTPStatus_Code::NOT_MODIFIED):
                return "Not Modified";

            case (HTTPStatus_Code::BAD_REQUEST):
                return "Bad Request";

            case (HTTPStatus_Code::UNAUTHORIZED):
                return "Unauthorized";

            case (HTTPStatus_Code::FORBIDDEN):
                return "Forbidden";

            case (HTTPStatus_Code::NOT_FOUND):
                return "Not Found";

            case (HTTPStatus_Code::TOO_MANY_REQUESTS):
                return "Too Many Requests";

            case (HTTPStatus_Code::INTERNAL_SERVER_ERROR):
                return "Internal Server Error";

            case (HTTPStatus_Code::BAD_GATEWAY):
                return "Bad Gateway";

            case (HTTPStatus_Code::SERVICE_UNAVAILABLE):
                return "Service Unavailable";

            case(HTTPStatus_Code::NOT_IMPLEMENTED):
                return "Not Implemented";

            default:
                throw Spotify::Exception("Unrecognized HTTP Status Code: " + std::to_string(code));

        }
    }
}

#endif //WEBINTERAL_H
