//
// Created by Harry Skerritt on 23/12/2025.
//


#include <utility>

#include "spotify/api/TrackAPI.hpp"

#include "nlohmann/json.hpp"
#include "spotify/core/Client.hpp"
#include "spotify/core/Endpoints.hpp"
#include "spotify/util/Http.hpp"
#include "spotify/util/Tools.hpp"

namespace Spotify {

    // --- GET ---
    std::optional<TrackObject> TrackAPI::getTrack(const std::string &id, const std::optional<std::string> &market) const {
        std::string url = Endpoints::TRACKS + "/" + WebTools::urlEncode(id);

        if (market.has_value() && !market->empty() && Tools::isValidMarket(*market)) {
            url += "?market=" + WebTools::urlEncode(*market);
        }

        return fetchAndParse<TrackObject>(url);
    }

    std::optional<TrackListObject> TrackAPI::getTracks(const std::vector<std::string> &ids, const std::optional<std::string> &market) const {
        std::string id_list = Tools::toCSV(ids, 0, 50);

        std::string url = Endpoints::TRACKS + "?ids=" + id_list;

        if (market.has_value() && !market->empty() && Tools::isValidMarket(*market)) {
            url += "?market=" + WebTools::urlEncode(*market);
        }

        return fetchAndParse<TrackListObject>(url);
    }

    std::optional<PagedSavedTrackObject> TrackAPI::getUserSavedTracks(const std::optional<std::string> &market, const std::optional<int> &limit, const std::optional<int> &offset) const {
        std::string url = Endpoints::MY_TRACKS;

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

        return fetchAndParse<PagedSavedTrackObject>(url);
    }

    std::optional<std::vector<bool> > TrackAPI::checkUsersSavedTracks(const std::vector<std::string> &ids) const {
        std::string id_list = Tools::toCSV(ids, 0, 50);

        std::string url = Endpoints::MY_TRACKS + "/contains?ids=" + id_list;

        return fetchAndParse<std::vector<bool>>(url);
    }


    // --- PUT ---
    void TrackAPI::saveTracksForUser(const std::vector<std::string> &ids) const {
        if (ids.empty()) return;

        nlohmann::json j;
        j["ids"] = ids;

        (void)sendAction("PUT", Endpoints::MY_TRACKS, j.dump());
    }

    void TrackAPI::saveTracksForUser(const std::vector<TimestampIDObject> &timestamped_ids) const {
        if (timestamped_ids.empty()) return;
        if (timestamped_ids.size() > 50) {
            throw LogicException("You must provide less than 50 timestamped IDs");
        }

        nlohmann::json j = nlohmann::json::object();
        nlohmann::json ts_array = nlohmann::json::array();

        for (const auto& item : timestamped_ids) {
            ts_array.push_back({
            {"id", item.id},
            {"added_at", item.added_at}
            });
        }
        j["timestamped_ids"] = ts_array;

        (void)sendAction("PUT", Endpoints::MY_TRACKS, j.dump());
    }

    // --- DELETE ---
    void TrackAPI::removeUsersSavedTracks(std::vector<std::string> ids) const {
        std::string id_list = Tools::toCSV(ids, 0, 20);

        std::string url = Endpoints::MY_TRACKS + "?ids=" + id_list;

        nlohmann::json j;
        j["ids"] = id_list;

        (void)sendAction("DELETE", url, j.dump());
    }







}