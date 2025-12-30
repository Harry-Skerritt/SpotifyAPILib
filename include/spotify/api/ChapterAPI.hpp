//
// Created by Harry Skerritt on 22/12/2025.
//

#ifndef CHAPTERAPI_HPP
#define CHAPTERAPI_HPP

#pragma once
#include <string>
#include <optional>
#include <iostream>
#include "spotify/models/Types.hpp"
#include "spotify/api/BaseAPI.hpp"

namespace Spotify {

    class ChapterAPI : public BaseAPI {
    // Funcs
    public:
        explicit ChapterAPI(Client* client) : BaseAPI(client) {}

        // GET
        /// Retrieves a Spotify chapter by its ID
        /// @param id Spotify chapter ID
        /// @param market ISO 3166-1 country code (optional)
        [[nodiscard]] ChapterObject getChapter(
            const std::string& id,
            const std::optional<std::string>& market = std::nullopt
        ) const;

        /// Retrieves multiple Spotify chapters by their IDs
        /// @param ids A vector of Spotify chapter IDs (max 50)
        /// @param market ISO 3166-1 country code (optional)
        [[nodiscard]] ChapterListObject getMultipleChapters(
            const std::vector<std::string>& ids,
            const std::optional<std::string>& market = std::nullopt
        ) const;
    };
}

#endif //CHAPTERAPI_HPP
