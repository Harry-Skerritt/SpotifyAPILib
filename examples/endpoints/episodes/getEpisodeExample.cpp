//
// Created by Harry Skerritt on 21/12/2025.
//
#include <spotify/spotify.hpp>
#include "../ExampleUtils.hpp"

int main () {

    // This will display info about a single episode from an id, and multiple episodes from a set of ids

    auto auth = Spotify::ExampleUtils::authenticateFromEnv();
    Spotify::Client client(auth);

    // Single Episode
    std::string episode_id = "6qkYUVrHxUn0AUWMy0exb4";
    auto single_episode = client.episode().getEpisode(episode_id);

    if (single_episode.has_value()) {
        std::cout << "\n\n       * Episode *        " << std::endl;
        std::cout << "--------------------------" << std::endl;
        std::cout << "Episode Title: " << single_episode->name << std::endl;
        std::cout << "From Show: " << single_episode->show.name << std::endl;
        std::cout << "Publisher: " << single_episode->show.publisher << std::endl;
        std::cout << "Description: " << single_episode->description << std::endl;
    }

    // Multi Album
    std::vector<std::string> episode_ids { "3LrTYwlBUcsyEu0f15DSf1", "3mYb3UPJkHtANLPu0PjTOh", "1haFghGQORCNCZB1a9yrEQ" };
    auto multi_episodes = client.episode().getMultipleEpisodes(episode_ids);

    if (multi_episodes.has_value()) {
        std::cout << "\n\n      * Multi Episodes *      " << std::endl;
        std::cout << "------------------------------" << std::endl;

        int i = 1;
        for (auto episode : multi_episodes->episodes) {
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