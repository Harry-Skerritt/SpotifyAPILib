//
// Created by Harry Skerritt on 22/12/2025.
//

#include "spotify/api/ChapterAPI.hpp"
#include "spotify/core/Endpoints.hpp"
#include "spotify/util/Tools.hpp"

#include "nlohmann/json.hpp"



namespace Spotify {

    // --- GET ---
    ChapterObject ChapterAPI::getChapter(
        const std::string &id,
        const std::optional<std::string> &market) const
    {

        std::string url = Endpoints::CHAPTERS + "/" + WebTools::urlEncode(id);

        if (market.has_value() && !market->empty()) {
            url += "?market=" +  WebTools::urlEncode(*market);
        }

        return fetchAndParse<ChapterObject>(url);
    }

    ChapterListObject ChapterAPI::getMultipleChapters(
        const std::vector<std::string> &ids,
        const std::optional<std::string> &market) const
    {

        std::string id_list = Tools::toCSV(ids, 0, 50);

        std::string url = Endpoints::CHAPTERS + "?ids=" + id_list;

        if (market.has_value() && !market->empty() && Tools::isValidMarket(*market)) {
            url += "?market=" + WebTools::urlEncode(*market);
        }

        return fetchAndParse<ChapterListObject>(url);

    }



}
