//
// Created by Harry Skerritt on 22/12/2025.
//

#include <spotify/spotify.hpp>
#include "../ExampleUtils.hpp"

int main () {

    // This will display info about a single browse category

    auto auth = Spotify::ExampleUtils::authenticateFromEnv();
    Spotify::Client client(auth);


    std::string category_id = "0JQ5DAt0tbjZptfcdMSKl3";
    auto single_category = client.category().getBrowseCategory(category_id);

    if (single_category.has_value()) {
        std::cout << "     * " << single_category->name << " *      " << std::endl;
        std::cout << "---------------------------" << std::endl;
        std::cout << "Image: " << single_category->icons.at(0).url << std::endl;
        std::cout << "href: " << single_category->href << std::endl;
        std::cout << "Id: " << single_category->id << std::endl;
    }

    return 0;
}