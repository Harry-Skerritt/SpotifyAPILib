//
// Created by Harry Skerritt on 22/12/2025.
//

#include "spotify/api/BrowseAPI.hpp"
#include "spotify/core/Endpoints.hpp"
#include "spotify/util/Tools.hpp"

#include "nlohmann/json.hpp"


namespace Spotify {

    // --- Market ---
    std::vector<std::string> BrowseAPI::getAvailableMarkets() const {
        const std::string url = Endpoints::API_V1 + "/markets";

        return fetchAndParse<std::vector<std::string>>(url, "markets");
    }


    // --- Search ---
    SearchObject BrowseAPI::searchForItem(
        const std::string &q,
        const std::vector<SearchType> &type,
        const std::optional<std::string> &market,
        const std::optional<int> &limit,
        const std::optional<int> &offset,
        const std::optional<std::string> &include_external) const
    {

        std::string url = Endpoints::API_V1 + "/search?q=" + WebTools::urlEncode(q);

        std::string type_str = buildSearchTypeString(type);
        url += "&type=" + WebTools::urlEncode(type_str);

        if (market &&  !market->empty() && Tools::isValidMarket(*market)) {
            url += "&market=" + WebTools::urlEncode(*market);
        }

        if (limit && Tools::inRange(*limit, 1, 50)) {
            url += "&limit=" + std::to_string(*limit);
        }

        if (offset && offset >= 0) {
            url += "&offset=" + std::to_string(*offset);
        }

        if (include_external && include_external == "audio")
            url += "&include_external=audio";
        else
            throw LogicException("include_external can only be equal to 'audio'");

        return fetchAndParse<SearchObject>(url);


    }


}
