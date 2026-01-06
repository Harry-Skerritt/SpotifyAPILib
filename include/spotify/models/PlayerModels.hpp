//
// Created by Harry Skerritt on 29/12/2025.
//

#ifndef PLAYERMODELS_HPP
#define PLAYERMODELS_HPP

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

    // Enum
    enum class RepeatState {
        Track,
        Context,
        Off
    };

    // 'Core'
    struct DeviceObject {
        std::optional<std::string> id;
        bool is_active;
        bool is_private_session;
        bool is_restricted;
        std::string name;
        std::string type;
        std::optional<int> volume_percent;
        bool supports_volume;
    };

    struct DeviceListObject {
        std::vector<DeviceObject> devices;
    };

    struct ActionsObject {
        bool interrupting_playback;
        bool pausing;
        bool resuming;
        bool seeking;
        bool skipping_next;
        bool skipping_prev;
        bool toggling_repeat_context;
        bool toggling_shuffle;
        bool toggling_repeat_track;
        bool transferring_playback;
    };

    struct OffsetObject {
        std::string position;
    };

    // Playback
    struct PlaybackObject {
        DeviceObject device;
        RepeatState repeat_state;
        bool shuffle_state;
        ContextObject context;
        long long timestamp;
        int progress_ms;
        bool is_playing;
        std::variant<std::shared_ptr<TrackObject>, std::shared_ptr<EpisodeObject>> item;
        std::string currently_playing_type;
        ActionsObject actions;

        // --- Type Accessors ---
        [[nodiscard]] std::shared_ptr<TrackObject> asTrack() const {
            if (auto ptr = std::get_if<std::shared_ptr<TrackObject>>(&item)) {
                return *ptr;
            }
            return nullptr;
        }

        [[nodiscard]] std::shared_ptr<EpisodeObject> asEpisode() const {
            if (auto ptr = std::get_if<std::shared_ptr<EpisodeObject>>(&item)) {
                return *ptr;
            }
            return nullptr;
        }

    };


    struct QueueObject {
        struct PlayableItem {
            std::variant<std::shared_ptr<TrackObject>, std::shared_ptr<EpisodeObject>> data;

            [[nodiscard]] std::shared_ptr<TrackObject> asTrack() const {
                if (auto ptr = std::get_if<std::shared_ptr<TrackObject>>(&data)) return *ptr;
                return nullptr;
            }

            [[nodiscard]] std::shared_ptr<EpisodeObject> asEpisode() const {
                if (auto ptr = std::get_if<std::shared_ptr<EpisodeObject>>(&data)) return *ptr;
                return nullptr;
            }

            [[nodiscard]] std::string name() const {
                if (auto t = asTrack()) return t->name;
                if (auto e = asEpisode()) return e->name;
                return "";
            }
        };

        PlayableItem currently_playing;
        std::vector<PlayableItem> queue;

        [[nodiscard]] std::shared_ptr<TrackObject> asTrack() const { return currently_playing.asTrack(); }
        [[nodiscard]] std::shared_ptr<EpisodeObject> asEpisode() const { return currently_playing.asEpisode(); }
    };

    struct StartPlaybackProperties {
        std::optional<std::string> context_uri;
        std::optional<std::vector<std::string>> uris;
        std::optional<OffsetObject> offset;
        int position_ms;
    };

    using RecentlyPlayedTracksObject = PagingObject<PlayHistoryObject>;

}

#endif //PLAYERMODELS_HPP
