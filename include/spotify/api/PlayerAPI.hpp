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
#include "spotify/util/JsonMapping.hpp"
#include "spotify/api/BaseAPI.hpp"

namespace Spotify {

    class PlayerAPI : public BaseAPI {
    // Funcs
    public:

        explicit PlayerAPI(Client* client) : BaseAPI(client) {};

        // GET
        [[nodiscard]] std::optional<PlaybackObject> getPlaybackState(const std::optional<std::string> &market = std::nullopt, const std::optional<std::string> &additional_types = std::nullopt) const;
        [[nodiscard]] std::optional<DeviceListObject> getAvailableDevices() const;
        [[nodiscard]] std::optional<PlaybackObject> getCurrentlyPlayingTrack(const std::optional<std::string> &market = std::nullopt, const std::optional<std::string> &additional_types = std::nullopt) const;
        [[nodiscard]] std::optional<RecentlyPlayedTracksObject> getRecentlyPlayedTracks(std::optional<int> limit = std::nullopt, std::optional<int64_t> after = std::nullopt,  std::optional<int64_t> before = std::nullopt) const;
        [[nodiscard]] std::optional<QueueObject> getUsersQueue() const;

        // POST
        void skipToNext(std::optional<std::string> device_id = std::nullopt) const;
        void skipToPrevious(std::optional<std::string> device_id = std::nullopt) const;
        void addItemToQueue(const std::string& uri, const std::optional<std::string> &device_id = std::nullopt) const;

        // PUT
        void transferPlayback(const std::vector<std::string>& device_ids, std::optional<bool> play = std::nullopt) const;
        void startPlayback(const std::optional<std::string>& device_id = std::nullopt, const std::optional<StartPlaybackProperties>& properties = std::nullopt) const;
        void pausePlayback(const std::optional<std::string> &device_id = std::nullopt) const;
        void seekToPosition(int position_ms, const std::optional<std::string> &device_id = std::nullopt) const;
        void setRepeatMode(RepeatState state, const std::optional<std::string> &device_id = std::nullopt) const;
        void setPlaybackVolume(int volume_percent, std::optional<std::string> device_id = std::nullopt) const;
        void togglePlaybackShuffle(bool state, std::optional<std::string> device_id = std::nullopt) const;


    private:
        void skipHelper(bool is_next, std::optional<std::string> device_id = std::nullopt) const;

    // Vars
    private:
        const std::string BASE_PLAYER_URL = "https://api.spotify.com/v1/me/player";



    };

}





#endif //PLAYERAPI_H
