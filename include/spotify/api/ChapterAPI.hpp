//
// Created by Harry Skerritt on 22/12/2025.
//

#ifndef CHAPTERAPI_HPP
#define CHAPTERAPI_HPP

#pragma once
#include <string>
#include <optional>
#include <iostream>
#include "spotify/util/Types.h"
#include "spotify/api/BaseAPI.hpp"

namespace Spotify {

    class ChapterAPI : public BaseAPI {
    // Funcs
    public:
        explicit ChapterAPI(Client* client) : BaseAPI(client) {}

        // GET
        [[nodiscard]] ChapterObject getChapter(
            const std::string& id,
            const std::optional<std::string>& market = std::nullopt
        ) const;

        [[nodiscard]] ChapterListObject getMultipleChapters(
            const std::vector<std::string>& ids,
            const std::optional<std::string>& market = std::nullopt
        ) const;
    };
}

#endif //CHAPTERAPI_HPP
