//
// Created by Harry Skerritt on 22/12/2025.
//



#include <spotify/spotify.hpp>
#include "../ExampleUtils.hpp"

#include <cstdlib>

int main () {

    // This will output the users recently played tracks up to the limit (10 in this case)

    auto auth = Spotify::ExampleUtils::authenticateFromEnv();
    Spotify::Client client(auth);

    auto recently_played = client.player().getRecentlyPlayedTracks(10);

    if (recently_played.has_value()) {
        std::cout << "\n\n     * Total Tracks *     " << std::endl;
        std::cout << "----------- " << recently_played->limit << " -----------" << std::endl;

        int i = 1;
        for (auto track : recently_played->items) {
            std::cout << "\n\n Track: " << i << "/" << recently_played->limit << std::endl;
            std::cout << "---------------------------" << std::endl;
            std::cout << "Song Name: " << track.track.name << std::endl;
            std::cout << "Song Artist: " << track.track.artists.at(0).name << std::endl;
            std::cout << "Song Album: " << track.track.album.name << std::endl;
            std::cout << "Song Played at: " << track.played_at << std::endl;
            i++;
        }
    }


    return 0;
}