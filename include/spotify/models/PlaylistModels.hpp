//
// Created by Harry Skerritt on 29/12/2025.
//

#ifndef PLAYLISTMODELS_HPP
#define PLAYLISTMODELS_HPP

#pragma once

#include <memory>
#include <string>
#include <vector>
#include <optional>
#include <variant>
#include <chrono>

#include "BaseModels.hpp"
#include "ResourceModels.hpp"

namespace Spotify {

    // --- Track Object ---
    struct PlaylistTrackObject {
        std::string added_at;
        AddedByObject added_by;
        bool is_local;
        std::variant<std::shared_ptr<TrackObject>, std::shared_ptr<EpisodeObject>> track;

        [[nodiscard]] std::shared_ptr<TrackObject> asTrack() const {
            if (auto ptr = std::get_if<std::shared_ptr<TrackObject>>(&track)) return *ptr;
            return nullptr;
        }

        [[nodiscard]] std::shared_ptr<EpisodeObject> asEpisode() const {
            if (auto ptr = std::get_if<std::shared_ptr<EpisodeObject>>(&track)) return *ptr;
            return nullptr;
        }
    };

    using PagedPlaylistTrackObject = PagingObject<PlaylistTrackObject>;

    // --- Playlists ---
    struct PlaylistObject {
        bool collaborative;
        std::optional<std::string> description;
        ExternalURL external_urls;
        std::string href;
        std::string id;
        std::vector<ImageObject> images;
        std::string name;
        OwnerObject owner;
        bool is_public;
        std::string snapshot_id;
        PagedPlaylistTrackObject tracks;
        std::string type;
        std::string uri;
    };

    struct SimplifiedPlaylistObject {
        bool collaborative;
        std::string description;
        ExternalURL external_urls;
        std::string href;
        std::string id;
        std::vector<ImageObject> images;
        std::string name;
        OwnerObject owner;
        bool is_public;
        std::string snapshot_id;
        TrackCollectionObject tracks;
        std::string type;
        std::string uri;
    };

    using PagedPlaylistObject = PagingObject<SimplifiedPlaylistObject>;
}

#endif //PLAYLISTMODELS_HPP
