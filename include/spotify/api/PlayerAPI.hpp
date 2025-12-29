//
// Created by Harry Skerritt on 21/12/2025.
//

#ifndef PLAYERAPI_H
#define PLAYERAPI_H

#pragma once
#include <string>
#include <optional>
#include <iostream>
#include "spotify/util/Types.h"
#include "spotify/api/BaseAPI.hpp"

namespace Spotify {

    class PlayerAPI : public BaseAPI {
    // Funcs
    public:

        explicit PlayerAPI(Client* client) : BaseAPI(client) {};

        // GET
        [[nodiscard]] PlaybackObject getPlaybackState(
            const std::optional<std::string> &market = std::nullopt,
            const std::optional<std::string> &additional_types = std::nullopt
        ) const;

        [[nodiscard]] DeviceListObject getAvailableDevices() const;

        [[nodiscard]] PlaybackObject getCurrentlyPlayingTrack(
            const std::optional<std::string> &market = std::nullopt,
            const std::optional<std::string> &additional_types = std::nullopt
        ) const;

        [[nodiscard]] RecentlyPlayedTracksObject getRecentlyPlayedTracks(
            const std::optional<int>& limit = std::nullopt,
            const std::optional<int64_t>& after = std::nullopt,
            const std::optional<int64_t>& before = std::nullopt
        ) const;

        [[nodiscard]] QueueObject getUsersQueue() const;

        // POST
        void skipToNext(const std::optional<std::string>& device_id = std::nullopt) const;

        void skipToPrevious(const std::optional<std::string>& device_id = std::nullopt) const;

        void addItemToQueue(
            const std::string& uri,
            const std::optional<std::string> &device_id = std::nullopt
        ) const;

        // PUT
        void transferPlayback(
            const std::vector<std::string>& device_ids,
            const std::optional<bool>& play = std::nullopt
        ) const;

        void startPlayback(
            const std::optional<std::string>& device_id = std::nullopt,
            const std::optional<StartPlaybackProperties>& properties = std::nullopt
        ) const;

        void pausePlayback(const std::optional<std::string> &device_id = std::nullopt) const;

        void seekToPosition(
            const int& position_ms,
            const std::optional<std::string> &device_id = std::nullopt
        ) const;

        void setRepeatMode(
            const RepeatState& state,
            const std::optional<std::string> &device_id = std::nullopt
        ) const;

        void setPlaybackVolume(
            const int& volume_percent,
            const std::optional<std::string>& device_id = std::nullopt
        ) const;

        void togglePlaybackShuffle(
            const bool& state,
            const std::optional<std::string>& device_id = std::nullopt
        ) const;


    private:
        void skipHelper(
            const bool& is_next,
            const std::optional<std::string>& device_id = std::nullopt
        ) const;
    };

}





#endif //PLAYERAPI_H
