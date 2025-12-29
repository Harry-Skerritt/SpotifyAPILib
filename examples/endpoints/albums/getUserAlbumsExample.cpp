//
// Created by Harry Skerritt on 21/12/2025.
//
#include <spotify/spotify.hpp>
#include "../ExampleUtils.hpp"

int main () {

    // This will display info about the top X (5 in this case) of the users saved albums

    auto auth = Spotify::ExampleUtils::authenticateFromEnv();
    Spotify::Client client(auth);

    auto user_albums = client.album().getUsersSavedAlbums(5);

    if (user_albums.has_value()) {
        std::cout << "\n\n  * Users Top: " << user_albums->limit << " Albums *  " << std::endl;
        std::cout << "----------------------------" << std::endl;

        int i = 1;
        for (const auto& saved_album : user_albums->items) {
            auto album = saved_album.album;
            std::cout << "\n\n Album: " << i << "/" << user_albums->limit << std::endl;
            std::cout << "---------------------------" << std::endl;
            std::cout << album.name << " by " << album.artists.at(0).name << std::endl;
            std::cout << "Released: " << album.release_date << std::endl;
            std::cout << "Track Count: " << album.total_tracks << std::endl;
            std::cout << "Added on: " << saved_album.added_at << std::endl;
            i++;
        }
    }


    return 0;
}