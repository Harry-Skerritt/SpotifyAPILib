//
// Created by Harry Skerritt on 01/01/2026.
//

#include <spotify/spotify.hpp>

using namespace Spotify;

// Example CLI showing a user's top 10 tracks and artists
// Shows how to authenticate, get user data, retrieve data about
// top artist and tracks, and display it to the console

// Helper functions
std::string truncateText(const std::string& text, std::size_t max) {
    if (text.size() <= max) return text;
    return text.substr(0, max - 3) + "...";
}
std::string centreText(const std::string& text, std::size_t width) {
    if (text.size() >= width) return text.substr(0, width);

    std::size_t left  = (width - text.size()) / 2;
    std::size_t right = width - text.size() - left;

    return std::string(left, ' ') + text + std::string(right, ' ');
}


// This function renders the processed data to the console
void renderResults(const std::vector<ArtistObject>& artists, const std::vector<SimplifiedTrackObject>& tracks, std::string username) {

    // Fixed layout widths for consistent CLI formatting
    constexpr std::size_t TOTAL_WIDTH = 80;
    constexpr std::size_t LEFT_COL = 55;

    // Output a header to make it clear what is being displayed
    std::string title = username + "'s top items";

    std::cout << std::string(TOTAL_WIDTH, '-') << '\n';
    std::cout << centreText(title, TOTAL_WIDTH) << '\n';
    std::cout << std::string(TOTAL_WIDTH, '-') << "\n\n";


    // Output Titles
    std::cout << std::left
              << std::setw(LEFT_COL)
              << "Tracks:"
              << "Artists:"
              << std::endl;

    // Output the Data
    std::size_t count = std::min(artists.size(), tracks.size());

    for (std::size_t i = 0; i < count; ++i) {
        std::string leftText =
            std::to_string(i + 1) + ". " +
            tracks[i].name + " - " +
            tracks[i].artists.at(0).name;

        std::string rightText =
            std::to_string(i + 1) + ". " +
            artists[i].name;

        leftText  = truncateText(leftText, LEFT_COL - 1);

        std::cout << std::left
                  << std::setw(LEFT_COL) << leftText
                  << rightText
                  << '\n';
    }
}

int main() {

    std::cout << "Starting " << getLibraryName()
             << " v" << getLibraryVersion() << std::endl;
    std::cout << "Copyright (c) 2025 Harry Skerritt" << std::endl;
    std::cout << "--------------------------------------------" << "\n" << std::endl;

    bool suppress = true; // Suppress console output during auth flow (optional)

    try {
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

        // Create the authentication object
        Auth auth( {client_key, client_secret} );

        // Generate the authorisation url - Replace the redirectUri with the one for your spotify app
        auto url = auth.createAuthoriseURL(
            "http://127.0.0.1:8888/callback",
            {
                Scope::UserTopRead,
                Scope::UserReadPrivate,
                Scope::UserReadEmail
            });


        // Open the URL and authenticate
        AuthServer::openBrowser(url);

        // Automatically handle the code coming in to the redirectURI
        std::string code = AuthServer::waitForCode(
            "127.0.0.1", 8888, std::nullopt, suppress);

        // Exchange the code for an authentication token
        auth.exchangeCode(code);

        // Show success message is enabled
        if (!suppress) {
            std::cout << "Authorization successful!" << std::endl;
        }

        // ************************************************************
        // *  Everything is successfully authenticated at this point  *
        // ************************************************************


        Client client(auth);

        // Spotify time range: ShortTerm | MediumTerm | LongTerm
        TimeRange time_range = TimeRange::ShortTerm;

        // Value to pass to Spotify for the amount of items to return
        int return_limit = 10;

        // Call the API at the target end points
        const auto username = client.users().getCurrentUserProfile().display_name;
        const auto top_tracks = client.users().getUsersTopTracks(time_range, return_limit).items;
        const auto top_artists = client.users().getUsersTopArtists(time_range, return_limit).items;

        // Send the retrieved data to the render function
        renderResults(top_artists, top_tracks, username);
    }
    // Catch any errors and display them in the console
    catch (const APIException& e) {
        std::cerr << "\n[Spotify API Error] Status: " << e.status()
                  << "\nReason: " << e.reason()
                  << "\nMessage: " << e.message() << std::endl;
        throw;
    }
    catch (const NetworkException& e) {
        std::cerr << "\n[Network Error] " << e.what() << std::endl;
        throw;
    }
    catch (const LogicException& e) {
        std::cerr << "\n[Configuration Error] " << e.what() << std::endl;
        throw;
    }
    catch (const Exception& e) {
        std::cerr << "\n[Library Error] " << e.what() << std::endl;
        throw;
    }
    catch (const std::exception& e) {
        std::cerr << "\n[Standard Exception] " << e.what() << std::endl;
        throw;
    }
    return 0;
}
