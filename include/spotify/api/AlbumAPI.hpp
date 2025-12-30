//
// Created by Harry Skerritt on 21/12/2025.
//

#ifndef ALBUMAPI_H
#define ALBUMAPI_H

#pragma once
#include <string>
#include <optional>
#include <iostream>

#include "spotify/internal.hpp"

namespace Spotify {

    class AlbumAPI : public BaseAPI {
    // Funcs
    public:

        explicit AlbumAPI(Client* client) : BaseAPI(client) {};

        // GET

        /// Retrieves a Spotify album by its ID
        /// @param id Spotify album ID
        /// @param market ISO 3166-1 country code (optional)
        [[nodiscard]] AlbumObject getAlbum(
            const std::string &id,
            const std::optional<std::string>& market = std::nullopt
        ) const;

        /// Retrieves multiple Spotify albums by their IDs
        /// @param ids A vector of Spotify album IDs (max 20)
        /// @param market ISO 3166-1 country code (optional)
        [[nodiscard]] AlbumListObject getMultipleAlbums(
            const std::vector<std::string>& ids,
            const std::optional<std::string>& market = std::nullopt
        ) const;

        /// Retrieves tracks from a Spotify album by its ID
        /// @param id A Spotify album ID
        /// @param market ISO 3166-1 country code (optional)
        /// @param limit Max number of items to return (optional)
        /// @param offset Index of first item to return (optional)
        [[nodiscard]] PagedTrackObject getAlbumTracks(
            const std::string& id,
            const std::optional<std::string>& market = std::nullopt,
            const std::optional<int>& limit = std::nullopt,
            const std::optional<int>& offset = std::nullopt
        ) const;

        /// Retrieves the current user's saved albums
        /// @param limit Max number of items to return (optional)
        /// @param offset Index of first item to return (optional)
        /// @param market ISO 3166-1 country code (optional)
        /// @note Requires @c user-library-read scope
        [[nodiscard]] PagedSavedAlbumObject getUsersSavedAlbums(
            const std::optional<int>& limit = std::nullopt,
            const std::optional<int>& offset = std::nullopt,
            const std::optional<std::string>& market = std::nullopt
        ) const;

        /// Checks whether the given albums are saved in the user's library
        /// @param ids Vector of Spotify album IDs
        /// @note Requires @c user-library-read scope
        /// @return Vector of booleans, one per input ID
        [[nodiscard]] std::vector<bool> checkUsersSavedAlbums(const std::vector<std::string>& ids) const;

        /// Get a list of new album releases featured in Spotify
        /// @param limit Max number of items to return (optional)
        /// @param offset Index of first item to return (optional)
        [[nodiscard]] PagedAlbumObject getNewReleases(
            const std::optional<int>& limit = std::nullopt,
            const std::optional<int>& offset = std::nullopt
        ) const;


        // PUT
        /// Saves the Spotify albums to the user's library
        /// @param ids Vector of Spotify album IDs
        /// @note Requires @c user-library-modify scope
        void saveAlbumsForUser(const std::vector<std::string>& ids) const;

        // DELETE
        /// Removes the Spotify albums from the user's library
        /// @param ids Vector of Spotify album IDs
        /// @note Requires @c user-library-modify scope
        void removeUsersSavedAlbums(const std::vector<std::string>& ids) const;
    };

}

#endif //ALBUMAPI_H
