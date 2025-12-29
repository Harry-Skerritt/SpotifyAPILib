//
// Created by Harry Skerritt on 21/12/2025.
//
#include <spotify/spotify.hpp>
#include "../ExampleUtils.hpp"

int main () {

    // This will display info about a single album from an id, and multiple albums from a set of ids

    auto auth = Spotify::ExampleUtils::authenticateFromEnv();
    Spotify::Client client(auth);

    // Single Album
    std::string album_id = "1U3qu4gDfohAqFrmpLT11l";
    auto single_album = client.album().getAlbum(album_id);

    if (single_album.has_value()) {
        std::cout << "     * Single Album *      " << std::endl;
        std::cout << "---------------------------" << std::endl;
        std::cout << single_album->name << " by " << single_album->artists.at(0).name << std::endl;
        std::cout << "Released: " << single_album->release_date << std::endl;
        std::cout << "Track Count: " << single_album->total_tracks << std::endl;
        std::cout << "Album Popularity: " << single_album->popularity << std::endl;
    }

    // Multi Album
    std::vector<std::string> album_ids { "6TZp52tXShLQbq8yNMxqNT", "3kB4VjXKKCY7l5xeH113Da", "3YhgdRfaZrVIOORGK9SNiV" };
    auto multi_albums = client.album().getMultipleAlbums(album_ids);

    if (multi_albums.has_value()) {
        std::cout << "\n\n      * Multi Album *      " << std::endl;
        std::cout << "---------------------------" << std::endl;

        int i = 1;
        for (auto album : multi_albums->albums) {
            std::cout << "\n\n Album: " << i << "/" << multi_albums->albums.size() << std::endl;
            std::cout << "---------------------------" << std::endl;
            std::cout << album.name << " by " << album.artists.at(0).name << std::endl;
            std::cout << "Released: " << album.release_date << std::endl;
            std::cout << "Track Count: " << album.total_tracks << std::endl;
            std::cout << "Album Popularity: " << album.popularity << std::endl;
            i++;
        }
    }


    return 0;
}