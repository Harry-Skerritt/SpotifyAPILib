//
// Created by Harry Skerritt on 01/01/2026.
//

#include <spotify/spotify.hpp>

using namespace Spotify;

int main() {

    // Load Client Key and Secret from .env file
    // Either replace the path below with a path to your .env or hardcode the values to client_key and client_secret
    // Note: Make sure to keep your keys safe!
    std::string env_path = "/Volumes/Data/Code/C++/2025/SpotifyAPILib/.env";
    Tools::loadEnv(env_path);

    const char* client_key = std::getenv("SPOTIFY_CLIENT_KEY");
    const char* client_secret = std::getenv("SPOTIFY_CLIENT_SECRET");

    // Handle keys being absent
    if (!client_key || !client_secret) {
        throw std::runtime_error("SPOTIFY_CLIENT_KEY or SECRET not found in environment.");
    }

    try {
        // Create the authentication object
        Auth auth({client_key, client_secret});


        // Generate the authorisation url - Replace the redirectUri with the one for your spotify app
        auto url = auth.createAuthoriseURL(
            "http://127.0.0.1:8888/callback",
            { Scope::UserReadPlaybackState }
        );


        // Open the URL and authenticate
        AuthServer::openBrowser(url);

        // Automatically handle the code coming in to the redirectURI
        std::string code = AuthServer::waitForCode("127.0.0.1", 8888);

        // Exchange the code for an authentication token
        // This may throw APIException, NetworkException, or LogicException

        auth.exchangeCode(code);

        // Fully authenticated client, ready to make API calls
        Client client(auth);

    }
    catch (const Exception& e) {
        std::cerr << "Authentication failed: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}