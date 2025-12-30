//
// Created by Harry Skerritt on 21/12/2025.
//

#ifndef SPOTIFY_HPP
#define SPOTIFY_HPP

#pragma once

#include "spotify/SpotifyVersion.hpp"

// API
#include "spotify/api/AlbumAPI.hpp"
#include "spotify/api/ArtistAPI.hpp"
#include "spotify/api/AudiobookAPI.hpp"
#include "spotify/api/BrowseAPI.hpp"
#include "spotify/api/CategoryAPI.hpp"
#include "spotify/api/ChapterAPI.hpp"
#include "spotify/api/EpisodeAPI.hpp"
#include "spotify/api/PlayerAPI.hpp"
#include "spotify/api/PlaylistAPI.hpp"
#include "spotify/api/ShowsAPI.hpp"
#include "spotify/api/TrackAPI.hpp"
#include "spotify/api/UsersAPI.hpp"

// Auth
#include "spotify/auth/Auth.hpp"
#include "spotify/auth/AuthServer.hpp"

// Core
#include "spotify/core/Client.hpp"
#include "spotify/core/Errors.hpp"


// Utils
#include "util/common/Tools.hpp"
#include "util/parse/SpotifyParser.hpp"
#include "models/Scopes.hpp"
#include "spotify/models/Types.hpp"

#endif //SPOTIFY_HPP
