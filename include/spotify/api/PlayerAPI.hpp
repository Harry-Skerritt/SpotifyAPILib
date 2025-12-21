//
// Created by Harry Skerritt on 21/12/2025.
//

#ifndef PLAYERAPI_H
#define PLAYERAPI_H

#pragma once
#include <string>
#include <optional>
#include "spotify/util/Types.h"
#include "spotify/util/JsonMapping.hpp"

namespace Spotify {

    class Client;

    class PlayerAPI {
    // Funcs
    public:

        explicit PlayerAPI(Client* client);

        // GET
        [[nodiscard]] std::optional<PlaybackObject> getPlaybackState() const;
        [[nodiscard]] std::optional<DeviceListObject> getAvailableDevices() const;
        [[nodiscard]] std::optional<PlaybackObject> getCurrentlyPlayingTrack() const;
        [[nodiscard]] std::optional<RecentlyPlayedTracksObject> getRecentlyPlayedTracks() const;
        [[nodiscard]] std::optional<QueueObject> getUsersQueue() const;

        // POST
        void skipToNext(std::optional<std::string> device_id = std::nullopt) const;
        void skipToPrevious(std::optional<std::string> device_id = std::nullopt) const;
        void addItemToQueue(std::string uri, std::optional<std::string> device_id = std::nullopt);

        // PUT
        void transferPlayback(std::vector<std::string> device_ids, std::optional<bool> play = std::nullopt);
        void startPlayback(std::optional<std::string> device_id = std::nullopt, std::optional<StartPlaybackProperties> properties = std::nullopt);
        void pausePlayback(std::optional<std::string> device_id = std::nullopt);
        void seekToPosition(int position_ms, std::optional<std::string> device_id = std::nullopt);
        void setRepeatMode(RepeatState state, std::optional<std::string> device_id = std::nullopt);
        void setPlaybackVolume(int volume_percent, std::optional<std::string> device_id = std::nullopt);
        void togglePlaybackShuffle(bool state, std::optional<std::string> device_id = std::nullopt);








    private:
        [[nodiscard]] std::string tryGetAccessToken() const;

        void skipHelper(bool is_next, std::optional<std::string> device_id = std::nullopt) const;

    // Vars
    public:
    private:
        Client* m_client;

        const std::string BASE_PLAYER_URL = "https://api.spotify.com/v1/me/player";



    };

}





#endif //PLAYERAPI_H
