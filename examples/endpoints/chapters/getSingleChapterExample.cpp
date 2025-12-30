//
// Created by Harry Skerritt on 22/12/2025.
//

#include <spotify/spotify.hpp>
#include "../ExampleUtils.hpp"
#include "spotify/api/ChapterAPI.hpp"

int main () {

    // This will display info about a single chapter

    auto auth = Spotify::ExampleUtils::authenticateFromEnv();
    Spotify::Client client(auth);


    std::string chapter_id = "0D5wENdkdwbqlrHoaJ9g29";
    auto chapter = client.chapter().getChapter(chapter_id);

    std::cout << "     * " << chapter.name << " *      " << std::endl;
    std::cout << "---------------------------" << std::endl;
    std::cout << "Image: " << chapter.images.at(0).url << std::endl;
    std::cout << "Id: " << chapter.id << std::endl;
    std::cout << "Description: " << chapter.description << std::endl;

    return 0;
}
