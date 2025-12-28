//
// Created by Harry Skerritt on 28/12/2025.
//

#include <spotify/spotify.hpp>
#include "../ExampleUtils.hpp"

int main () {

    // This will display the current users top artists and tracks
    auto auth = Spotify::ExampleUtils::authenticateFromEnv();
    Spotify::Client client(auth);

    std::string time_scale = "short_term";

    // Artist
    auto top_artists = client.users().getUsersTopArtists(time_scale);
    if (top_artists.has_value()) {

        std::cout << " * Top Artists * " << std::endl;
        std::cout << "-----------------" << std::endl;

        int i = 1;
        for (auto artist : top_artists->items) {
            std::cout << i << ": " << artist.name << std::endl;
            i++;
        }
    }

    // Tracks
    auto top_tracks = client.users().getUsersTopTracks(time_scale);
    if (top_tracks.has_value()) {

        std::cout << "\n\n * Top Tracks * " << std::endl;
        std::cout << "-----------------" << std::endl;

        int i = 1;
        for (auto track : top_tracks->items) {
            std::cout << i << ": " << track.name << " - " << track.artists.at(0).name << std::endl;
            i++;
        }
    }


    return 0;
}