//
// Created by Harry Skerritt on 22/12/2025.
//
#include <spotify/spotify.hpp>
#include "../ExampleUtils.hpp"

int main () {

    // This will display the top albums of a selected type and amount

    auto auth = Spotify::ExampleUtils::authenticateFromEnv();
    Spotify::Client client(auth);


    // This will return ONLY albums and singles
    std::string artist_id = "1Qp56T7n950O3EGMsSl81D";
    std::vector<Spotify::IncludeGroups> include_groups = {Spotify::IncludeGroups::Album, Spotify::IncludeGroups::Single};
    auto albums = client.artist().getArtistsAlbums(artist_id, include_groups);

    // Get artist name:
    std::string artist_name;
    auto artist = client.artist().getArtist(artist_id);
    if (artist.has_value()) artist_name = artist->name;


    if (albums.has_value()) {

        std::cout << "\n\n" << artist_name << " - Albums" << std::endl;
        std::cout << "----------------------------" << std::endl;


        int i = 1;
        for (const auto& album : albums->items) {
            std::cout << "\n\n Album: " << i << "/" << albums->limit << std::endl;
            std::cout << "---------------------------" << std::endl;
            std::cout << "Album Name: " << album.name << std::endl;
            std::cout << "Release Date: " << album.release_date << std::endl;
            std::cout << "Album Type: " << album.album_type << std::endl;
            std::cout << "Track Count: " << album.total_tracks << std::endl;
            std::cout << "Album Art: " << album.images.at(0).url << std::endl;
            i++;
        }
    }

    return 0;
}