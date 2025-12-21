//
// Created by Harry Skerritt on 21/12/2025.
//

#include <utility>

#include "spotify/api/AlbumAPI.hpp"

#include "nlohmann/json.hpp"
#include "spotify/core/Client.hpp"
#include "spotify/util/Http.hpp"
#include "spotify/util/Tools.hpp"

namespace Spotify {
    AlbumAPI::AlbumAPI(Client *client) : m_client(client) { }


    // --- GET ---
    std::optional<AlbumObject> AlbumAPI::getAlbum(const std::string &id, std::optional<std::string> market) const {
        if (!m_client) return std::nullopt;

        std::string token = tryGetAccessToken();

        std::string url = BASE_ALBUM_URL + "/" + WebTools::urlEncode(id);

        if (market.has_value() && !market->empty() && Tools::isValidMarket(*market)) {
                url += "?market=" + WebTools::urlEncode(*market);
        }

        auto result = HTTP::get(url, token);

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
            return data.get<AlbumObject>();

        } catch (const nlohmann::json::exception& e) {
            std::cerr << "JSON Mapping failed: " << e.what() << std::endl;
            return std::nullopt;
        }
    }

    std::optional<AlbumListObject> AlbumAPI::getMultipleAlbums(const std::vector<std::string>& ids, std::optional<std::string> market) const {
        if (!m_client) return std::nullopt;

        std::string token = tryGetAccessToken();

        std::string id_list = Tools::toCSV(ids, 0, 20);
        if (id_list == "size-error") {
            std::cerr << "Error: You must provide between 1 and 20 IDs." << std::endl;
            return std::nullopt;
        }

        std::string url = BASE_ALBUM_URL + "?ids=" + id_list;

        if (market.has_value() && !market->empty()) {
            if (Tools::isValidMarket(*market)) {
                url += "&market=" + WebTools::urlEncode(*market);
            }
        }

        auto result = HTTP::get(url, token);

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
            return data.get<AlbumListObject>();

        } catch (const nlohmann::json::exception& e) {
            std::cerr << "JSON Mapping failed: " << e.what() << std::endl;
            return std::nullopt;
        }

    }

    std::optional<PagedTrackObject> AlbumAPI::getAlbumTracks(const std::string &id, std::optional<std::string> market, std::optional<int> limit, std::optional<int> offset) const {
        if (!m_client) return std::nullopt;

        std::string token = tryGetAccessToken();

        std::string url = BASE_ALBUM_URL + "/" + WebTools::urlEncode(id) + "/tracks";

        std::vector<std::string> params;

        if (market &&  !market->empty() && Tools::isValidMarket(*market)) {
            params.push_back("market=" + WebTools::urlEncode(*market));
        }

        if (limit && Tools::inRange(*limit, 1, 50)) {
            params.push_back("limit=" + std::to_string(*limit));
        }

        if (offset && offset >= 0) {
            params.push_back("offset=" + std::to_string(*offset));
        }

        if (!params.empty()) {
            url += "?";
            for (size_t i = 0; i < params.size(); i++) {
                url += params[i];
                if (i < params.size() - 1) url += "&";
            }
        }

        auto result = HTTP::get(url, token);

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
            return data.get<PagedTrackObject>();

        } catch (const nlohmann::json::exception& e) {
            std::cerr << "JSON Mapping failed: " << e.what() << std::endl;
            return std::nullopt;
        }
    }

    std::optional<PagedAlbumObject> AlbumAPI::getUsersSavedAlbums(std::optional<int> limit, std::optional<int> offset, std::optional<std::string> market) const {
        if (!m_client) return std::nullopt;

        std::string token = tryGetAccessToken();

        std::string url = BASE_ALBUM_USER_URL;

        std::vector<std::string> params;

        if (market &&  !market->empty() && Tools::isValidMarket(*market)) {
            params.push_back("market=" + WebTools::urlEncode(*market));
        }

        if (limit && Tools::inRange(*limit, 1, 50)) {
            params.push_back("limit=" + std::to_string(*limit));
        }

        if (offset && offset >= 0) {
            params.push_back("offset=" + std::to_string(*offset));
        }

        if (!params.empty()) {
            url += "?";
            for (size_t i = 0; i < params.size(); i++) {
                url += params[i];
                if (i < params.size() - 1) url += "&";
            }
        }

        auto result = HTTP::get(url, token);

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
            return data.get<PagedAlbumObject>();

        } catch (const nlohmann::json::exception& e) {
            std::cerr << "JSON Mapping failed: " << e.what() << std::endl;
            return std::nullopt;
        }
    }

    std::optional<std::vector<bool> > AlbumAPI::checkUsersSavedAlbums(std::vector<std::string> ids) const {
        if (!m_client) return std::nullopt;

        std::string token = tryGetAccessToken();

        std::string id_list = Tools::toCSV(ids, 0, 20);
        if (id_list == "size-error") {
            std::cerr << "Error: You must provide between 1 and 20 IDs." << std::endl;
            return std::nullopt;
        }

        std::string url = BASE_ALBUM_URL + "/contains?ids=" + id_list;

        auto result = HTTP::get(url, token);

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
            return data.get<std::vector<bool>>();

        } catch (const nlohmann::json::exception& e) {
            std::cerr << "JSON Mapping failed: " << e.what() << std::endl;
            return std::nullopt;
        }
    }

    std::optional<PagedAlbumObject> AlbumAPI::getNewReleases(std::optional<int> limit, std::optional<int> offset) {
        if (!m_client) return std::nullopt;

        std::string token = tryGetAccessToken();

        std::string url = BASE_BROWSE_URL;

        std::vector<std::string> params;

        if (limit && Tools::inRange(*limit, 1, 50)) {
            params.push_back("limit=" + std::to_string(*limit));
        }

        if (offset && offset >= 0) {
            params.push_back("offset=" + std::to_string(*offset));
        }

        if (!params.empty()) {
            url += "?";
            for (size_t i = 0; i < params.size(); i++) {
                url += params[i];
                if (i < params.size() - 1) url += "&";
            }
        }

        auto result = HTTP::get(url, token);

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
            return data.get<PagedAlbumObject>();

        } catch (const nlohmann::json::exception& e) {
            std::cerr << "JSON Mapping failed: " << e.what() << std::endl;
            return std::nullopt;
        }
    }


    // --- PUT ---
    void AlbumAPI::SaveAlbumsForUser(std::vector<std::string> ids) const {
        if (!m_client) return;

        std::string token = tryGetAccessToken();

        std::string id_list = Tools::toCSV(ids, 0, 20);
        if (id_list == "size-error") {
            std::cerr << "Error: You must provide between 1 and 20 IDs." << std::endl;
            return;
        }

        std::string url = BASE_ALBUM_USER_URL + "?ids=" + id_list;


        nlohmann::json j;
        j["ids"] = id_list;

        std::string body = j.dump();

        auto result = HTTP::put(url, token , body);

        if (result.code != RFC2616_Code::NO_CONTENT && result.code != RFC2616_Code::OK) {
            std::cerr << "Transfer Playback failed: " << (int)result.code << " - " << result.body << std::endl;
        }
    }


    // --- DELETE ---
    void AlbumAPI::RemoveUsersSavedAlbums(std::vector<std::string> ids) const {
        if (!m_client) return;

        std::string token = tryGetAccessToken();

        std::string id_list = Tools::toCSV(ids, 0, 20);
        if (id_list == "size-error") {
            std::cerr << "Error: You must provide between 1 and 20 IDs." << std::endl;
            return;
        }

        std::string url = BASE_ALBUM_USER_URL + "?ids=" + id_list;

        nlohmann::json j;
        j["ids"] = id_list;

        std::string body = j.dump();

        auto result = HTTP::remove(url, token , body);

        if (result.code != RFC2616_Code::NO_CONTENT && result.code != RFC2616_Code::OK) {
            std::cerr << "Transfer Playback failed: " << (int)result.code << " - " << result.body << std::endl;
        }

    }


    // --- PRIVATE ---
    std::string AlbumAPI::tryGetAccessToken() const {
        try {
            return m_client->getAccessToken();
        } catch (...) {
            std::cerr << "CRITICAL: Crash during AccessToken retrieval!" << std::endl;
            throw;
        }
    }

}
