//
// Created by Harry Skerritt on 18/12/2025.
//

#include <spotify/Auth.hpp>
#include <cstdlib>
#include <fstream>


void loadEnv(const std::string& filename = ".env") {
    std::ifstream file(filename);
    if (!file.is_open()) return;

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        auto pos = line.find('=');
        if (pos == std::string::npos) continue;

        std::string key = line.substr(0, pos);
        std::string value = line.substr(pos + 1);

        setenv(key.c_str(), value.c_str(), 1); // overwrite if exists
    }
}

int main() {

    loadEnv("/Volumes/Data/Code/C++/2025/SpotifyAPILib/.env");
    const char* client_key = std::getenv("SPOTIFY_CLIENT_KEY");
    const char* client_secret = std::getenv("SPOTIFY_CLIENT_SECRET");

    if (!client_key || !client_secret) {
        std::cerr << "Failed to get environment variables" << std::endl;
        return 1;
    }

    Spotify::Auth client({client_key, client_secret});
    client.authenticateClient();

    return 0;
}