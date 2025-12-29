//
// Created by Harry Skerritt on 21/12/2025.
//

#ifndef ALBUMAPI_H
#define ALBUMAPI_H

#pragma once
#include <string>
#include <optional>
#include <iostream>
#include "spotify/util/Types.h"
#include "spotify/api/BaseAPI.hpp"

namespace Spotify {

    class AlbumAPI : public BaseAPI {
    // Funcs
    public:

        explicit AlbumAPI(Client* client) : BaseAPI(client) {};

        // GET

        /// Retrieves a Spotify album by its ID.
        /// @param id Spotify album ID.
        /// @param market Optional ISO 3166-1 country code.
        /// @return Album data or @c std::nullopt if unavailable.
        [[nodiscard]] AlbumObject getAlbum(
            const std::string &id,
            const std::optional<std::string>& market = std::nullopt
        ) const;

        /// Retrieves multiple Spotify albums by their IDs.
        /// @param ids A vector of Spotify album IDs (max 20).
        /// @param market Optional ISO 3166-1 country code.
        /// @return Album list or @c std::nullopt if unavailable.
        [[nodiscard]] AlbumListObject getMultipleAlbums(
            const std::vector<std::string>& ids,
            const std::optional<std::string>& market = std::nullopt
        ) const;

        /// Retrieves tracks from a Spotify album ID.
        /// @param id A Spotify album ID.
        /// @param market Optional ISO 3166-1 country code.
        /// @param limit Max number of items to return
        /// @param offset Index of first item to return
        /// @return Page of tracks or @c std::nullopt if unavailable.
        [[nodiscard]] PagedTrackObject getAlbumTracks(
            const std::string& id,
            const std::optional<std::string>& market = std::nullopt,
            const std::optional<int>& limit = std::nullopt,
            const std::optional<int>& offset = std::nullopt
        ) const;

        [[nodiscard]] PagedSavedAlbumObject getUsersSavedAlbums(
            const std::optional<int>& limit = std::nullopt,
            const std::optional<int>& offset = std::nullopt,
            const std::optional<std::string>& market = std::nullopt
        ) const;

        [[nodiscard]] std::vector<bool> checkUsersSavedAlbums(const std::vector<std::string>& ids) const;

        [[nodiscard]] PagedAlbumObject getNewReleases(
            const std::optional<int>& limit = std::nullopt,
            const std::optional<int>& offset = std::nullopt
        ) const;


        // PUT
        void saveAlbumsForUser(const std::vector<std::string>& ids) const;

        // DELETE
        void removeUsersSavedAlbums(const std::vector<std::string>& ids) const;
    };

}

#endif //ALBUMAPI_H
