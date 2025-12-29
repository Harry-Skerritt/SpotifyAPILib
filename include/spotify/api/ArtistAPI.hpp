//
// Created by Harry Skerritt on 22/12/2025.
//

#ifndef ARTISTAPI_HPP
#define ARTISTAPI_HPP

#pragma once
#include <string>
#include <optional>
#include <iostream>
#include "spotify/util/Types.h"
#include "spotify/api/BaseAPI.hpp"

namespace Spotify {

    class ArtistAPI : public BaseAPI {
    // Funcs
    public:

        explicit ArtistAPI(Client* client) : BaseAPI(client) {};

        // GET
        [[nodiscard]] ArtistObject getArtist(const std::string &id) const;

        [[nodiscard]] ArtistListObject getMultipleArtists(const std::vector<std::string>& ids) const;

        [[nodiscard]] PagedAlbumObject getArtistsAlbums(
            const std::string &id,
            const std::optional<std::vector<IncludeGroups>>& include_groups = std::nullopt,
            const std::optional<std::string>& market = std::nullopt,
            const std::optional<int>& limit = std::nullopt,
            const std::optional<int>& offset = std::nullopt
        ) const;

        [[nodiscard]] TrackListObject getArtistTopTracks(
            const std::string &id,
            const std::optional<std::string>& market = std::nullopt
        ) const;

    };
}

#endif //ARTISTAPI_HPP
