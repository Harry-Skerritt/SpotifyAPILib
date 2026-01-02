# --- Helper Function ---
function(set_example_output_dir TARGET_NAME CATEGORY SUBFOLDER)
    set_target_properties(${TARGET_NAME} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/examples/${CATEGORY}/${SUBFOLDER}")
endfunction()

# --- Macro to reduce boilerplate ---
macro(add_spotify_example TARGET_NAME SRC_PATH CATEGORY SUBFOLDER)
    add_executable(${TARGET_NAME} ${SRC_PATH})
    target_link_libraries(${TARGET_NAME} PRIVATE SpotifyCPP)
    set_example_output_dir(${TARGET_NAME} ${CATEGORY} ${SUBFOLDER})
endmacro()

# --- Real World Examples ---
add_spotify_example(example_authentication "realworld/authenticate.cpp" "realworld" "authenticate")
add_spotify_example(example_nowPlaying "realworld/now_playing.cpp" "realworld" "now_playing")
add_spotify_example(example_topItems "realworld/top_items.cpp" "realworld" "top_items")
add_spotify_example(example_Search "realworld/search.cpp" "realworld" "search")
add_spotify_example(example_PlaybackControl "realworld/playback_control.cpp" "realworld" "playback_control")
add_spotify_example(example_topTracksPlaylist "realworld/playlist_management.cpp" "realworld" "top_tracks_playlist")


# --- Endpoint Examples ---
# --- Auth Examples ---
add_spotify_example(example_authManual "endpoints/auth/authManualExample.cpp" "endpoints" "auth")
add_spotify_example(example_authServer "endpoints/auth/authServerExample.cpp" "endpoints" "auth")

configure_file(
        "endpoints/auth/index.html"
        "${CMAKE_BINARY_DIR}/examples/endpoints/auth/index.html"
        COPYONLY
)

# --- Album Examples ---
add_spotify_example(example_getAlbums "endpoints/albums/getAlbumExample.cpp" "endpoints" "albums")
add_spotify_example(example_getAlbumTracks "endpoints/albums/getAlbumTracksExample.cpp" "endpoints" "albums")
add_spotify_example(example_getUserAlbums "endpoints/albums/getUserAlbumsExample.cpp" "endpoints" "albums")
add_spotify_example(example_saveUserAlbums "endpoints/albums/saveAlbumForUserExample.cpp" "endpoints" "albums")
add_spotify_example(example_deleteUserAlbums "endpoints/albums/removeAlbumForUserExample.cpp" "endpoints" "albums")
add_spotify_example(example_newReleases "endpoints/albums/newReleaseExample.cpp" "endpoints" "albums")

# --- Artist Examples ---
add_spotify_example(example_getArtists "endpoints/artists/getArtistExample.cpp" "endpoints" "artists")
add_spotify_example(example_getArtistsAlbums "endpoints/artists/getArtistsAlbumsExample.cpp" "endpoints" "artists")
add_spotify_example(example_getArtistTopTracks "endpoints/artists/getArtistTopTracksExample.cpp" "endpoints" "artists")


# --- Audiobook Examples ---
add_spotify_example(example_getAudiobook "endpoints/audiobooks/getAudiobookExample.cpp" "endpoints" "audiobooks")
add_spotify_example(example_getAudiobookChapters "endpoints/audiobooks/getAudiobookChapters.cpp" "endpoints" "audiobooks")
add_spotify_example(example_getUserAudiobooks "endpoints/audiobooks/getUserAudiobooksExample.cpp" "endpoints" "audiobooks")
add_spotify_example(example_saveUserAudiobook "endpoints/audiobooks/saveAudiobookForUser.cpp" "endpoints" "audiobooks")
add_spotify_example(example_deleteUserAudiobook "endpoints/audiobooks/removeAudiobookForUser.cpp" "endpoints" "audiobooks")

# --- Browse Examples ---
add_spotify_example(example_getAvailableMarkets "endpoints/browse/getAvailableMarketsExample.cpp" "endpoints" "browse")
add_spotify_example(example_SearchEndpoint "endpoints/browse/searchExample.cpp" "endpoints" "browse")

# --- Category Examples ---
add_spotify_example(example_getSingleCategory "endpoints/categories/getSingleCategoryExample.cpp" "endpoints" "categories")
add_spotify_example(example_getMultiCategory "endpoints/categories/getMultipleCategoriesExample.cpp" "endpoints" "categories")

# --- Chapter Examples ---
add_spotify_example(example_getSingleChapter "endpoints/chapters/getSingleChapterExample.cpp" "endpoints" "chapters")
add_spotify_example(example_getMultiChapter "endpoints/chapters/getMultipleChaptersExample.cpp" "endpoints" "chapters")

# --- Episode Examples ---
add_spotify_example(example_getEpisodes "endpoints/episodes/getEpisodeExample.cpp" "endpoints" "episodes")
add_spotify_example(example_getUsersEpisodes "endpoints/episodes/getUserEpisodesExample.cpp" "endpoints" "episodes")
add_spotify_example(example_saveUserEpisode "endpoints/episodes/saveEpisodeForUserExample.cpp" "endpoints" "episodes")
add_spotify_example(example_deleteUserEpisode "endpoints/episodes/removeEpisodeForUserExample.cpp" "endpoints" "episodes")

# --- Player Examples ---
add_spotify_example(example_getPlaybackState "endpoints/player/getPlaybackStateExample.cpp" "endpoints" "player")
add_spotify_example(example_transferPlayback "endpoints/player/transferPlaybackExample.cpp" "endpoints" "player")
add_spotify_example(example_getDevices "endpoints/player/getDevicesExample.cpp" "endpoints" "player")
add_spotify_example(example_getCurrentlyPlaying "endpoints/player/getCurrentTrackExample.cpp" "endpoints" "player")
add_spotify_example(example_playPause "endpoints/player/playPauseExample.cpp" "endpoints" "player")
add_spotify_example(example_getRecentlyPlayed "endpoints/player/getRecentlyPlayedExample.cpp" "endpoints" "player")
add_spotify_example(example_getUserQueue "endpoints/player/getUserQueueExample.cpp" "endpoints" "player")
add_spotify_example(example_addToQueue "endpoints/player/addToQueueExample.cpp" "endpoints" "player")

# --- Playlist Examples ---
add_spotify_example(example_getPlaylist "endpoints/playlists/getPlaylistExample.cpp" "endpoints" "playlist")
add_spotify_example(example_createAndManipulate "endpoints/playlists/createAndManipulatePlaylistExample.cpp" "endpoints" "playlist")
add_spotify_example(example_getCurrentUsersPlaylist "endpoints/playlists/getCurrentUsersPlaylistsExample.cpp" "endpoints" "playlist")
add_spotify_example(example_getUsersPlaylist "endpoints/playlists/getUsersPlaylistsExample.cpp" "endpoints" "playlist")
add_spotify_example(example_getPlaylistItems "endpoints/playlists/getPlaylistItemsExamples.cpp" "endpoints" "playlist")
add_spotify_example(example_getPlaylistCover "endpoints/playlists/getPlaylistCoverExample.cpp" "endpoints" "playlist")

# --- Track Examples ---
add_spotify_example(example_getTrack "endpoints/tracks/getTrackExample.cpp" "endpoints" "tracks")
add_spotify_example(example_getUserTracks "endpoints/tracks/getUserTracksExample.cpp" "endpoints" "tracks")
add_spotify_example(example_saveUserTracks "endpoints/tracks/saveTrackForUserExample.cpp" "endpoints" "tracks")
add_spotify_example(example_deleteUserTracks "endpoints/tracks/removeTrackForUserExample.cpp" "endpoints" "tracks")

# --- Users Examples ---
add_spotify_example(example_getCurrentUser "endpoints/users/getCurrentUserExample.cpp" "endpoints" "users")
add_spotify_example(example_getUsersTopItems "endpoints/users/getUsersTopItemsExample.cpp" "endpoints" "users")
add_spotify_example(example_followUnfollowArtistsAndUsers "endpoints/users/followArtistsAndUsersExample.cpp" "endpoints" "users")
add_spotify_example(example_getFollowedArtists "endpoints/users/getFollowedArtistExample.cpp" "endpoints" "users")