//
// Created by Harry Skerritt on 22/12/2025.
//

#ifndef EPISODEAPI_HPP
#define EPISODEAPI_HPP

#pragma once
#include <string>
#include <optional>
#include <iostream>
#include "spotify/util/Types.h"
#include "spotify/api/BaseAPI.hpp"

namespace Spotify {

    class EpisodeAPI : public BaseAPI {
    // Funcs
    public:

        explicit EpisodeAPI(Client* client) : BaseAPI(client) {};

        // GET
        [[nodiscard]] EpisodeObject getEpisode(
            const std::string &id,
            const std::optional<std::string> &market = std::nullopt
        ) const;

        [[nodiscard]] EpisodeListObject getMultipleEpisodes(
            const std::vector<std::string>& ids,
            const std::optional<std::string>& market = std::nullopt
        ) const;

        [[nodiscard]] PagedSavedEpisodeObject getUsersSavedEpisodes(
            const std::optional<std::string>& market = std::nullopt,
            const std::optional<int>& limit = std::nullopt,
            const std::optional<int>& offset = std::nullopt
        ) const;

        [[nodiscard]] std::vector<bool> checkUsersSavedEpisodes(const std::vector<std::string>& ids) const;

        // PUT
        void saveEpisodeForUser(const std::vector<std::string>& ids) const;

        // Delete
        void removeUserSavedEpisodes(const std::vector<std::string>& ids) const;
    };
}

#endif //EPISODEAPI_HPP
