//
// Created by Harry Skerritt on 22/12/2025.
//

#include <spotify/spotify.hpp>
#include "../ExampleUtils.hpp"

int main () {

    // This will save the input track to the users 'Your Music' library

    auto auth = Spotify::ExampleUtils::authenticateFromEnv();
    Spotify::Client client(auth);

    // With id
    std::vector<std::string> track_ids = {"0RdUX4WE0fO30VnlUbDVL6"};

    client.track().saveTracksForUser(track_ids);

    std::cout << "Saved Track w/o timestamp!" << std::endl;

    // With Timestamp
    std::vector<Spotify::TimestampIDObject> timestamped_track_ids = { {"3ovjw5HZZv43SxTwApooCM", Spotify::Tools::getISOTimestamp()}};
    client.track().saveTracksForUser(timestamped_track_ids);

    std::cout << "Saved Track w/ timestamp!" << std::endl;


    // Testing the check endpoint
    std::cout << "Checking albums..." << std::endl;
    std::vector<std::string> check_ids = { "0RdUX4WE0fO30VnlUbDVL6", "3ovjw5HZZv43SxTwApooCM", "58dBJivB6lbAY5irCuAxJX" };
    auto check = client.track().checkUsersSavedTracks(check_ids);

    int i = 1;
    if (check.has_value()) {
        for (auto c : check.value()) {
            if (c) {
                std::cout << "Track " << i << " present!" << std::endl;
            } else {
                std::cout << "Track " << i << " not present!" << std::endl;
            }
            i++;
        }
    }

    return 0;
}