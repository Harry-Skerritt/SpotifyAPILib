//
// Created by Harry Skerritt on 22/12/2025.
//

#include <spotify/spotify.hpp>
#include "../ExampleUtils.hpp"

int main () {

    // This will save the input episode to the users library

    auto auth = Spotify::ExampleUtils::authenticateFromEnv();
    Spotify::Client client(auth);


    std::vector<std::string> episode_ids = {"4ERiEJNkcTttMOiQpIWPr7"};

    client.episode().saveEpisodeForUser(episode_ids);

    std::cout << "Saved Episode! - Checking..." << std::endl;

    // This tests the check endpoint

    auto check = client.episode().checkUsersSavedEpisodes(episode_ids);

    if (check.has_value()) {
        for (auto c : check.value()) {
            std::cout << c << std::endl;
        }
    }


    return 0;
}