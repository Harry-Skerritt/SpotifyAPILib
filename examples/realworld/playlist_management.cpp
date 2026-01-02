//
// Created by Harry Skerritt on 01/01/2026.
//

#include <spotify/spotify.hpp>

using namespace Spotify;

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
                Scope::PlaylistModifyPrivate,
                Scope::PlaylistModifyPublic,
                Scope::UserReadPrivate,
                Scope::UserReadEmail,
                Scope::UserTopRead,
                Scope::UGCImageUpload
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

        // Create a client
        Client client(auth);

        // Get the current users profile and extract the information needed
        auto user = client.users().getCurrentUserProfile();
        std::string user_id = user.id;
        std::string username = user.display_name;
        if (username.empty()) username = "unknown";


        // Set up the variables for the playlist
        std::string playlist_name = "Spotify API Lib - Example";
        std::string playlist_desc = "A playlist created for " + username + " containing their top 20 songs! Made using the Spotify API Lib C++ Library!";

        // Create a new playlist
        auto new_playlist = client.playlist().createPlaylist(
            user_id,
            playlist_name,
            false,
            false,
            playlist_desc );


        // Confirm creation and extract the id
        std::string new_playlist_id;
        if (new_playlist.has_value()) {
            std::cout << "Created a new playlist for " << username << std::endl;
            new_playlist_id = new_playlist.value().id;
        } else {
            throw std::runtime_error("Could not create playlist!");
        }

        // Add cover image to the playlist
        std::string image_url = "https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcQW6H6tLVXa2pvLWkQYhbyFBlCbAL8WfVZtDQ&s";
        client.playlist().addCustomPlaylistCover(new_playlist_id, image_url);

        // Spotify time range: ShortTerm | MediumTerm | LongTerm
        TimeRange time_range = TimeRange::MediumTerm;

        // Value to pass to Spotify for the amount of items to return
        int return_limit = 20;


        // Empty vector for song uris
        std::vector<std::string> track_uris;

        // Get the users top 20 tracks
        std::cout << "Getting top tracks..." << std::endl;
        auto tracks = client.users().getUsersTopTracks(time_range, return_limit);

        // Get validated URIs and add them to a vector
        track_uris.reserve(tracks.items.size());
        for (auto& track : tracks.items) {
            track_uris.push_back(Parse::extractURI(track.uri));
        }

        // Add the songs to the playlist
        std::cout << "Adding top tracks..." << std::endl;
        client.playlist().addItemsToPlaylist(new_playlist_id, track_uris);


        std::cout << "Added tracks to playlist!" << std::endl;
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