//
// Created by Harry Skerritt on 30/12/2025.
//

#ifndef INTERNALHELPERS_H
#define INTERNALHELPERS_H

#include <random>
#include <utility>
#include <string>

#include "spotify/core/Errors.hpp"

namespace Spotify::detail {

  inline bool inRange(
        int test_case,
        int low,
        int high)
    {
        return (low <= test_case && test_case <= high);
    }


    inline std::string toCSV(
        std::vector<std::string> ids,
        int min_qty,
        int max_qty)
    {
        int size = ids.size();
        if (size > max_qty || size <= min_qty) {
            throw Spotify::LogicException("CSV generation failed: size " + std::to_string(size) +
                                      " is outside allowed range [" + std::to_string(min_qty) +
                                      "..." + std::to_string(max_qty) + "]");
        }

        std::string csv = std::accumulate(std::next(ids.begin()), ids.end(), ids[0], [](std::string a, std::string b) {
            return std::move(a) + "," + b;
        });

        return csv;
    }

}

#endif //INTERNALHELPERS_H
