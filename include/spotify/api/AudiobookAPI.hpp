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
#include "spotify/util/JsonMapping.hpp"
#include "spotify/api/BaseAPI.hpp"


namespace Spotify {

    class AudiobookAPI : public BaseAPI {
    // Funcs
    public:

        explicit AudiobookAPI(Client* client) : BaseAPI(client) {};

        // GET
        [[nodiscard]] std::optional<AudiobookObject> getAudiobook(const std::string &id, std::optional<std::string> market = std::nullopt) const;
        [[nodiscard]] std::optional<AudiobookListObject> getMultipleAudiobooks(const std::vector<std::string>& ids, std::optional<std::string> market = std::nullopt) const;
        [[nodiscard]] std::optional<PagedChapterObject> getAudiobookChapters(const std::string &id, std::optional<std::string> market = std::nullopt,
            std::optional<int> limit = std::nullopt, std::optional<int> offset = std::nullopt) const;
        [[nodiscard]] std::optional<PagedAudiobookObject> getUsersSavedAudiobooks(std::optional<int> limit = std::nullopt,std::optional<int> offset = std::nullopt) const;
        [[nodiscard]] std::optional<std::vector<bool>> checkUsersSavedAudiobooks(std::vector<std::string> ids) const;


        // PUT
        void saveAudiobookForUser(std::vector<std::string> ids) const;

        // DELETE
        void removeUsersSavedAudiobooks(std::vector<std::string> ids) const;
    };

}

#endif //AUDIOBOOKAPI_HPP
