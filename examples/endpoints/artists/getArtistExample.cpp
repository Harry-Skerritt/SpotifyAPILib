//
// Created by Harry Skerritt on 22/12/2025.
//
#include <spotify/spotify.hpp>
#include "../ExampleUtils.hpp"

int main () {

    // This will display info about a single artist from an id, and multiple artists from a set of ids

    auto auth = Spotify::ExampleUtils::authenticateFromEnv();
    Spotify::Client client(auth);


    // Single Album
    std::string artist_id = "1nwPEi1UZdJtCxBqATpsq3";
    auto single_artist = client.artist().getArtist(artist_id);

    if (single_artist.has_value()) {
        std::cout << "      * Single Artist *     " << std::endl;
        std::cout << "----------------------------" << std::endl;
        std::cout << "Artist Name: " << single_artist->name << std::endl;
        std::cout << "Total Followers: " << single_artist->followers.total << std::endl;
        std::cout << "Artist Image: " << single_artist->images.at(0).url << std::endl;
        std::cout << "Album Popularity: " << single_artist->popularity << std::endl;
    }


    std::vector<std::string> artist_ids { "6p2HnfM955TI1bX34dkLnI", "5SHQUMAmEK5KmuSb0aDvsn", "3KrgUUwoRQ6OQp4IOmqnSF" };
    auto multi_artist = client.artist().getMultipleArtists(artist_ids);

    if (multi_artist.has_value()) {
        std::cout << "\n\n      * Multi Artists *      " << std::endl;
        std::cout << "---------------------------" << std::endl;

        int i = 1;
        for (auto artist : multi_artist->artists) {
            std::cout << "\n\n Artist: " << i << "/" << multi_artist->artists.size() << std::endl;
            std::cout << "---------------------------" << std::endl;
            std::cout << "Artist Name: " << artist.name << std::endl;
            std::cout << "Total Followers: " << artist.followers.total << std::endl;
            std::cout << "Artist Image: " << artist.images.at(0).url << std::endl;
            std::cout << "Album Popularity: " << artist.popularity << std::endl;
            i++;
        }
    }

    return 0;
}