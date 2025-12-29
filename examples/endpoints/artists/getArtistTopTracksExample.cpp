//
// Created by Harry Skerritt on 22/12/2025.
//
#include <spotify/spotify.hpp>
#include "../ExampleUtils.hpp"

int main () {

    // This will display the top tracks of the entered artist

    auto auth = Spotify::ExampleUtils::authenticateFromEnv();
    Spotify::Client client(auth);



    std::string artist_id = "2xShSStof9kwGk4iVTgNnp";
    auto top_tracks = client.artist().getArtistTopTracks(artist_id);

    // Get artist name:
    std::string artist_name;
    auto artist = client.artist().getArtist(artist_id);
    if (artist.has_value()) artist_name = artist->name;


    if (top_tracks.has_value()) {

        std::cout << "\n\n" << artist_name << " - Top Tracks" << std::endl;
        std::cout << "----------------------------" << std::endl;


        int i = 1;
        for (const auto& track : top_tracks->tracks) {
            std::cout << "\n\n Track: " << i << "/" << top_tracks->tracks.size() << std::endl;
            std::cout << "---------------------------" << std::endl;
            std::cout << "Track Name: " << track.name << std::endl;
            std::cout << "Track Album: " << track.album.name << std::endl;
            std::cout << "Track Length: " << track.duration_ms << "ms" << std::endl;
            std::cout << "Is Explicit? " << (track.is_explicit ? "Yes" : "No") << std::endl;
            i++;
        }
    }

    return 0;
}