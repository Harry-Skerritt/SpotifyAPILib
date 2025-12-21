//
// Created by Harry Skerritt on 21/12/2025.
//

#include <utility>

#include "spotify/api/PlayerAPI.hpp"

#include "nlohmann/json.hpp"
#include "spotify/core/Client.hpp"
#include "spotify/util/Http.hpp"

namespace Spotify {
    PlayerAPI::PlayerAPI(Client *client) : m_client(client) { }

    // --- GET ---
    std::optional<PlaybackObject> PlayerAPI::getPlaybackState() const {
        if (!m_client) return std::nullopt;

        std::string token = tryGetAccessToken();
        auto result = HTTP::get((BASE_PLAYER_URL), token);


        if (result.code == RFC2616_Code::NO_CONTENT && result.code != RFC2616_Code::OK) {
            std::cerr << WebTools::getHttpStatusText((int)result.code)<< std::endl;
            return std::nullopt;
        }

        // Successfully received a body
        if (result.body.empty()) {
            std::cerr << "CRITICAL: No body received from request!" << std::endl;
            return std::nullopt;
        }


        try {
            auto data = nlohmann::json::parse(result.body);
            return data.get<PlaybackObject>();

        } catch (const nlohmann::json::exception& e) {
            std::cerr << "JSON Mapping failed: " << e.what() << std::endl;
            return std::nullopt;
        }
    }

    std::optional<DeviceListObject> PlayerAPI::getAvailableDevices() const {
        if (!m_client) return std::nullopt;

        std::string token = tryGetAccessToken();
        auto result = HTTP::get((BASE_PLAYER_URL + "/devices"), token);


        if (result.code == RFC2616_Code::NO_CONTENT && result.code != RFC2616_Code::OK) {
            std::cerr << WebTools::getHttpStatusText((int)result.code)<< std::endl;
            return std::nullopt;
        }

        // Successfully received a body
        if (result.body.empty()) {
            std::cerr << "CRITICAL: No body received from request!" << std::endl;
            return std::nullopt;
        }

        try {
            auto data = nlohmann::json::parse(result.body);
            return data.get<Spotify::DeviceListObject>();

        } catch (const nlohmann::json::exception& e) {
            std::cerr << "JSON Mapping failed: " << e.what() << std::endl;
            return std::nullopt;
        }
    }

    std::optional<PlaybackObject> PlayerAPI::getCurrentlyPlayingTrack() const {
        if (!m_client) return std::nullopt;

        std::string token = tryGetAccessToken();
        auto result = HTTP::get((BASE_PLAYER_URL + "/currently-playing"), token);

        if (result.code == RFC2616_Code::NO_CONTENT && result.code != RFC2616_Code::OK) {
            std::cerr << WebTools::getHttpStatusText((int)result.code)<< std::endl;
            return std::nullopt;
        }

        // Successfully received a body
        if (result.body.empty()) {
            std::cerr << "CRITICAL: No body received from request!" << std::endl;
            return std::nullopt;
        }

        try {
            auto data = nlohmann::json::parse(result.body);
            return data.get<Spotify::PlaybackObject>();

        } catch (const nlohmann::json::exception& e) {
            std::cerr << "JSON Mapping failed: " << e.what() << std::endl;
            return std::nullopt;
        }
    }

    std::optional<RecentlyPlayedTracksObject> PlayerAPI::getRecentlyPlayedTracks() const {
        if (!m_client) return std::nullopt;

        std::string token = tryGetAccessToken();
        auto result = HTTP::get((BASE_PLAYER_URL + "/currently-playing"), token);

        if (result.code == RFC2616_Code::NO_CONTENT && result.code != RFC2616_Code::OK) {
            std::cerr << WebTools::getHttpStatusText((int)result.code)<< std::endl;
            return std::nullopt;
        }

        // Successfully received a body
        if (result.body.empty()) {
            std::cerr << "CRITICAL: No body received from request!" << std::endl;
            return std::nullopt;
        }

        try {
            auto data = nlohmann::json::parse(result.body);
            return data.get<Spotify::RecentlyPlayedTracksObject>();

        } catch (const nlohmann::json::exception& e) {
            std::cerr << "JSON Mapping failed: " << e.what() << std::endl;
            return std::nullopt;
        }
    }

