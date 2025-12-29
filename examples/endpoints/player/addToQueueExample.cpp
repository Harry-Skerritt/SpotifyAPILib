//
// Created by Harry Skerritt on 22/12/2025.
//


#include <spotify/spotify.hpp>
#include "../ExampleUtils.hpp"

int main () {

    // This will add a track to the users queue

    auto auth = Spotify::ExampleUtils::authenticateFromEnv();
    Spotify::Client client(auth);

    std::string track_id = "spotify:track:36KCt9jFNaENQ11idHTDyp";
    client.player().addItemToQueue(track_id);

    std::cout << "Added track to queue!" << std::endl;

    return 0;




}