//
// Created by Harry Skerritt on 28/12/2025.
//

#ifndef ENDPOINTS_HPP
#define ENDPOINTS_HPP

#include <string>

namespace Spotify::Endpoints {

    // Auth Endpoints
    inline const std::string AUTHORISE = "https://accounts.spotify.com/authorize";
    inline const std::string TOKEN = "https://accounts.spotify.com/api/token";


    // --- Base API ---
    inline const std::string API_V1 = "https://api.spotify.com/v1";

    // --- Albums ---
    inline const std::string ALBUMS = API_V1 + "/albums";
    inline const std::string MY_ALBUMS = API_V1 + "/me/albums";

    // --- Artists ---
    inline const std::string ARTISTS = API_V1 + "/artists";

    // --- Audiobooks ---
    inline const std::string AUDIOBOOKS = API_V1 + "/audiobooks";
    inline const std::string MY_AUDIOBOOKS = API_V1 + "/me/audiobooks";

    // --- Browse ---
    inline const std::string BROWSE = API_V1 + "/browse";
    inline const std::string CATEGORIES = BROWSE + "/categories";

    // --- Chapters ---
    inline const std::string CHAPTERS = API_V1 + "/chapters";

    // --- Episodes ---
    inline const std::string EPISODES = API_V1 + "/episodes";
    inline const std::string MY_EPISODES = API_V1 + "/me/episodes";

    // --- Player ---
    inline const std::string PLAYER = API_V1 + "/me/player";

    // --- Playlist ---
    inline const std::string PLAYLISTS = API_V1 + "/playlists";
    inline const std::string MY_PLAYLISTS = API_V1 + "/me/playlists";

    // --- Shows ---
    inline const std::string SHOWS = API_V1 + "/shows";
    inline const std::string MY_SHOWS = API_V1 + "/me/shows";

    // --- Track ---
    inline const std::string TRACKS = API_V1 + "/tracks";
    inline const std::string MY_TRACKS = API_V1 + "/me/tracks";

    // --- Users ---
    inline const std::string ME = API_V1 + "/me";
    inline const std::string USERS = API_V1 + "/users";











}

#endif //ENDPOINTS_HPP
