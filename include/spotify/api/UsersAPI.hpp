//
// Created by Harry Skerritt on 28/12/2025.
//

#ifndef USERSAPI_H
#define USERSAPI_H

#pragma once
#include <string>
#include <optional>
#include <iostream>
#include "spotify/util/Types.h"
#include "spotify/api/BaseAPI.hpp"

namespace Spotify {

    class UsersAPI : public BaseAPI {
    //Funcs
    public:

        explicit UsersAPI(Client* client) : BaseAPI(client) {}

        // GET

        [[nodiscard]] UserObject getCurrentUserProfile() const;

        [[nodiscard]] PagedArtistObject getUsersTopArtists(
            const std::optional<std::string>& time_range = std::nullopt,
            const std::optional<int>& limit = std::nullopt,
            const std::optional<int>& offset = std::nullopt
        ) const;

        [[nodiscard]] PagedTrackObject getUsersTopTracks(
            const std::optional<std::string>& time_range = std::nullopt,
            const std::optional<int>& limit = std::nullopt,
            const std::optional<int>& offset = std::nullopt
        ) const;

        [[nodiscard]] UserObject getUsersProfile(const std::string& user_id) const;

        [[nodiscard]] PagedArtistObject getFollowedArtists(
            const std::string& type = "artist",
            const std::optional<std::string>& after = std::nullopt,
            const std::optional<int>& limit = std::nullopt
        ) const;

        [[nodiscard]] std::vector<bool> checkUserFollowsArtists(const std::vector<std::string>& ids) const;

        [[nodiscard]] std::vector<bool> checkUserFollowsUsers(const std::vector<std::string>& ids) const;

        [[nodiscard]] std::vector<bool> checkUserFollowsPlaylist(
            const std::string& playlist_id,
            const std::optional<std::string>& id
        ) const;

        // PUT
        void followPlaylist(
            const std::string& playlist_id,
            const std::optional<bool>& is_public = std::nullopt
        ) const;

        void followArtist( const std::vector<std::string>& ids) const;

        void followUser(const std::vector<std::string>& ids) const;


        // DELETE
        void unfollowPlaylist(const std::string& playlist_id) const;

        void unfollowArtist(const std::vector<std::string>& ids) const;

        void unfollowUser(const std::vector<std::string>& ids) const;

    };

}
#endif //USERSAPI_H
