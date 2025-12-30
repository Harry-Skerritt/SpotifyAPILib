//
// Created by Harry Skerritt on 28/12/2025.
//
#include <spotify/spotify.hpp>
#include "../ExampleUtils.hpp"

int main () {

    // This will display info about the current user
    auto auth = Spotify::ExampleUtils::authenticateFromEnv();
    Spotify::Client client(auth);

    auto current_user = client.users().getCurrentUserProfile();

    std::cout << " * " << current_user.display_name << " * " << std::endl;
    std::cout << "--------------------" << std::endl;
    std::cout << "User Email: " << current_user.email << std::endl;
    std::cout << "User ID: " << current_user.id << std::endl;
    std::cout << "Follower Count: " << current_user.followers.total << std::endl;
    std::cout << "User Icon: " << current_user.images.at(0).url << std::endl;

    return 0;
}