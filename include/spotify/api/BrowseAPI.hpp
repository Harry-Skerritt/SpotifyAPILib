//
// Created by Harry Skerritt on 22/12/2025.
//

#ifndef BROWSEAPI_H
#define BROWSEAPI_H

#pragma once
#include <string>
#include <optional>
#include <iostream>

#include "spotify/internal.hpp"

namespace Spotify {

    class BrowseAPI : public BaseAPI {
    // Funcs
    public:

        explicit BrowseAPI(Client* client) : BaseAPI(client) {};

        // Market

        /// Gets a list of markets where Spotify is available
        /// @return Vector of strings
        [[nodiscard]] std::vector<std::string> getAvailableMarkets() const;

        // Search
        /// Perform a search for a query
        /// @param q Search query (IDs, URIs, or plain text)
        /// @param type Object type to search for
        /// @param market ISO 3166-1 country code (optional)
        /// @param limit Max number of items to return (optional)
        /// @param offset Index of first item to return (optional)
        /// @param include_external Enables searching of external audio (Optional)
        [[nodiscard]] SearchObject searchForItem(
            const std::string &q,
            const std::vector<SearchType>& type,
            const std::optional<std::string>& market = std::nullopt,
            const std::optional<int>& limit = std::nullopt,
            const std::optional<int>& offset = std::nullopt,
            const std::optional<std::string>& include_external = std::nullopt
        ) const;
    };

}

#endif //BROWSEAPI_H
