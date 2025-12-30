//
// Created by Harry Skerritt on 24/12/2025.
//

#include <utility>

#include "spotify/api/PlaylistAPI.hpp"


#include "spotify/core/Client.hpp"
#include "spotify/core/Endpoints.hpp"
#include "../../include/spotify/util/web/Http.hpp"
#include "../../include/spotify/util/parse/JsonMapping.hpp"
#include "../../include/spotify/util/common/Tools.hpp"

#include "nlohmann/json.hpp"

namespace Spotify {

    // --- GET ---
    PlaylistObject PlaylistAPI::getPlaylist(
        const std::string &playlist_id,
        const std::optional<std::string> &market,
        const std::optional<std::string> &fields,
        const std::optional<AdditionalType> &additional_types) const
    {
        std::string url = Endpoints::PLAYLISTS + "/" + playlist_id;

        std::vector<std::string> params;

        if (market.has_value() &&  !market->empty() && Tools::isValidMarket(*market)) {
            params.push_back("market=" + detail::urlEncode(*market));
        }

        if (fields.has_value() && !fields->empty()) {
            params.push_back("fields=" + detail::urlEncode(*fields));
        }

        if (additional_types.has_value()) {
            params.push_back("additional_types=" + detail::urlEncode(additionalTypeToString(*additional_types)));
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

    PagedPlaylistTrackObject PlaylistAPI::getPlaylistItems(
        const std::string &playlist_id,
        const std::optional<std::string> &market,
        const std::optional<std::string>& fields,
        const std::optional<int> &limit,
        const std::optional<int> &offset,
        const std::optional<AdditionalType>& additional_types) const
    {
        std::string url = Endpoints::PLAYLISTS + "/" + playlist_id + "/tracks";

        std::vector<std::string> params;

        if (market.has_value() &&  !market->empty() && Tools::isValidMarket(*market)) {
            params.push_back("market=" + detail::urlEncode(*market));
        }

        if (fields.has_value() && !fields->empty()) {
            params.push_back("fields=" + detail::urlEncode(*fields));
        }

        if (limit && detail::inRange(*limit, 1, 50)) {
            params.push_back("limit=" + std::to_string(*limit));
        }

        if (offset && offset >= 0) {
            params.push_back("offset=" + std::to_string(*offset));
        }

        if (additional_types.has_value()) {
            params.push_back("additional_types=" + detail::urlEncode(additionalTypeToString(*additional_types)));
        }

        if (!params.empty()) {
            url += "?";
            for (size_t i = 0; i < params.size(); i++) {
                url += params[i];
                if (i < params.size() - 1) url += "&";
            }
        }

        return fetchAndParse<PagedPlaylistTrackObject>(url);
    }

    PagedPlaylistObject PlaylistAPI::getCurrentUsersPlaylists(
        const std::optional<int> &limit,
        const std::optional<int> &offset) const
    {
        std::string url = Endpoints::MY_PLAYLISTS;

        std::vector<std::string> params;

        if (limit && detail::inRange(*limit, 1, 50)) {
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

    PagedPlaylistObject PlaylistAPI::getUsersPlaylists(
        const std::string &user_id,
        const std::optional<int> &limit,
        const std::optional<int> &offset) const
    {
        std::string url = Endpoints::USERS + "/" + user_id + "/playlists";

        std::vector<std::string> params;

        if (limit && detail::inRange(*limit, 1, 50)) {
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

    std::vector<ImageObject> PlaylistAPI::getPlaylistCoverImage(const std::string &playlist_id) const {

        std::string url = Endpoints::PLAYLISTS + "/" + playlist_id + "/images";

        return fetchAndParse<std::vector<ImageObject> >(url);
    }



    // --- PUT ---
    void PlaylistAPI::changePlaylistDetails(
        const std::string &playlist_id,
        const std::optional<std::string> &name,
        const std::optional<bool> &is_public,
        const std::optional<std::string> &description,
        const std::optional<bool> &is_collaborative) const
    {
        std::string url = Endpoints::PLAYLISTS + "/" + playlist_id;

        nlohmann::json j;

        if (name.has_value())
            j["name"] = *name;

        if (is_public.has_value())
            j["public"] = *is_public;

        if (description.has_value())
            j["description"] = *description;

        if (is_collaborative.has_value())
            j["collaborative"] = *is_collaborative;

        (void)sendAction("PUT", url, j.dump());
    }

    void PlaylistAPI::replacePlaylistItems(
        const std::string &playlist_id,
        const std::vector<std::string> &uris) const
    {
        std::string url = Endpoints::PLAYLISTS + "/" + playlist_id + "/tracks";

        std::string uri_list = detail::toCSV(uris, 1, 100);

        nlohmann::json j;
        j["uris"] = uri_list;

        (void)sendAction("PUT", url, j.dump());
    }

    void PlaylistAPI::reorderPlaylistItems(
        const std::string& playlist_id,
        const int &range_start,
        const int &insert_before,
        const std::optional<int> &range_length,
        const std::optional<std::string> &snapshot_id) const
    {
        std::string url = Endpoints::PLAYLISTS + "/" + playlist_id + "/tracks";

        nlohmann::json j;

        j["range_start"] = range_start;
        j["insert_before"] = insert_before;

        if (range_length.has_value())
            j["range_length"] = *range_length;

        if (snapshot_id.has_value())
            j["snapshot_id"] = *snapshot_id;


        (void)sendAction("PUT", url, j.dump());
    }

    void PlaylistAPI::addCustomPlaylistCover(
        const std::string &playlist_id,
        const std::string &image_path) const
    {
        std::string raw_image_data;
        bool is_url (image_path.rfind("http://", 0) == 0 || image_path.rfind("https://", 0) == 0);

        if (is_url) {
            // Is URL
            auto result = HTTP::getImage(image_path);

            if (result.code != RFC2616_Code::OK) {
                throw APIException({static_cast<int>(result.code), "Failed to download image from URL", "IMAGE_DOWNLOAD_FAILED"});
            }

            raw_image_data = result.body;
        } else {
            // Is File
            std::ifstream file(image_path, std::ios::binary);
            if (!file.is_open()) {
                throw LogicException("Could not open local image file: " + image_path);
            }
            std::stringstream buffer;
            buffer << file.rdbuf();
            raw_image_data = buffer.str();
        }

        if (raw_image_data.size() > 256 * 1024) {
            throw LogicException("Image too large (Max 256KB). Provided size: " +  std::to_string(raw_image_data.size() / 1024) + "KB");
        }
        std::string base64_image = base64_encode(raw_image_data);

        std::string url = Endpoints::PLAYLISTS + "/" + playlist_id + "/images";

        std::map<std::string, std::string> extra_headers = {{ "Content-Type", "image/jpeg"} };


        (void)sendAction("PUT", url, base64_image, extra_headers);
    }



    // --- POST ---
    void PlaylistAPI::addItemsToPlaylist(
        const std::string &playlist_id,
        const std::vector<std::string> &uris,
        const std::optional<int> &position) const
    {
        std::string url = Endpoints::PLAYLISTS + "/" + playlist_id + "/tracks";

        if (uris.empty() || uris.size() > 100) {
            throw LogicException("You must provide between 1 and 100 URIs.");
        }

        nlohmann::json j;

        nlohmann::json uri_array = nlohmann::json::array();
        for (const auto &uri : uris) {
            uri_array.push_back(uri );
        }

        j["uris"] = uri_array;

        if (position.has_value())
            j["position"] = *position;

        (void)sendAction("POST", url, j.dump());
    }


    std::optional<PlaylistObject> PlaylistAPI::createPlaylist(
        const std::string &user_id,
        const std::string &name,
        const std::optional<bool> &is_public,
        const std::optional<bool> &is_collaborative,
        const std::optional<std::string> &description) const
    {
        std::string url = Endpoints::USERS + "/" + user_id + "/playlists";

        nlohmann::json j;
        j["name"] = name;

        if (is_public.has_value())
            j["public"] = *is_public;

        if (is_collaborative.has_value())
            j["collaborative"] = *is_collaborative;

        if (description.has_value() && !description->empty())
            j["description"] = *description;

        auto body = sendAction("POST", url, j.dump());

        if (body.has_value()) {
            try {
                auto data = nlohmann::json::parse(*body);

                return data.get<PlaylistObject>();
            } catch (const std::exception& e) {
                throw ParseException("Failed to map JSON to PlaylistObject: " + std::string(e.what()), *body);
            }
        }

        return std::nullopt;
    }



    // --- DELETE ---
    void PlaylistAPI::removePlaylistItems(
        const std::string &playlist_id,
        const std::vector<URIObject> &tracks,
        const std::optional<std::string> &snapshot_id) const
    {
        std::string url = Endpoints::PLAYLISTS + "/" + playlist_id + "/tracks";

        nlohmann::json j;

        nlohmann::json track_array = nlohmann::json::array();
        for (const auto &track : tracks) {
            track_array.push_back({ {"uri", track.uri} });
        }
        j["tracks"] = track_array;

        if (snapshot_id.has_value() && !snapshot_id->empty())
            j["snapshot_id"] = *snapshot_id;

        (void)sendAction("DELETE", url, j.dump());
    }








}