//
// Created by Harry Skerritt on 22/12/2025.
//

#include <spotify/spotify.hpp>
#include "../ExampleUtils.hpp"
#include "spotify/api/ChapterAPI.hpp"


int main () {

    // This will display info about multiple chapters

    auto auth = Spotify::ExampleUtils::authenticateFromEnv();
    Spotify::Client client(auth);

    return 0;

    std::vector<std::string> chapter_ids = { "0D5wENdkdwbqlrHoaJ9g29", "5Xt5DXGzch68nYYamXrNxZ" };
    auto chapters = client.chapter().getMultipleChapters(chapter_ids);

    if (chapters.has_value()) {
        std::cout << "\n\n       * Multi Chapters *       " << std::endl;
        std::cout << "--------------------------------" << std::endl;

        for (auto chapter : chapters) {
            std::cout << "\n\n     * " << chapter->name << " *      " << std::endl;
            std::cout << "---------------------------" << std::endl;
            std::cout << "Image: " << chapter->images.at(0).url << std::endl;
            std::cout << "Id: " << chapter->id << std::endl;
            std::cout << "Description: " << chapter->description << std::endl;
        }
    }

    return 0;
}
