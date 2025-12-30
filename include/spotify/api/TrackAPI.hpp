//
// Created by Harry Skerritt on 22/12/2025.
//

#ifndef TRACKAPI_HPP
#define TRACKAPI_HPP

#pragma once
#include <string>
#include <optional>
#include <iostream>

#include "spotify/internal.hpp"


namespace Spotify {

    class TrackAPI : public BaseAPI {
    // Funcs
    public:

        explicit TrackAPI(Client* client) : BaseAPI(client) {};

        // GET
        /// Retrieves a Spotify track by its ID
        /// @param id Spotify track ID
        /// @param market ISO 3166-1 country code (optional)
        [[nodiscard]] TrackObject getTrack(
            const std::string &id,
            const std::optional<std::string> &market = std::nullopt
        ) const;

        /// Retrieves multiple Spotify tracks by their IDs
        /// @param ids A vector of Spotify track IDs (max 50)
        /// @param market ISO 3166-1 country code (optional)
        [[nodiscard]] TrackListObject getTracks(
            const std::vector<std::string>& ids,
            const std::optional<std::string>& market = std::nullopt
        ) const;

        /// Retrieves the current user's saved tracks
        /// @param market ISO 3166-1 country code (optional)
        /// @param limit Max number of items to return (optional)
        /// @param offset Index of first item to return (optional)
        /// @note Requires @c user-library-read scope
        [[nodiscard]] PagedSavedTrackObject getUserSavedTracks(
            const std::optional<std::string>& market = std::nullopt,
            const std::optional<int>& limit = std::nullopt,
            const std::optional<int>& offset = std::nullopt
        ) const;

        /// Checks whether the given tracks are saved in the user's library
        /// @param ids Vector of Spotify track IDs
        /// @note Requires @c user-library-read scope
        /// @return Vector of booleans, one per input ID
        [[nodiscard]] std::vector<bool> checkUsersSavedTracks(const std::vector<std::string>& ids) const;

        // PUT
        /// Saves the Spotify tracks to the user's library
        /// @param ids Vector of Spotify audiobook IDs
        /// @note Requires @c user-library-modify scope
        void saveTracksForUser(const std::vector<std::string>& ids) const;

        /// Saves the Spotify tracks to the user's library
        /// @param timestamped_ids Vector of Spotify timestamped_ids
        /// @note Requires @c user-library-modify scope
        void saveTracksForUser(const std::vector<TimestampIDObject>& timestamped_ids) const;

        // DELETE
        /// Removes the Spotify tracks from the user's library
        /// @param ids Vector of Spotify audiobook IDs
        /// @note Requires @c user-library-modify scope
        void removeUsersSavedTracks(std::vector<std::string> ids) const;

    };

}


#endif //TRACKAPI_HPP
