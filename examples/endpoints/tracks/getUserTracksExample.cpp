//
// Created by Harry Skerritt on 21/12/2025.
//
#include <spotify/spotify.hpp>
#include "../ExampleUtils.hpp"

int main () {

    // This will display info about the top X (5 in this case) of the users saved tracks

    auto auth = Spotify::ExampleUtils::authenticateFromEnv();
    Spotify::Client client(auth);

    auto user_tracks = client.track().getUserSavedTracks(std::nullopt, 5);

    if (user_tracks.has_value()) {
        std::cout << "\n\n  * Users Top: " << user_tracks->limit << " Tracks *  " << std::endl;
        std::cout << "----------------------------" << std::endl;

        int i = 1;
        for (const auto& saved_track : user_tracks->items) {
            auto track = saved_track.track;
            std::cout << "\n\n Track: " << i << "/" << user_tracks->limit << std::endl;
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