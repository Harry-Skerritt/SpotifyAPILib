//
// Created by Harry Skerritt on 21/12/2025.
//

#include <spotify/spotify.hpp>
#include "../ExampleUtils.hpp"

int main () {

    // This will print the top 100 new releases to the console!

    auto auth = Spotify::ExampleUtils::authenticateFromEnv();
    Spotify::Client client(auth);

    int limit = 20;
    int offset = 0;
    bool has_more = true;

    while (has_more) {
        auto releases = client.album().getNewReleases(limit, offset);

        if (releases && !releases->items.empty()) {
            // 2. Calculate Page Numbers
            int currentPage = (offset / limit) + 1;
            int totalPages = std::ceil((float)releases->total / limit);

            std::cout << "\n< Page " << currentPage << "/" << totalPages << " >" << std::endl;
            std::cout << "--------------------------" << std::endl;

            for (size_t i = 0; i < releases->items.size(); ++i) {
                // Global index: (Page * Limit) + current item index
                int globalIndex = offset + i + 1;
                std::cout << globalIndex << ": " << releases->items[i].name << std::endl;
            }

            if (releases->next.has_value() && (offset + limit) < releases->total) {
                offset += limit;
            } else {
                has_more = false;
            }
        } else {
            has_more = false;
        }
    }


    return 0;
}