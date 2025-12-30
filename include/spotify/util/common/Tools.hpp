//
// Created by Harry Skerritt on 20/12/2025.
//

#ifndef TOOLS_H
#define TOOLS_H

#pragma once

#include <string>
#include <fstream>
#include <chrono>

namespace Spotify::Tools {

    void loadEnv(const std::string& filename = ".env");

    /// @brief Checks is the input string is a valid ISO 3166 Country Code
    /// @param market A string containing a country code
    /// @return True if the code is one of the 185 accepted codes
    bool isValidMarket(const std::string& market);

    /// @brief Creates an ISO 8601 formatted timestamp
    /// Example: 2023-01-15T14:30:00Z
    std::string getISOTimestamp();

    /// @brief Formats milliseconds into a "M:SS" string.
    /// Example: 185000ms -> "3:05"
    /// @param ms Time in milliseconds
    std::string formatMs(long long ms);




}



#endif //TOOLS_H
