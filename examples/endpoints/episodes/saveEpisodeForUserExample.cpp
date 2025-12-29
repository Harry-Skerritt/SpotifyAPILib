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

    int i = 1;
    if (check.has_value()) {
        for (auto c : check.value()) {
            if (c) {
                std::cout << "Episode " << i << " present!";
            } else {
                std::cout << "Episode " << i << " not present!";
            }
            i++;
        }
    }


    return 0;
}