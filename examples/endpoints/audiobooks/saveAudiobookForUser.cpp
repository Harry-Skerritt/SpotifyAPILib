//
// Created by Harry Skerritt on 22/12/2025.
//

#include <spotify/spotify.hpp>
#include "../ExampleUtils.hpp"

int main () {

    // This will save the input album to the users 'Your Music' library

    auto auth = Spotify::ExampleUtils::authenticateFromEnv();
    Spotify::Client client(auth);


    std::vector<std::string> audiobook_ids = {"2CuUBkbEhsiy67oAMl3MOE"};

    client.audiobook().saveAudiobookForUser(audiobook_ids);

    std::cout << "Saved Audiobook! - Checking" << std::endl;

    // This tests the check endpoint
    auto check = client.audiobook().checkUsersSavedAudiobooks(audiobook_ids);

    int i = 1;
    if (check.has_value()) {
        for (auto c : check.value()) {
            if (c) {
                std::cout << "Audiobook " << i << " present!";
            } else {
                std::cout << "Audiobook " << i << " not present!";
            }
            i++;
        }
    }

    return 0;
}