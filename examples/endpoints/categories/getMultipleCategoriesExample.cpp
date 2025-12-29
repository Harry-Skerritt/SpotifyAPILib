//
// Created by Harry Skerritt on 22/12/2025.
//

#include <spotify/spotify.hpp>
#include "../ExampleUtils.hpp"


int main () {

    // This will display info about multiple browse categories

    auto auth = Spotify::ExampleUtils::authenticateFromEnv();
    Spotify::Client client(auth);

    auto multi_categories = client.category().getMultipleBrowseCategories(std::nullopt, 50);

    if (multi_categories.has_value()) {
        std::cout << "\n\n      * Browse Categories *      " << std::endl;
        std::cout << "---------------------------------" << std::endl;

        for (auto category : multi_categories->items) {
            std::cout << "\n\n     * " << category.name << " *      " << std::endl;
            std::cout << "---------------------------" << std::endl;
            std::cout << "Image: " << category.icons.at(0).url << std::endl;
            std::cout << "href: " << category.href << std::endl;
            std::cout << "Id: " << category.id << std::endl;
        }
    }

    return 0;
}
