//
// Created by Harry Skerritt on 22/12/2025.
//

#include "spotify/api/ArtistAPI.hpp"
#include "spotify/core/Endpoints.hpp"
#include "../../include/spotify/util/common/Tools.hpp"

#include "nlohmann/json.hpp"

namespace Spotify {

    // --- GET ---
    ArtistObject ArtistAPI::getArtist(const std::string &id) const {

        std::string url = Endpoints::ARTISTS + "/" + detail::urlEncode(id);

        return fetchAndParse<ArtistObject>(url);
    }

   ArtistListObject ArtistAPI::getMultipleArtists(const std::vector<std::string> &ids) const {

        std::string id_list = detail::toCSV(ids, 0, 20);


        std::string url = Endpoints::ARTISTS  + "?ids=" + id_list;

       return fetchAndParse<ArtistListObject>(url);
    }

    PagedAlbumObject ArtistAPI::getArtistsAlbums(
        const std::string &id,
        const std::optional<std::vector<IncludeGroups>>& include_groups,
        const std::optional<std::string>& market,
        const std::optional<int>& limit,
        const std::optional<int>& offset) const
    {
        std::string url = Endpoints::ARTISTS  + "/" + detail::urlEncode(id) + "/albums";

        std::vector<std::string> params;

        if (include_groups.has_value() && !include_groups->empty() && include_groups->size() <= 4) {
            std::string group_str = buildIncludeGroupsString(*include_groups);
            params.push_back("include_groups=" + detail::urlEncode(group_str));
        }

        if (market &&  !market->empty() && Tools::isValidMarket(*market)) {
            params.push_back("market=" + detail::urlEncode(*market));
        }

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

        return fetchAndParse<PagedAlbumObject>(url);
    }

    TrackListObject ArtistAPI::getArtistTopTracks(
        const std::string &id,
        const std::optional<std::string>& market) const
    {

        std::string url = Endpoints::ARTISTS  + "/" + detail::urlEncode(id) + "/top-tracks";

        if (market.has_value() && !market->empty() && Tools::isValidMarket(*market)) {
            url += "?market=" + detail::urlEncode(*market);
        }

        return fetchAndParse<TrackListObject>(url);
    }

}
