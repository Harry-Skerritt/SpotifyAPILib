//
// Created by Harry Skerritt on 22/12/2025.
//

#include <spotify/spotify.hpp>
#include "../ExampleUtils.hpp"

int main () {

    // This will display the currently available devices in the console

    auto auth = Spotify::ExampleUtils::authenticateFromEnv();
    Spotify::Client client(auth);

    auto devices = client.player().getAvailableDevices();

    if (!devices.has_value()) {
        std::cerr << "No player found!" << std::endl;
        return 1;
    }

    std::cout << "   * " << devices->devices.size() << " Available Devices *   " << std::endl;
    std::cout << "-----------------------------" << std::endl;

    for (const auto& device : devices->devices) {
        std::cout << device.name << std::endl;
    }

    return 0;
}