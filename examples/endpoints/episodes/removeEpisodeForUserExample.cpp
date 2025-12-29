//
// Created by Harry Skerritt on 22/12/2025.
//
#include <spotify/spotify.hpp>
#include "../ExampleUtils.hpp"

int main () {

    // This will remove the input episode from the users library

    auto auth = Spotify::ExampleUtils::authenticateFromEnv();
    Spotify::Client client(auth);


    std::vector<std::string> episode_ids = {"4ERiEJNkcTttMOiQpIWPr7"};

    client.episode().removeUserSavedEpisodes(episode_ids);

    std::cout << "Removed Episode!" << std::endl;

    return 0;
}