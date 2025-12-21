//
// Created by Harry Skerritt on 21/12/2025.
//

#include <utility>

#include "spotify/api/PlayerAPI.hpp"

#include "nlohmann/json.hpp"
#include "spotify/core/Client.hpp"
#include "spotify/util/Http.hpp"

Spotify::PlayerAPI::PlayerAPI(Client *client) : m_client(client) { }

// --- GET ---
std::optional<Spotify::PlaybackObject> Spotify::PlayerAPI::getPlaybackState() const {
    if (!m_client) return std::nullopt;

    std::string token = tryGetAccessToken();
    auto result = HTTP::get((BASE_PLAYER_URL), token);


    if (result.code == RFC2616_Code::NO_CONTENT || result.code != RFC2616_Code::OK) {
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

std::optional<Spotify::DeviceListObject> Spotify::PlayerAPI::getAvailableDevices() const {
    if (!m_client) return std::nullopt;

    std::string token = tryGetAccessToken();
    auto result = HTTP::get((BASE_PLAYER_URL + "/devices"), token);


    if (result.code == RFC2616_Code::NO_CONTENT || result.code != RFC2616_Code::OK) {
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

std::optional<Spotify::PlaybackObject> Spotify::PlayerAPI::getCurrentlyPlayingTrack() const {
    if (!m_client) return std::nullopt;

    std::string token = tryGetAccessToken();
    auto result = HTTP::get((BASE_PLAYER_URL + "/currently-playing"), token);

    if (result.code == RFC2616_Code::NO_CONTENT || result.code != RFC2616_Code::OK) {
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

std::optional<Spotify::RecentlyPlayedTracksObject> Spotify::PlayerAPI::getRecentlyPlayedTracks() const {
    if (!m_client) return std::nullopt;

    std::string token = tryGetAccessToken();
    auto result = HTTP::get((BASE_PLAYER_URL + "/currently-playing"), token);

    if (result.code == RFC2616_Code::NO_CONTENT || result.code != RFC2616_Code::OK) {
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

std::optional<Spotify::QueueObject> Spotify::PlayerAPI::getUsersQueue() const {
    if (!m_client) return std::nullopt;

    std::string token = tryGetAccessToken();
    auto result = HTTP::get((BASE_PLAYER_URL + "/currently-playing"), token);

    if (result.code == RFC2616_Code::NO_CONTENT || result.code != RFC2616_Code::OK) {
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
void Spotify::PlayerAPI::skipToNext(std::optional<std::string> device_id) const {
    skipHelper(true, std::move(device_id));
}

void Spotify::PlayerAPI::skipToPrevious(std::optional<std::string> device_id) const {
    skipHelper(false, std::move(device_id));
}

void Spotify::PlayerAPI::addItemToQueue(std::string uri, std::optional<std::string> device_id) {
    if (!m_client) return;

    std::string token = tryGetAccessToken();

    std::string url = BASE_PLAYER_URL + "/queue?uri=" + WebTools::urlEncode(uri);

    if (device_id.has_value() && !device_id->empty()) {
        url += "&device_id=" + *device_id;
    }

    auto result = HTTP::post(url, token, "");

    if (result.code != RFC2616_Code::OK) {
        std::cerr << "Failed to add to queue: " << (int)result.code << std::endl;
    }
}


// --- PUT ---

// --- PRIVATE ---
std::string Spotify::PlayerAPI::tryGetAccessToken() const {
    try {
        return m_client->getAccessToken();
    } catch (...) {
        std::cerr << "CRITICAL: Crash during AccessToken retrieval!" << std::endl;
        throw;
    }
}

void Spotify::PlayerAPI::skipHelper(bool is_next, std::optional<std::string> device_id) const {
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


