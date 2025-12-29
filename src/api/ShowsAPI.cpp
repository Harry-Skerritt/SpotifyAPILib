//
// Created by Harry Skerritt on 28/12/2025.
//

#include "spotify/api/ShowsAPI.hpp"
#include "spotify/core/Endpoints.hpp"
#include "spotify/util/Tools.hpp"

#include "nlohmann/json.hpp"

namespace Spotify {

    // --- GET ---
    ShowObject ShowsAPI::getShow(
        const std::string &id,
        const std::optional<std::string> &market) const
    {
        std::string url = Endpoints::SHOWS + "/" + WebTools::urlEncode(id);

        if (market.has_value() && !market->empty() && Tools::isValidMarket(*market)) {
            url += "?market=" + WebTools::urlEncode(*market);
        }

        return fetchAndParse<ShowObject>(url);
    }

    ShowListObject ShowsAPI::getShows(
        const std::vector<std::string> &ids,
        const std::optional<std::string> &market) const
    {
        std::string id_list = Tools::toCSV(ids, 0, 50);

        std::string url = Endpoints::SHOWS + "?ids=" + WebTools::urlEncode(id_list);

        if (market.has_value() && !market->empty() && Tools::isValidMarket(*market)) {
            url += "?market=" + WebTools::urlEncode(*market);
        }

        return fetchAndParse<ShowListObject>(url);
    }

    PagedEpisodeObject ShowsAPI::getShowEpisodes(
        const std::string &id,
        const std::optional<std::string> &market,
        const std::optional<int> &limit,
        const std::optional<int> &offset) const
    {

        std::string url = Endpoints::SHOWS + "/" + WebTools::urlEncode(id) + "/episodes";

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

        return fetchAndParse<PagedEpisodeObject>(url);
    }

    PagedSavedShowObject ShowsAPI::getUserSavedShows(
        const std::optional<int> &limit,
        const std::optional<int> &offset) const
    {
        std::string url = Endpoints::MY_SHOWS;

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

        return fetchAndParse<PagedSavedShowObject>(url);
    }

   std::vector<bool> ShowsAPI::checkUsersSavedShows(const std::vector<std::string> &ids) const {
        std::string id_list = Tools::toCSV(ids, 0, 50);

        std::string url = Endpoints::MY_SHOWS + "/contains?ids=" + id_list;

        return fetchAndParse<std::vector<bool>>(url);
    }

    // --- PUT ---
    void ShowsAPI::saveShowsForUser(const std::vector<std::string> &ids) const {
        if (ids.empty()) throw Spotify::LogicException("IDs cannot be empty");

        std::string id_list = Tools::toCSV(ids, 0, 50);
        std::string url = Endpoints::MY_SHOWS + "?ids" = WebTools::urlEncode(id_list);

        (void)sendAction("PUT", url, "");
    }

    // --- DELETE ---
    void ShowsAPI::removeShowsForUser(
        const std::vector<std::string> &ids,
        const std::optional<std::string> &market) const
    {
        if (ids.empty()) throw Spotify::LogicException("IDs cannot be empty");

        std::string id_list = Tools::toCSV(ids, 0, 50);
        std::string url = Endpoints::MY_SHOWS + "?ids" = WebTools::urlEncode(id_list);

        if (market.has_value() && !market->empty() && Tools::isValidMarket(*market)) {
            url += "?market=" + WebTools::urlEncode(*market);
        }

        (void)sendAction("DELETE", url, "");
    }

}