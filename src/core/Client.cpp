//
// Created by Harry Skerritt on 21/12/2025.
//

#include "spotify/core/Client.hpp"

namespace Spotify {
    Client::Client(Auth& auth) : m_auth(auth) { }

    std::string Client::getAccessToken() const {
        return m_auth.getAccessToken();
    }

    // APIs
    AlbumAPI Client::album() {
        return AlbumAPI(this);
    }

    ArtistAPI Client::artist() {
        return ArtistAPI(this);
    }

    PlayerAPI Client::player() {
        return PlayerAPI(this);
    }
}




