//
// Created by Harry Skerritt on 28/12/2025.
//

#ifndef USERSAPI_H
#define USERSAPI_H

#pragma once
#include <string>
#include <optional>
#include <iostream>
#include "spotify/models/Types.hpp"
#include "spotify/api/BaseAPI.hpp"

namespace Spotify {

    class UsersAPI : public BaseAPI {
    //Funcs
    public:

        explicit UsersAPI(Client* client) : BaseAPI(client) {}

        // GET

        /// Retrieves the current users profile
        /// @note Requires @c user-read-private scope
        /// @note Requires @c user-read-email scope
        [[nodiscard]] UserObject getCurrentUserProfile() const;

        /// Retrieves the current users top artists
        /// @param time_range The time frame to return values from (Optional)
        /// @param limit Max number of items to return (optional)
        /// @param offset Index of first item to return (optional)
        /// @note Requires @c user-top-read scope
        [[nodiscard]] PagedArtistObject getUsersTopArtists(
            const std::optional<std::string>& time_range = std::nullopt,
            const std::optional<int>& limit = std::nullopt,
            const std::optional<int>& offset = std::nullopt
        ) const;

        /// Retrieves the current users top tracks
        /// @param time_range The time frame to return values from (Optional)
        /// @param limit Max number of items to return (optional)
        /// @param offset Index of first item to return (optional)
        /// @note Requires @c user-top-read scope
        [[nodiscard]] PagedTrackObject getUsersTopTracks(
            const std::optional<std::string>& time_range = std::nullopt,
            const std::optional<int>& limit = std::nullopt,
            const std::optional<int>& offset = std::nullopt
        ) const;

        /// Retrieves the profile of a Spotify user
        /// @param user_id Spotify user ID
        [[nodiscard]] UserObject getUsersProfile(const std::string& user_id) const;

        /// Retrieves the current users followed artists
        /// @param after Last artist ID retrieved (optional)
        /// @param limit Max number of items to return (optional)
        /// @note Requires @c user-follow-read scope
        [[nodiscard]] PagedArtistObject getFollowedArtists(
            const std::string& type = "artist",
            const std::optional<std::string>& after = std::nullopt,
            const std::optional<int>& limit = std::nullopt
        ) const;

        /// Checks whether the current user follows the given artists
        /// @param ids Vector of Spotify artist IDs
        /// @note Requires @c user-follow-read scope
        /// @return Vector of booleans, one per input ID
        [[nodiscard]] std::vector<bool> checkUserFollowsArtists(const std::vector<std::string>& ids) const;

        /// Checks whether the current user follows the given users
        /// @param ids Vector of Spotify user IDs
        /// @note Requires @c user-follow-read scope
        /// @return Vector of booleans, one per input ID
        [[nodiscard]] std::vector<bool> checkUserFollowsUsers(const std::vector<std::string>& ids) const;

        /// Checks whether the current user follows a playlist
        /// @param playlist_id Spotify playlist IDs
        /// @param id A Spotify user ID (optional) [deprecated]
        /// @return Vector of booleans of size 1
        [[nodiscard]] std::vector<bool> checkUserFollowsPlaylist(
            const std::string& playlist_id,
            const std::optional<std::string>& id
        ) const;

        // PUT
        /// Adds the current user to a Spotify playlists followers
        /// @param playlist_id Spotify playlist ID
        /// @param is_public Show playlist in users public playlists (optional)
        /// @note Requires @c playlist-modify-private scope
        /// @note Requires @c playlist-modify-public scope
        void followPlaylist(
            const std::string& playlist_id,
            const std::optional<bool>& is_public = std::nullopt
        ) const;

        /// Adds the current user to a Spotify artists followers
        /// @param ids Spotify artist IDs
        /// @note Requires @c user-follow-modify scope
        void followArtist( const std::vector<std::string>& ids) const;

        /// Adds the current user to a Spotify users followers
        /// @param ids Spotify users IDs
        /// @note Requires @c user-follow-modify scope
        void followUser(const std::vector<std::string>& ids) const;


        // DELETE
        /// Removes the current user from a Spotify playlists followers
        /// @param playlist_id Spotify playlist ID
        /// @note Requires @c playlist-modify-private scope
        /// @note Requires @c playlist-modify-public scope
        void unfollowPlaylist(const std::string& playlist_id) const;

        /// Removes the current user from a Spotify artists followers
        /// @param ids Spotify artist IDs
        /// @note Requires @c user-follow-modify scope
        void unfollowArtist(const std::vector<std::string>& ids) const;

        /// Removes the current user from a Spotify users followers
        /// @param ids Spotify user IDs
        /// @note Requires @c user-follow-modify scope
        void unfollowUser(const std::vector<std::string>& ids) const;

    };

}
#endif //USERSAPI_H
