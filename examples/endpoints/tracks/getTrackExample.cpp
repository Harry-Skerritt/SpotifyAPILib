//
// Created by Harry Skerritt on 21/12/2025.
//
#include <spotify/spotify.hpp>
#include "../ExampleUtils.hpp"

int main () {

    // This will display info about a single track from an id, and multiple tracks from a set of ids

    auto auth = Spotify::ExampleUtils::authenticateFromEnv();
    Spotify::Client client(auth);

    // Single Track
    std::string track_id = "3H6NMrKZOc4bpcQHVZf5Mc";
    auto single_track = client.track().getTrack(track_id);

    if (single_track.has_value()) {
        std::cout << "\n\n     * Single Track *      " << std::endl;
        std::cout << "---------------------------" << std::endl;
        std::cout << "Track Title: " << single_track->name << std::endl;
        std::cout << "Track Artist: " << single_track->artists.at(0).name << std::endl;
        std::cout << "Track Length: " << single_track->duration_ms << "ms" << std::endl;
        std::cout << "Track Cover: " << single_track->album.images.at(0).url << std::endl;
    }


    // Multi Tracks
    std::vector<std::string> track_ids { "6of9j8KsOn4Q2VuDYMvuqN", "046x8yuXjJFPaaQI6Iyz9e", "6zYdoGQaG0LwePeZdTWkg3" };
    auto multi_tracks = client.track().getTracks(track_ids);

    if (multi_tracks.has_value()) {
        std::cout << "\n\n      * Multi Tracks *      " << std::endl;
        std::cout << "---------------------------" << std::endl;

        int i = 1;
        for (auto track : multi_tracks->tracks) {
            std::cout << "\n\n Track: " << i << "/" << multi_tracks->tracks.size() << std::endl;
            std::cout << "---------------------------" << std::endl;
            std::cout << "Track Title: " << track.name << std::endl;
            std::cout << "Track Artist: " << track.artists.at(0).name << std::endl;
            std::cout << "Track Length: " << track.duration_ms << "ms" << std::endl;
            std::cout << "Track Cover: " << track.album.images.at(0).url << std::endl;
            i++;
        }
    }


    return 0;
}