//
// Created by Harry Skerritt on 22/12/2025.
//

#include <spotify/spotify.hpp>
#include "../ExampleUtils.hpp"

int main () {

    // This will save the input album to the users 'Your Music' library

    auto auth = Spotify::ExampleUtils::authenticateFromEnv();
    Spotify::Client client(auth);


    std::vector<std::string> album_ids = {"125bv7EBFzsaqeW2LzY6QP"};

    client.album().saveAlbumsForUser(album_ids);

    std::cout << "Saved Album! - Checking..." << std::endl;

    // This tests the check endpoint
    auto check = client.album().checkUsersSavedAlbums(album_ids);

    int i = 1;
    if (check.has_value()) {
        for (auto c : check.value()) {
            if (c) {
                std::cout << "Album " << i << " present!";
            } else {
                std::cout << "Album " << i << " not present!";
            }
            i++;
        }
    }

    return 0;
}