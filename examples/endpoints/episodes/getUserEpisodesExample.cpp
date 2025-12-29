//
// Created by Harry Skerritt on 21/12/2025.
//
#include <spotify/spotify.hpp>
#include "../ExampleUtils.hpp"

int main () {

    // This will display info about the top X (5 in this case) of the users saved episodes

    auto auth = Spotify::ExampleUtils::authenticateFromEnv();
    Spotify::Client client(auth);

    auto user_episodes = client.episode().getUsersSavedEpisodes(std::nullopt, 5);

    if (user_episodes.has_value()) {
        std::cout << "\n\n  * Users Top: " << user_episodes->limit << " Episodes *  " << std::endl;
        std::cout << "-------------------------------" << std::endl;

        int i = 1;
        for (const auto& saved_episode : user_episodes->items) {
            auto episode = saved_episode.episode;
            std::cout << "\n\n       * Episode " << i << " *          " << std::endl;
            std::cout << "--------------------------" << std::endl;
            std::cout << "Episode Title: " << episode.name << std::endl;
            std::cout << "From Show: " << episode.show.name << std::endl;
            std::cout << "Publisher: " << episode.show.publisher << std::endl;
            std::cout << "Description: " << episode.description << std::endl;
            i++;
        }
    }


    return 0;
}