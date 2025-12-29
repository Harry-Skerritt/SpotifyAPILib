//
// Created by Harry Skerritt on 22/12/2025.
//
#include <spotify/spotify.hpp>
#include "../ExampleUtils.hpp"

int main () {

    // This will remove the input tracks from the users 'Your Music' library

    auto auth = Spotify::ExampleUtils::authenticateFromEnv();
    Spotify::Client client(auth);


    std::vector<std::string> track_ids = {"0RdUX4WE0fO30VnlUbDVL6", "3ovjw5HZZv43SxTwApooCM", };

    client.track().removeUsersSavedTracks(track_ids);

    std::cout << "Removed Tracks!" << std::endl;

    return 0;
}