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

    class Client {
    // Funcs
    public:
        explicit Client(Auth& auth);
        ~Client() = default;

        [[nodiscard]] std::string getAccessToken() const;

        AlbumAPI album();
        ArtistAPI artist();
        AudiobookAPI audiobook();
        BrowseAPI browse();
        CategoryAPI category();
        ChapterAPI chapter();
        EpisodeAPI episode();
        PlayerAPI player();
        PlaylistAPI playlist();
        ShowsAPI shows();
        TrackAPI track();
        UsersAPI users();


    // Vars
    private:
        Auth& m_auth;

    };

}



#endif //CLIENT_H
