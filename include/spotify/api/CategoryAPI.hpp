//
// Created by Harry Skerritt on 22/12/2025.
//

#ifndef CATEGORYAPI_H
#define CATEGORYAPI_H

#pragma once
#include <string>
#include <optional>
#include <iostream>
#include "spotify/models/Types.hpp"
#include "spotify/util/JsonMapping.hpp"
#include "spotify/api/BaseAPI.hpp"

namespace Spotify {

    class CategoryAPI : public BaseAPI {
        // Funcs
    public:
        explicit CategoryAPI(Client* client) : BaseAPI(client) {}

        // GET
        /// Retrieves Spotify browse categories.
        /// @param locale ISO 639-1 Language code and ISO 3166-1 country code (optional)
        /// @param limit Max number of items to return (optional)
        /// @param offset Index of first item to return (optional)
        [[nodiscard]] PagedCategoryObject getMultipleBrowseCategories(
            const std::optional<std::string>& locale = std::nullopt,
            const std::optional<int>& limit = std::nullopt,
            const std::optional<int>& offset = std::nullopt
        ) const;


        /// Retrieves a Spotify browse category by its ID.
        /// @param category_id Spotify category ID.
        /// @param locale ISO 639-1 Language code and ISO 3166-1 country code (optional)
        [[nodiscard]] CategoryObject getBrowseCategory(
            const std::string& category_id,
            const std::optional<std::string>& locale = std::nullopt
        ) const;
    };
}


#endif //CATEGORYAPI_H
