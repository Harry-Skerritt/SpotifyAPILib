//
// Created by Harry Skerritt on 28/12/2025.
//

#ifndef SHOWSAPI_HPP
#define SHOWSAPI_HPP

#pragma once
#include <string>
#include <optional>
#include <iostream>
#include "spotify/models/Types.hpp"
#include "spotify/api/BaseAPI.hpp"

namespace Spotify {

    class ShowsAPI : public BaseAPI {
    // Funcs
    public:

        explicit ShowsAPI(Client* client) : BaseAPI(client) {};

        // GET
        /// Retrieves a Spotify show by its ID
        /// @param id Spotify show ID
        /// @param market ISO 3166-1 country code (optional)
        /// @note Requires @c user-read-playback-position scope
        [[nodiscard]] ShowObject getShow(
            const std::string& id,
            const std::optional<std::string>& market = std::nullopt
        ) const;

        /// Retrieves multiple Spotify shows by their IDs
        /// @param ids A vector of Spotify show IDs (max 50)
        /// @param market ISO 3166-1 country code (optional)
        [[nodiscard]] ShowListObject getShows(
            const std::vector<std::string>& ids,
            const std::optional<std::string>& market = std::nullopt
        ) const;

        /// Retrieves episodes from a Spotify show by its ID
        /// @param id A Spotify show ID
        /// @param market ISO 3166-1 country code (optional)
        /// @param limit Max number of items to return (optional)
        /// @param offset Index of first item to return (optional)
        /// @note Requires @c user-read-playback-position scope
        [[nodiscard]] PagedEpisodeObject getShowEpisodes(
            const std::string& id,
            const std::optional<std::string>& market = std::nullopt,
            const std::optional<int>& limit = std::nullopt,
            const std::optional<int>& offset = std::nullopt
        ) const;

        /// Retrieves the current user's saved shows
        /// @param limit Max number of items to return (optional)
        /// @param offset Index of first item to return (optional)
        /// @note Requires @c user-library-read scope
        [[nodiscard]] PagedSavedShowObject getUserSavedShows(
            const std::optional<int>& limit = std::nullopt,
            const std::optional<int>& offset = std::nullopt
        ) const;

        /// Checks whether the given shows are saved in the user's library
        /// @param ids Vector of Spotify show IDs
        /// @note Requires @c user-library-read scope
        /// @return Vector of booleans, one per input ID
        [[nodiscard]] std::vector<bool> checkUsersSavedShows(const std::vector<std::string>& ids) const;

        // PUT
        /// Saves the Spotify shows to the user's library
        /// @param ids Vector of Spotify show IDs
        /// @note Requires @c user-library-modify scope
        void saveShowsForUser(const std::vector<std::string>& ids) const;

        // DELETE
        /// Removes the Spotify shows from the user's library
        /// @param ids Vector of Spotify show IDs
        /// @param market ISO 3166-1 country code (optional)
        /// @note Requires @c user-library-modify scope
        void removeShowsForUser(
            const std::vector<std::string>& ids,
            const std::optional<std::string>& market = std::nullopt
        ) const;

    };

}
#endif //SHOWSAPI_HPP
