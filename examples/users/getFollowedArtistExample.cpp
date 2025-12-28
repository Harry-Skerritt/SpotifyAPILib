//
// Created by Harry Skerritt on 28/12/2025.
//

#include <spotify/spotify.hpp>
#include "../ExampleUtils.hpp"

int main () {

    // This will display the current users top artists and tracks
    auto auth = Spotify::ExampleUtils::authenticateFromEnv();
    Spotify::Client client(auth);


    // Artist
    auto followed_artists = client.users().getFollowedArtists();
    if (followed_artists.has_value()) {

        std::cout << " * Followed Artists * " << std::endl;
        std::cout << "----------------------" << std::endl;

        int i = 1;
        for (const auto& artist : followed_artists->items) {
            std::cout << i << ": " << artist.name << std::endl;
            i++;
        }
    }




    return 0;
}