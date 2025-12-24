//
// Created by Harry Skerritt on 24/12/2025.
//

#include <utility>

#include "spotify/api/PlaylistAPI.hpp"

#include <regex>

#include "nlohmann/json.hpp"
#include "spotify/core/Client.hpp"
#include "spotify/util/Http.hpp"
#include "spotify/util/Tools.hpp"

namespace Spotify {

    // --- GET ---
    std::optional<PlaylistObject> PlaylistAPI::getPlaylist(
        const std::string &playlist_id,
        const std::optional<std::string> &market,
        const std::optional<std::string> &fields,
        const std::optional<AdditionalType> &additional_types) const
    {

        std::string url = BASE_PLAYLIST_URL + "/" + playlist_id;

        std::vector<std::string> params;

        if (market.has_value() &&  !market->empty() && Tools::isValidMarket(*market)) {
            params.push_back("market=" + WebTools::urlEncode(*market));
        }

        if (fields.has_value() && !fields->empty()) {
            params.push_back("fields=" + WebTools::urlEncode(*fields));
        }

        if (additional_types.has_value()) {
            params.push_back("additional_types=" + WebTools::urlEncode(additionalTypeToString(*additional_types)));
        }

        if (!params.empty()) {
            url += "?";
            for (size_t i = 0; i < params.size(); i++) {
                url += params[i];
                if (i < params.size() - 1) url += "&";
            }
        }

        return fetchAndParse<PlaylistObject>(url);
    }

    std::optional<PagedTrackObject> PlaylistAPI::getPlaylistItems(
        const std::string &playlist_id,
        const std::optional<std::string> &market,
        const std::optional<std::string>& fields,
        const std::optional<int> &limit,
        const std::optional<int> &offset,
        const std::optional<AdditionalType>& additional_types) const
    {

        std::string url = BASE_PLAYLIST_URL + "/" + playlist_id + "/tracks";

        std::vector<std::string> params;

        if (market.has_value() &&  !market->empty() && Tools::isValidMarket(*market)) {
            params.push_back("market=" + WebTools::urlEncode(*market));
        }

        if (fields.has_value() && !fields->empty()) {
            params.push_back("fields=" + WebTools::urlEncode(*fields));
        }

        if (limit && Tools::inRange(*limit, 1, 50)) {
            params.push_back("limit=" + std::to_string(*limit));
        }

        if (offset && offset >= 0) {
            params.push_back("offset=" + std::to_string(*offset));
        }

        if (additional_types.has_value()) {
            params.push_back("additional_types=" + WebTools::urlEncode(additionalTypeToString(*additional_types)));
        }

        if (!params.empty()) {
            url += "?";
            for (size_t i = 0; i < params.size(); i++) {
                url += params[i];
                if (i < params.size() - 1) url += "&";
            }
        }

        return fetchAndParse<PagedTrackObject>(url);
    }

    std::optional<PagedPlaylistObject> PlaylistAPI::getCurrentUsersPlaylists(
        const std::optional<int> &limit,
        const std::optional<int> &offset) const {

        std::string url = BASE_PLAYLIST_USER_URL;

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

        return fetchAndParse<PagedPlaylistObject>(url);
    }

    std::optional<PagedPlaylistObject> PlaylistAPI::getUsersPlaylists(
        const std::string &user_id,
        const std::optional<int> &limit,
        const std::optional<int> &offset) const {

        std::string url = BASE_USER_URL + "/" + user_id + "/playlists";

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

        return fetchAndParse<PagedPlaylistObject>(url);
    }

    std::optional<std::vector<ImageObject> > PlaylistAPI::getPlaylistCoverImage(const std::string &playlist_id) const {

        std::string url = BASE_PLAYLIST_URL + "/" + playlist_id + "/images";

        return fetchAndParse<std::vector<ImageObject> >(url);
    }


    // --- PUT ---







}