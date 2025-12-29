//
// Created by Harry Skerritt on 21/12/2025.
//

#include <spotify/spotify.hpp>
#include "../ExampleUtils.hpp"

#include <cstdlib>


int main () {

    // This will show the current track and some info about it in the conosle

    auto auth = Spotify::ExampleUtils::authenticateFromEnv();
    Spotify::Client client(auth);

    auto pb = client.player().getCurrentlyPlayingTrack();


    if (!pb.has_value()) {
        std::cout << "Nothing is playing (or private session is active)." << std::endl;
        return 0;
    }

    if (pb->asTrack() != nullptr) {
        auto track = pb->asTrack();
        auto album_cover = track->album.images.at(0);

        std::cout << "\n\n    * Currently Playing *    " << std::endl;
        std::cout << "-----------------------------" << std::endl;
        std::cout << track->name << " by " << track->artists.at(0).name << std::endl;
        std::cout << pb->progress_ms << "ms / " << track->duration_ms << "ms" << std::endl;
        std::cout << "(" << album_cover.height.value_or(0) << "x" << album_cover.width.value_or(0) << "): "
                    << album_cover.url << std::endl;
    }




    return 0;
}