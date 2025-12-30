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
        switch (RFC2616_Code response_code = static_cast<RFC2616_Code>(code)) {
            case (RFC2616_Code::OK):
                return "OK";

            case (RFC2616_Code::CREATED):
                return "Created";

            case (RFC2616_Code::ACCEPTED):
                return "Accepted";

            case (RFC2616_Code::NO_CONTENT):
                return "No Content";

            case (RFC2616_Code::NOT_MODIFIED):
                return "Not Modified";

            case (RFC2616_Code::BAD_REQUEST):
                return "Bad Request";

            case (RFC2616_Code::UNAUTHORIZED):
                return "Unauthorized";

            case (RFC2616_Code::FORBIDDEN):
                return "Forbidden";

            case (RFC2616_Code::NOT_FOUND):
                return "Not Found";

            case (RFC2616_Code::TOO_MANY_REQUESTS):
                return "Too Many Requests";

            case (RFC2616_Code::INTERNAL_SERVER_ERROR):
                return "Internal Server Error";

            case (RFC2616_Code::BAD_GATEWAY):
                return "Bad Gateway";

            case (RFC2616_Code::SERVICE_UNAVAILABLE):
                return "Service Unavailable";

            case(RFC2616_Code::NOT_IMPLEMENTED):
                return "Not Implemented";

            default:
                throw Spotify::Exception("Unrecognized HTTP Status Code: " + std::to_string(code));

        }
    }
}

#endif //WEBINTERAL_H
