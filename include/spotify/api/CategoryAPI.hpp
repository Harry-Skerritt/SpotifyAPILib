//
// Created by Harry Skerritt on 22/12/2025.
//

#ifndef CATEGORYAPI_H
#define CATEGORYAPI_H

#pragma once
#include <string>
#include <optional>
#include <iostream>
#include "spotify/util/Types.h"
#include "spotify/util/JsonMapping.hpp"
#include "spotify/api/BaseAPI.hpp"

namespace Spotify {

    class CategoryAPI : public BaseAPI {
        // Funcs
    public:
        explicit CategoryAPI(Client* client) : BaseAPI(client) {}

        // GET
        [[nodiscard]] PagedCategoryObject getMultipleBrowseCategories(
            const std::optional<std::string>& locale = std::nullopt,
            const std::optional<int>& limit = std::nullopt,
            const std::optional<int>& offset = std::nullopt
        ) const;

        [[nodiscard]] CategoryObject getBrowseCategory(
            const std::string& category_id,
            const std::optional<std::string>& locale = std::nullopt
        ) const;
    };
}


#endif //CATEGORYAPI_H
