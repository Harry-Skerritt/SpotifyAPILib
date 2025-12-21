//
// Created by Harry Skerritt on 21/12/2025.
//

#ifndef ALBUMAPI_H
#define ALBUMAPI_H

#pragma once
#include <string>
#include <optional>
#include <iostream>
#include "spotify/util/Types.h"
#include "spotify/util/JsonMapping.hpp"

namespace Spotify {

    class Client;

    class AlbumAPI {
    // Funcs
    public:

        explicit AlbumAPI(Client* client);

        // GET
        [[nodiscard]] std::optional<AlbumObject> getAlbum(const std::string &id, std::optional<std::string> market = std::nullopt) const;
        [[nodiscard]] std::optional<AlbumListObject> getMultipleAlbums(const std::vector<std::string>& ids, std::optional<std::string> market = std::nullopt) const;
        [[nodiscard]] std::optional<PagedTrackObject> getAlbumTracks(const std::string& id, std::optional<std::string> market = std::nullopt,
            std::optional<int> limit  = std::nullopt, std::optional<int> offset = std::nullopt) const; // Todo: Check return type
        [[nodiscard]] std::optional<PagedAlbumObject> getUsersSavedAlbums(std::optional<int> limit = std::nullopt, std::optional<int> offset = std::nullopt, std::optional<std::string> market = std::nullopt) const; // Todo: Check return type
        [[nodiscard]] std::optional<std::vector<bool>> checkUsersSavedAlbums(std::vector<std::string> ids) const;
        [[nodiscard]] std::optional<PagedAlbumObject> getNewReleases(std::optional<int> limit = std::nullopt, std::optional<int> offset = std::nullopt);


        // PUT
        void SaveAlbumsForUser(std::vector<std::string> ids) const;

        // DELETE
        void RemoveUsersSavedAlbums(std::vector<std::string> ids) const;


    private:
        [[nodiscard]] std::string tryGetAccessToken() const;

    // Vars
    public:
    private:
        Client* m_client;

        const std::string BASE_ALBUM_URL = "https://api.spotify.com/v1/albums";
        const std::string BASE_ALBUM_USER_URL = "https://api.spotify.com/v1/me/albums";
        const std::string BASE_BROWSE_URL = "https://api.spotify.com/v1/browse";




    };

}

#endif //ALBUMAPI_H
