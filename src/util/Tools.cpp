//
// Created by Harry Skerritt on 20/12/2025.
//

#include "spotify/util/Tools.hpp"

#include <algorithm>

namespace Spotify {
    // --- WEB TOOLS ---
    std::string WebTools::generateRandomState(size_t length) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 255);

        std::ostringstream oss;
        for (size_t i = 0; i < length; ++i) {
            oss << std::hex << std::setw(2) << std::setfill('0') << dis(gen);
        }
        return oss.str();
    }

    std::string WebTools::urlEncode(const std::string &value) {
        std::ostringstream escaped;
        escaped.fill('0');
        escaped << std::hex;

        for (char c : value) {
            if (isalnum((unsigned char)c) || c == '-' || c == '_' || c == '.' || c == '~') {
                escaped << c;
            } else {
                escaped << '%' << std::uppercase << std::setw(2) << int((unsigned char)c) << std::nouppercase;
            }
        }

        return escaped.str();
    }

    std::string WebTools::extractValue(const std::string &json, const std::string &key) {
        std::string searchKey = "\"" + key + "\":\"";
        size_t start = json.find(searchKey);
        if (start == std::string::npos) return "";

        start += searchKey.length();
        size_t end = json.find("\"", start);
        return json.substr(start, end - start);
    }

    int WebTools::extractIntValue(const std::string &json, const std::string &key) {
        std::string searchKey = "\"" + key + "\"";
        size_t keyPos = json.find(searchKey);
        if (keyPos == std::string::npos) return 0;

        size_t colonPos = json.find(":", keyPos + searchKey.length());
        if (colonPos == std::string::npos) return 0;

        size_t start = json.find_first_of("-0123456789", colonPos);
        if (start == std::string::npos) return 0;

        size_t end = json.find_first_not_of("0123456789", start);

        std::string valStr = json.substr(start, end - start);
        try {
            return std::stoi(valStr);
        } catch (...) {
            return 0;
        }
    }

    std::string WebTools::getHttpStatusText(int code)
    {
        RFC2616_Code response_code = static_cast<RFC2616_Code>(code);

        switch (response_code) {
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

            case (RFC2616_Code::NETWORK_ERROR):
                return "Network Error";

            default:
                return "Unknown Status (" + std::to_string(code) + ")";

        }
    }

    // --- TOOLS ---
    void Tools::loadEnv(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) return;

        std::string line;
        while (std::getline(file, line)) {
            if (line.empty() || line[0] == '#') continue;
            auto pos = line.find('=');
            if (pos == std::string::npos) continue;

            std::string key = line.substr(0, pos);
            std::string value = line.substr(pos + 1);

            setenv(key.c_str(), value.c_str(), 1); // overwrite if exists
        }
    }

    std::string Tools::stringifyResponse(ResponseCode code) {
        switch(code) {
            case(SUCCESS):
                return "SUCCESS";
            case(NETWORK_ERROR):
                return "NETWORK_ERROR";
            case(AUTH_ERROR):
                return "AUTH_ERROR";
            case(PARSE_ERROR):
                return "PARSE_ERROR";
            default:
                return "UNKNOWN";
        }
    }

    bool Tools::inRange(int test_case, int low, int high) {
        return (low <= test_case && test_case <= high);
    }


    std::string Tools::toCSV(std::vector<std::string> ids, int min_qty, int max_qty) {
        int size = ids.size();
        if (size > max_qty || size <= min_qty) {
           return "size-error";
        }

        std::string csv = std::accumulate(std::next(ids.begin()), ids.end(), ids[0], [](std::string a, std::string b) {
            return std::move(a) + "," + b;
        });

        return csv;
    }

    bool Tools::isValidMarket(std::string market) {
        if (market.length() != 2) return false;

        std::string upper = market;
        std::ranges::transform(upper, upper.begin(), ::toupper);
        return std::ranges::binary_search(valid_markets, upper);
    }
}

