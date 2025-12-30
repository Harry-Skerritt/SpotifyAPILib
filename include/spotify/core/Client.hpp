//
// Created by Harry Skerritt on 21/12/2025.
//

#ifndef CLIENT_H
#define CLIENT_H

#pragma once
#include <string>

namespace Spotify {

    class Auth;

    class AlbumAPI;
    class ArtistAPI;
    class AudiobookAPI;
    class BrowseAPI;
    class CategoryAPI;
    class ChapterAPI;
    class EpisodeAPI;
    class PlayerAPI;
    class PlaylistAPI;
    class ShowsAPI;
    class TrackAPI;
    class UsersAPI;

    /// @brief Main Spotify client class. Provides access to all API endpoints.
    class Client {
    // Funcs
    public:
        explicit Client(Auth& auth);
        ~Client() = default;

        [[nodiscard]] std::string getAccessToken() const;

        ///@brief Access the album endpoints
        AlbumAPI album();

        ///@brief Access the artist endpoints
        ArtistAPI artist();

        ///@brief Access the audiobook endpoints
        AudiobookAPI audiobook();

        ///@brief Access the search and market endpoints
        BrowseAPI browse();

        ///@brief Access the category endpoints
        CategoryAPI category();

        ///@brief Access the chapter endpoints
        ChapterAPI chapter();

        ///@brief Access the episode endpoints
        EpisodeAPI episode();

        ///@brief Access the player endpoints
        PlayerAPI player();

        ///@brief Access the playlist endpoints
        PlaylistAPI playlist();

        ///@brief Access the show (podcast) endpoints
        ShowsAPI shows();

        ///@brief Access the track endpoints
        TrackAPI track();

        ///@brief Access the user endpoints
        UsersAPI users();


    // Vars
    private:
        Auth& m_auth;

    };

}



#endif //CLIENT_H
