//
// Created by Harry Skerritt on 30/12/2025.
//

#ifndef SPOTIFYPARSER_HPP
#define SPOTIFYPARSER_HPP

#include <algorithm>
#include <iostream>
#include <string>

#include "spotify/core/Errors.hpp"

namespace Spotify::Parse {

    /// Checks whether a string matches the Spotify ID format
    /// @note A valid Spotify ID is exactly 22 characters long and contains only
    /// alphanumeric characters. This function does not verify that the ID
    /// exists on Spotify.
    /// @param id Spotify ID (e.g. 6IVkf5av5jnraZpLPszoZR)
    /// @returns True if the ID is correctly formatted
    inline bool isValidID(const std::string &id) {
        if (id.length() != 22) return false;
        return std::ranges::all_of(id, [](unsigned char c) {
            return std::isalnum(c);
        });
    }

    /// Extracts and validates a Spotify ID from an input string.
    /// Supports both Spotify URLs and Spotify URIs, such as:
    /// - https://open.spotify.com/track/{id}
    /// - spotify:track:{id}
    /// @param input Spotify URL or URI.
    /// @throws InvalidIDException if the extracted ID does not match the expected format.
    inline std::string extractID(const std::string& input) {
        // Find the last '/' (URL) or ':' (URI)
        size_t start = input.find_last_of("/:");
        start = (start == std::string::npos) ? 0 : start + 1;

        // Find '?'
        size_t end = input.find('?', start);
        if (end == std::string::npos) end = input.length();

        std::string id = input.substr(start, end - start);

        if (!isValidID(id)) {
            throw InvalidIDException("String '" + id + "' is not a valid 22-character Base62 Spotify ID");
        };

        return id;
    }


    /// Converts a Spotify URL or URI into a validated Spotify URI.
    /// @param input Spotify URL or URI.
    /// @throws InvalidResourceException if the resource type is unsupported or invalid.
    /// @throws InvalidIDException if the extracted ID is not a valid Spotify ID.
    inline std::string extractURI(const std::string& input) {
        if (input.starts_with("spotify:") && input.find('?') == std::string::npos) {
            // Already a URI
            extractID(input);
            return input;
        }

        std::string type;
        if (input.contains("/album/")) type = "album";
        else if (input.contains("/track/")) type = "track";
        else if (input.contains("/artist/")) type = "artist";
        else if (input.contains("/playlist/")) type = "playlist";
        else if (input.contains("/show/")) type = "show";
        else if (input.contains("/episode/")) type = "episode";
        else if (input.contains("/user/")) type = "user";
        else throw InvalidResourceException("Could not find a valid Spotify type in: " + input);

        return "spotify:" + type + ":" + extractID(input);
    }

}

#endif //SPOTIFYPARSER_HPP
