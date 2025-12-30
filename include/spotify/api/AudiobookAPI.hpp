//
// Created by Harry Skerritt on 22/12/2025.
//

#ifndef AUDIOBOOKAPI_HPP
#define AUDIOBOOKAPI_HPP

#pragma once
#include <string>
#include <optional>
#include <iostream>
#include "spotify/models/Types.hpp"
#include "spotify/api/BaseAPI.hpp"


namespace Spotify {

    class AudiobookAPI : public BaseAPI {
    // Funcs
    public:

        explicit AudiobookAPI(Client* client) : BaseAPI(client) {};

        // GET
        /// Retrieves a Spotify audiobook by its ID
        /// @param id Spotify audiobook ID
        /// @param market ISO 3166-1 country code (optional)
        [[nodiscard]] AudiobookObject getAudiobook(
            const std::string &id,
            const std::optional<std::string>& market = std::nullopt
        ) const;

        /// Retrieves multiple Spotify audiobooks by their IDs
        /// @param ids A vector of Spotify audiobook IDs (max 50)
        /// @param market ISO 3166-1 country code (optional)
        [[nodiscard]] AudiobookListObject getMultipleAudiobooks(
            const std::vector<std::string>& ids,
            const std::optional<std::string>& market = std::nullopt
        ) const;

        /// Retrieves chapters from a Spotify audiobook by its ID
        /// @param id A Spotify audiobook ID
        /// @param market ISO 3166-1 country code (optional)
        /// @param limit Max number of items to return (optional)
        /// @param offset Index of first item to return (optional)
        [[nodiscard]] PagedChapterObject getAudiobookChapters(
            const std::string &id,
            const std::optional<std::string>& market = std::nullopt,
            const std::optional<int>& limit = std::nullopt,
            const std::optional<int>& offset = std::nullopt
        ) const;

        /// Retrieves the current user's saved audiobooks
        /// @param limit Max number of items to return (optional)
        /// @param offset Index of first item to return (optional)
        /// @note Requires @c user-library-read scope
        [[nodiscard]] PagedAudiobookObject getUsersSavedAudiobooks(
            const std::optional<int>& limit = std::nullopt,
            const std::optional<int>& offset = std::nullopt
        ) const;

        /// Checks whether the given audiobooks are saved in the user's library
        /// @param ids Vector of Spotify audiobook IDs
        /// @note Requires @c user-library-read scope
        /// @return Vector of booleans, one per input ID
        [[nodiscard]] std::vector<bool> checkUsersSavedAudiobooks(const std::vector<std::string>& ids) const;


        // PUT
        /// Saves the Spotify audiobooks to the user's library
        /// @param ids Vector of Spotify audiobook IDs
        /// @note Requires @c user-library-modify scope
        void saveAudiobookForUser(const std::vector<std::string>& ids) const;

        // DELETE
        /// Removes the Spotify audiobooks from the user's library
        /// @param ids Vector of Spotify audiobook IDs
        /// @note Requires @c user-library-modify scope
        void removeUsersSavedAudiobooks(const std::vector<std::string>& ids) const;
    };

}

#endif //AUDIOBOOKAPI_HPP
