//
// Created by Harry Skerritt on 28/12/2025.
//


#include <spotify/spotify.hpp>
#include "../ExampleUtils.hpp"

int main () {

    // This will follow and unfollow an artist and a user along with checking the check endpoint

    auto auth = Spotify::ExampleUtils::authenticateFromEnv();
    Spotify::Client client(auth);


    // Artist
    std::vector<std::string> artist_ids = { "2xShSStof9kwGk4iVTgNnp" };
    client.users().followArtist(artist_ids);
    std::cout << "Followed Artist!" << std::endl;

    // check
    auto follow_artist = client.users().checkUserFollowsArtists(artist_ids);
    if (follow_artist.has_value()) {
        int i = 1;
        for (auto artist : *follow_artist) {
            if (artist) {
                std::cout << "Artist " << i << " followed" << std::endl;
            } else {
                std::cout << "Artist " << i << " not followed" << std::endl;
            }
            i++;
        }
    }


    std::cout << "Unfollow Artist? (Y/n) :" << std::endl;
    std::string artist_unfollow_q;
    std::getline(std::cin, artist_unfollow_q);
    std::transform(artist_unfollow_q.begin(), artist_unfollow_q.end(), artist_unfollow_q.begin(),
    [](unsigned char c){ return std::tolower(c); });

    if (artist_unfollow_q == "y") {
        client.users().unfollowArtist(artist_ids);
    }

    // Users
    std::vector<std::string> user_ids = { "smedjan" };
    client.users().followUser(user_ids);

    // check
    auto follow_user = client.users().checkUserFollowsUsers(user_ids);
    if (follow_user.has_value()) {
        int i = 1;
        for (auto user : *follow_user) {
            if (user) {
                std::cout << "User " << i << " followed" << std::endl;
            } else {
                std::cout << "User " << i << " not followed" << std::endl;
            }
            i++;
        }
    }

    std::cout << "Unfollow User? (Y/n) :" << std::endl;
    std::string user_unfollow_q;
    std::getline(std::cin, user_unfollow_q);
    std::transform(user_unfollow_q.begin(), user_unfollow_q.end(), user_unfollow_q.begin(),
    [](unsigned char c){ return std::tolower(c); });

    if (user_unfollow_q == "y") {
        client.users().unfollowUser(user_ids);
    }


    return 0;
}