//
// Created by Harry Skerritt on 24/12/2025.
//

#ifndef PLAYLISTAPI_H
#define PLAYLISTAPI_H

#pragma once
#include <string>
#include <optional>
#include <iostream>
#include "spotify/api/BaseAPI.hpp"
#include "spotify/models/Types.hpp"
#include "spotify/util/SpotifyEnums.hpp"

namespace Spotify {

    class PlaylistAPI : public BaseAPI {
    // Funcs
    public:

        explicit PlaylistAPI(Client* client) : BaseAPI(client) {}

        // GET
        /// Retrieves a Spotify playlist by its ID owned by the current user
        /// @param playlist_id Spotify playlist ID
        /// @param market ISO 3166-1 country code (optional)
        /// @param fields Fields that will be returned (optional)
        /// @param additional_types Item type to return (optional)
        [[nodiscard]] PlaylistObject getPlaylist(
            const std::string& playlist_id,
            const std::optional<std::string>& market = std::nullopt,
            const std::optional<std::string>& fields = std::nullopt,
            const std::optional<AdditionalType>& additional_types = std::nullopt
        ) const;

        /// Retrieves tracks of a Spotify playlist owned by the current user
        /// @param playlist_id Spotify playlist ID
        /// @param market ISO 3166-1 country code (optional)
        /// @param fields Fields that will be returned (optional)
        /// @param limit Max number of items to return (optional)
        /// @param offset Index of first item to return (optional)
        /// @param additional_types Item type to return (optional)
        /// @note Requires @c playlist-read-private scope
        [[nodiscard]] PagedPlaylistTrackObject getPlaylistItems(
            const std::string& playlist_id,
            const std::optional<std::string>& market = std::nullopt,
            const std::optional<std::string>& fields = std::nullopt,
            const std::optional<int>& limit = std::nullopt,
            const std::optional<int>& offset = std::nullopt,
            const std::optional<AdditionalType>& additional_types = std::nullopt
        ) const;

        /// Retrieves Spotify playlists owned by the current user
        /// @param limit Max number of items to return (optional)
        /// @param offset Index of first item to return (optional)
        /// @note Requires @c playlist-read-private scope
        [[nodiscard]] PagedPlaylistObject getCurrentUsersPlaylists(
            const std::optional<int>& limit = std::nullopt,
            const std::optional<int>& offset = std::nullopt
        ) const;

        /// Retrieves Spotify playlists owned by a user ID
        /// @param user_id Spotify user ID
        /// @param limit Max number of items to return (optional)
        /// @param offset Index of first item to return (optional)
        /// @note Requires @c playlist-read-private scope
        /// @note Requires @c playlist-read-collaborative scope
        [[nodiscard]] PagedPlaylistObject getUsersPlaylists(
            const std::string& user_id,
            const std::optional<int>& limit = std::nullopt,
            const std::optional<int>& offset = std::nullopt
        ) const;

        /// Retrieves the cover image of a Spotify playlists
        /// @param playlist_id Spotify playlist ID
        /// @return A vector of Images
        [[nodiscard]] std::vector<ImageObject> getPlaylistCoverImage(const std::string& playlist_id) const;

        // PUT
        /// Changes a playlist's details
        /// @param playlist_id Spotify playlist ID
        /// @param name New playlist name (optional)
        /// @param is_public New public state (optional)
        /// @param description New playlist description (optional)
        /// @param is_collaborative New collaborative state (optional)
        /// @note Requires @c playlist-modify-private scope
        /// @note Requires @c playlist-modify-public scope
        void changePlaylistDetails(
            const std::string& playlist_id,
            const std::optional<std::string>& name = std::nullopt,
            const std::optional<bool>& is_public = std::nullopt,
            const std::optional<std::string>& description = std::nullopt,
            const std::optional<bool>& is_collaborative = std::nullopt
        ) const;

        /// Overwrite existing playlist items with new ones
        /// @param playlist_id Spotify playlist ID
        /// @param uris Vector of new items URIs
        /// @note Requires @c playlist-modify-private scope
        /// @note Requires @c playlist-modify-public scope
        void replacePlaylistItems(
            const std::string& playlist_id,
            const std::vector<std::string>& uris
        ) const;


        /// Reorders items within a playlist.
        /// @param playlist_id Spotify playlist ID
        /// @param range_start Index of the first item to move
        /// @param insert_before Index to insert the items before
        /// @param range_length Number of items to move (optional)
        /// @param snapshot_id Playlist snapshot ID to target a specific version (optional)
        /// @note Requires @c playlist-modify-private scope
        /// @note Requires @c playlist-modify-public scope
        void reorderPlaylistItems(
            const std::string& playlist_id,
            const int& range_start,
            const int& insert_before,
            const std::optional<int>& range_length = std::nullopt,
            const std::optional<std::string>& snapshot_id = std::nullopt
        ) const;

        /// Upload a custom playlist cover
        /// @param playlist_id Spotify playlist ID
        /// @param image_path Either a local file path or url to an image
        /// @note Requires @c playlist-modify-private scope
        /// @note Requires @c playlist-modify-public scope
        /// @note Requires @c ugc-image-upload scope
        void addCustomPlaylistCover(
            const std::string& playlist_id,
            const std::string& image_path
        ) const;

        // POST
        /// Adds items to a Spotify playlist
        /// @param playlist_id Spotify playlist ID
        /// @param uris Vector of new items URIs
        /// @param position Start point for new items (optional)
        /// @note Requires @c playlist-modify-private scope
        /// @note Requires @c playlist-modify-public scope
        void addItemsToPlaylist(
            const std::string& playlist_id,
            const std::vector<std::string>& uris,
            const std::optional<int>& position = std::nullopt
        ) const;

        /// Creates a new playlist for a Spotify user
        /// @param user_id Spotify user ID
        /// @param name New playlist's name
        /// @param is_public New playlist's public state (optional)
        /// @param is_collaborative New playlist's collaborative state (optional)
        /// @param description New playlist's description (optional)
        /// @note Requires @c playlist-modify-private scope
        /// @note Requires @c playlist-modify-public scope
        /// @return Can return the new PlaylistObject if needed
        [[nodiscard]] std::optional<PlaylistObject> createPlaylist(
            const std::string& user_id,
            const std::string& name,
            const std::optional<bool>& is_public = std::nullopt,
            const std::optional<bool>& is_collaborative = std::nullopt,
            const std::optional<std::string>& description = std::nullopt
        ) const;

        // DELETE
        /// Removes items from a Spotify playlist
        /// @param playlist_id Spotify playlist ID
        /// @param tracks Vector URIObjects to remove
        /// @param snapshot_id Playlist snapshot ID to target a specific version (optional)
        /// @note Requires @c playlist-modify-private scope
        /// @note Requires @c playlist-modify-public scope
        void removePlaylistItems(
            const std::string& playlist_id,
            const std::vector<URIObject>& tracks,
            const std::optional<std::string>& snapshot_id = std::nullopt
        ) const;
    };
}

#endif //PLAYLISTAPI_H
