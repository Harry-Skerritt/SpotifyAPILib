//
// Created by Harry Skerritt on 21/12/2025.
//
#include <spotify/spotify.hpp>
#include "../ExampleUtils.hpp"


int main () {

    // This will display the track listing of an album, from the album id
    auto auth = Spotify::ExampleUtils::authenticateFromEnv();
    Spotify::Client client(auth);


    std::string album_id = "2EruEBw8awLTVzwhSd4yqt";
    auto album_tracks = client.album().getAlbumTracks(album_id);

    if (album_tracks.has_value()) {
        std::cout << "\n\n     * Total Tracks *     " << std::endl;
        std::cout << "----------- " << album_tracks->total << " -----------" << std::endl;

        for (auto track : album_tracks->items) {
            std::cout << "\n\n Track: " << track.track_number << "/" << album_tracks->total << std::endl;
            std::cout << "---------------------------" << std::endl;
            std::cout << "Song Name: " << track.name << std::endl;
            std::cout << "Artist: " << track.artists.at(0).name << std::endl;
            std::cout << "Is Explicit: " << track.is_explicit << std::endl;
            std::cout << "Track ID: " << track.id << std::endl;
        }
    }


    return 0;
}