    std::optional<QueueObject> PlayerAPI::getUsersQueue() const {
        if (!m_client) return std::nullopt;

        std::string token = tryGetAccessToken();
        auto result = HTTP::get((BASE_PLAYER_URL + "/currently-playing"), token);

        if (result.code == RFC2616_Code::NO_CONTENT && result.code != RFC2616_Code::OK) {
            std::cerr << WebTools::getHttpStatusText((int)result.code)<< std::endl;
            return std::nullopt;
        }

        // Successfully received a body
        if (result.body.empty()) {
            std::cerr << "CRITICAL: No body received from request!" << std::endl;
            return std::nullopt;
        }

        try {
            auto data = nlohmann::json::parse(result.body);
            return data.get<Spotify::QueueObject>();

        } catch (const nlohmann::json::exception& e) {
            std::cerr << "JSON Mapping failed: " << e.what() << std::endl;
            return std::nullopt;
        }
    }

    // --- POST ---
    void PlayerAPI::skipToNext(std::optional<std::string> device_id) const {
        skipHelper(true, std::move(device_id));
    }

    void PlayerAPI::skipToPrevious(std::optional<std::string> device_id) const {
        skipHelper(false, std::move(device_id));
    }

    void PlayerAPI::addItemToQueue(const std::string& uri, const std::optional<std::string> &device_id) const {
        if (!m_client) return;

        std::string token = tryGetAccessToken();

        std::string url = BASE_PLAYER_URL + "/queue?uri=" + WebTools::urlEncode(uri);

        if (device_id.has_value() && !device_id->empty()) {
            url += "&device_id=" + *device_id;
        }

        auto result = HTTP::post(url, token, "");

        if (result.code != RFC2616_Code::OK) {
            std::cerr << "Failed to add to queue: " << WebTools::getHttpStatusText((int)result.code) << std::endl;
        }
    }

    // --- PUT ---
    void PlayerAPI::transferPlayback(const std::vector<std::string>& device_ids, std::optional<bool> play) const {
        if (!m_client) return;

        if (device_ids.size() != 1) {
            std::cerr << "device_ids must have size of 1. Current size: " << device_ids.size() << std::endl;
            return;
        }

        std::string token = tryGetAccessToken();

        nlohmann::json j;
        j["device_ids"] = device_ids;

        if (play.has_value()) {
            j["play"] = *play;
        }

        std::string body = j.dump();

        auto result = HTTP::put(BASE_PLAYER_URL, token , body);

        if (result.code != RFC2616_Code::NO_CONTENT && result.code != RFC2616_Code::OK) {
            std::cerr << "Transfer Playback failed: " << (int)result.code << " - " << result.body << std::endl;
        }
    }

    void PlayerAPI::startPlayback(const std::optional<std::string>& device_id, const std::optional<StartPlaybackProperties>& properties) {
        if (!m_client) return;

        std::string token = tryGetAccessToken();

        std::string url = BASE_PLAYER_URL + "/play";

        if (device_id.has_value() && !device_id->empty()) {
            url += "?device_id=" + *device_id;
        }

        std::string body = "";
        if (properties.has_value()) {
            const auto& props = *properties;
            nlohmann::json j = nlohmann::json::object();

            if (props.context_uri) {
                j["context_uri"] = *props.context_uri;
            }

            if (props.uris) {
                j["uris"] = *props.uris;
            }

            if (props.offset) {
                try {
                    j["offset"]["position"] = std::stoi(props.offset->position);
                } catch (...) {
                    j["offset"]["position"] = props.offset->position;
                }
            }

            j["position_ms"] = props.position_ms;

            body = j.dump();
        }


        auto result = HTTP::put(url, token , body);

        if (result.code != RFC2616_Code::NO_CONTENT && result.code != RFC2616_Code::OK) {
            std::cerr << "Start Playback failed: " << (int)result.code << " - " << result.body << std::endl;
        }
    }

    void PlayerAPI::pausePlayback(const std::optional<std::string> &device_id) const {
        if (!m_client) return;

        std::string token = tryGetAccessToken();

        std::string url = BASE_PLAYER_URL + "/pause";

        if (device_id.has_value() && !device_id->empty()) {
            url += "?device_id=" + *device_id;
        }

        auto result = HTTP::put(url, token , "");

        if (result.code != RFC2616_Code::NO_CONTENT && result.code != RFC2616_Code::OK) {
            std::cerr << "Failed to pause playback: " << WebTools::getHttpStatusText((int)result.code) << std::endl;
        }
    }

