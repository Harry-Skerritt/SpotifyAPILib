//
// Created by Harry Skerritt on 22/12/2025.
//

#ifndef AUDIOBOOKAPI_HPP
#define AUDIOBOOKAPI_HPP

#pragma once
#include <string>
#include <optional>
#include <iostream>
#include "spotify/util/Types.h"
#include "spotify/api/BaseAPI.hpp"


namespace Spotify {

    class AudiobookAPI : public BaseAPI {
    // Funcs
    public:

        explicit AudiobookAPI(Client* client) : BaseAPI(client) {};

        // GET
        [[nodiscard]] AudiobookObject getAudiobook(
            const std::string &id,
            const std::optional<std::string>& market = std::nullopt
        ) const;

        [[nodiscard]] AudiobookListObject getMultipleAudiobooks(
            const std::vector<std::string>& ids,
            const std::optional<std::string>& market = std::nullopt
        ) const;

        [[nodiscard]] PagedChapterObject getAudiobookChapters(
            const std::string &id,
            const std::optional<std::string>& market = std::nullopt,
            const std::optional<int>& limit = std::nullopt,
            const std::optional<int>& offset = std::nullopt
        ) const;

        [[nodiscard]] PagedAudiobookObject getUsersSavedAudiobooks(
            const std::optional<int>& limit = std::nullopt,
            const std::optional<int>& offset = std::nullopt
        ) const;

        [[nodiscard]] std::vector<bool> checkUsersSavedAudiobooks(const std::vector<std::string>& ids) const;


        // PUT
        void saveAudiobookForUser(const std::vector<std::string>& ids) const;

        // DELETE
        void removeUsersSavedAudiobooks(const std::vector<std::string>& ids) const;
    };

}

#endif //AUDIOBOOKAPI_HPP
