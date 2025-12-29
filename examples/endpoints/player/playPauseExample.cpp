//
// Created by Harry Skerritt on 22/12/2025.
//

#include <thread>
#include <chrono>

#include <spotify/spotify.hpp>
#include "../ExampleUtils.hpp"

#include <cstdlib>

int main () {

    // This will pause the playback, wait 5 seconds, and result the playback

    auto auth = Spotify::ExampleUtils::authenticateFromEnv();
    Spotify::Client client(auth);

    std::cout << "Pausing Playback!" << std::endl;
    client.player().pausePlayback();

    std::cout << "Waiting..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(5));

    std::cout << "Resuming Playback!" << std::endl;
    client.player().startPlayback();

    return 0;
}