    void PlayerAPI::seekToPosition(int position_ms, const std::optional<std::string> &device_id) const {
        if (!m_client) return;

        std::string token = tryGetAccessToken();

        std::string url = BASE_PLAYER_URL + "/seek?position_ms=" + WebTools::urlEncode(std::to_string(position_ms));

        if (device_id.has_value() && !device_id->empty()) {
            url += "?device_id=" + *device_id;
        }

        auto result = HTTP::put(url, token , "");

        if (result.code != RFC2616_Code::NO_CONTENT && result.code != RFC2616_Code::OK) {
            std::cerr << "Failed to seek position: " << WebTools::getHttpStatusText((int)result.code) << std::endl;
        }
    }

    void PlayerAPI::setRepeatMode(RepeatState state, const std::optional<std::string> &device_id) const {
        if (!m_client) return;

        std::string repeat_state;
        switch (state) {
            case(Context):
                repeat_state = "context";

            case (Track):
                repeat_state = "track";

            case (Off):
                repeat_state = "off";
        }


        std::string token = tryGetAccessToken();

        std::string url = BASE_PLAYER_URL + "/repeat?state=" + WebTools::urlEncode(repeat_state);

        if (device_id.has_value() && !device_id->empty()) {
            url += "?device_id=" + *device_id;
        }

        auto result = HTTP::put(url, token , "");

        if (result.code != RFC2616_Code::NO_CONTENT && result.code != RFC2616_Code::OK) {
            std::cerr << "Failed to set repeat state: " << WebTools::getHttpStatusText((int)result.code) << std::endl;
        }
    }

    void PlayerAPI::setPlaybackVolume(int volume_percent, std::optional<std::string> device_id) const {
        if (!m_client) return;

        std::string token = tryGetAccessToken();

        std::string url = BASE_PLAYER_URL + "/volume?volume_percent=" + WebTools::urlEncode(std::to_string(volume_percent));

        if (device_id.has_value() && !device_id->empty()) {
            url += "?device_id=" + *device_id;
        }

        auto result = HTTP::put(url, token , "");

        if (result.code != RFC2616_Code::NO_CONTENT && result.code != RFC2616_Code::OK) {
            std::cerr << "Failed to set volume: " << WebTools::getHttpStatusText((int)result.code) << std::endl;
        }
    }

    void PlayerAPI::togglePlaybackShuffle(bool state, std::optional<std::string> device_id) const {
        if (!m_client) return;

        std::string token = tryGetAccessToken();

        std::string url = BASE_PLAYER_URL + "/shuffle?state=" + (state ? "true" : "false");;

        if (device_id.has_value() && !device_id->empty()) {
            url += "?device_id=" + *device_id;
        }

        auto result = HTTP::put(url, token , "");

        if (result.code != RFC2616_Code::NO_CONTENT && result.code != RFC2616_Code::OK) {
            std::cerr << "Failed to set shuffle state: " << WebTools::getHttpStatusText((int)result.code) << std::endl;
        }
    }


    // --- PRIVATE ---
    std::string PlayerAPI::tryGetAccessToken() const {
        try {
            return m_client->getAccessToken();
        } catch (...) {
            std::cerr << "CRITICAL: Crash during AccessToken retrieval!" << std::endl;
            throw;
        }
    }

    void PlayerAPI::skipHelper(bool is_next, std::optional<std::string> device_id) const {
        if (!m_client) return;

        std::string token = tryGetAccessToken();

        std::string url = BASE_PLAYER_URL + "/previous";
        if (is_next)
            url = BASE_PLAYER_URL + "/next";

        if (device_id.has_value() && !device_id->empty()) {
            url += "?device_id=" + *device_id;
        }

        auto result = HTTP::post(url, token, "");

        if (result.code != RFC2616_Code::NO_CONTENT && result.code != RFC2616_Code::OK) {
            std::cerr << "Skip track failed: " << WebTools::getHttpStatusText((int)result.code) << std::endl;
        }
    }
}