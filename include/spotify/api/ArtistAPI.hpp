//
// Created by Harry Skerritt on 22/12/2025.
//

#ifndef ARTISTAPI_HPP
#define ARTISTAPI_HPP

#pragma once
#include <string>
#include <optional>
#include <iostream>

#include "spotify/internal.hpp"

namespace Spotify {

    class ArtistAPI : public BaseAPI {
    // Funcs
    public:

        explicit ArtistAPI(Client* client) : BaseAPI(client) {};

        // GET
        /// Retrieves a Spotify artist by their ID
        /// @param id Spotify artist ID
        [[nodiscard]] ArtistObject getArtist(const std::string &id) const;

        /// Retrieves multiple Spotify artists by their IDs
        /// @param ids A vector of Spotify artist IDs (max 50).
        [[nodiscard]] ArtistListObject getMultipleArtists(const std::vector<std::string>& ids) const;

        /// Retrieves Spotify albums by a Spotify artist from their ID
        /// @param id A Spotify artist IDs
        /// @param market ISO 3166-1 country code (optional)
        /// @param limit Max number of items to return (optional)
        /// @param offset Index of first item to return (optional)
        [[nodiscard]] PagedAlbumObject getArtistsAlbums(
            const std::string &id,
            const std::optional<std::vector<IncludeGroups>>& include_groups = std::nullopt,
            const std::optional<std::string>& market = std::nullopt,
            const std::optional<int>& limit = std::nullopt,
            const std::optional<int>& offset = std::nullopt
        ) const;


        /// Retrieves the top tracks by a Spotify artist from their ID
        /// @param id A Spotify artist IDs
        /// @param market ISO 3166-1 country code (optional)
        [[nodiscard]] TrackListObject getArtistTopTracks(
            const std::string &id,
            const std::optional<std::string>& market = std::nullopt
        ) const;

    };
}

#endif //ARTISTAPI_HPP
