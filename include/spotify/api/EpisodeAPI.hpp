//
// Created by Harry Skerritt on 22/12/2025.
//

#ifndef EPISODEAPI_HPP
#define EPISODEAPI_HPP

#pragma once
#include <string>
#include <optional>
#include <iostream>

#include "spotify/internal.hpp"

namespace Spotify {

    class EpisodeAPI : public BaseAPI {
    // Funcs
    public:

        explicit EpisodeAPI(Client* client) : BaseAPI(client) {};

        // GET
        /// Retrieves a Spotify episode by its ID
        /// @param id Spotify episode ID
        /// @param market ISO 3166-1 country code (optional)
        /// @note Requires @c user-read-playback-position scope
        [[nodiscard]] EpisodeObject getEpisode(
            const std::string &id,
            const std::optional<std::string> &market = std::nullopt
        ) const;


        /// Retrieves multiple Spotify episodes by their IDs
        /// @param ids A vector of Spotify episode IDs (max 50)
        /// @param market ISO 3166-1 country code (optional)
        /// @note Requires @c user-read-playback-position scope
        [[nodiscard]] EpisodeListObject getMultipleEpisodes(
            const std::vector<std::string>& ids,
            const std::optional<std::string>& market = std::nullopt
        ) const;

        /// Retrieves the current user's saved episodes
        /// @param limit Max number of items to return (optional)
        /// @param offset Index of first item to return (optional)
        /// @param market ISO 3166-1 country code (optional)
        /// @note Requires @c user-library-read scope
        /// @note Requires @c user-read-playback-position scope
        [[nodiscard]] PagedSavedEpisodeObject getUsersSavedEpisodes(
            const std::optional<std::string>& market = std::nullopt,
            const std::optional<int>& limit = std::nullopt,
            const std::optional<int>& offset = std::nullopt
        ) const;

        /// Checks whether the given episodes are saved in the user's library
        /// @param ids Vector of Spotify episode IDs
        /// @note Requires @c user-library-read scope
        /// @return Vector of booleans, one per input ID
        [[nodiscard]] std::vector<bool> checkUsersSavedEpisodes(const std::vector<std::string>& ids) const;

        // PUT
        /// Saves the Spotify episodes to the user's library
        /// @param ids Vector of Spotify episode IDs
        /// @note Requires @c user-library-modify scope
        void saveEpisodeForUser(const std::vector<std::string>& ids) const;

        // Delete
        /// Removes the Spotify episodes from the user's library
        /// @param ids Vector of Spotify episode IDs
        /// @note Requires @c user-library-modify scope
        void removeUserSavedEpisodes(const std::vector<std::string>& ids) const;
    };
}

#endif //EPISODEAPI_HPP
