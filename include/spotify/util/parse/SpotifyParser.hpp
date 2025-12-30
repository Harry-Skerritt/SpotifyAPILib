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
    /// exists on Spotify
    /// @param id Spotify ID (e.g. 6IVkf5av5jnraZpLPszoZR)
    /// @return True if the ID is correctly formatted
    inline bool isValidID(const std::string &id) {
        if (id.length() != 22) return false;
        return std::ranges::all_of(id, [](unsigned char c) {
            return std::isalnum(c);
        });
    }


    // --- IDS ---

    /// Extracts and validates a Spotify ID from an input string
    ///
    /// Supports both Spotify URLs and Spotify URIs, such as:
    /// - https://open.spotify.com/track/{id}
    /// - spotify:track:{id}
    /// @param input Spotify URL or URI
    /// @throws InvalidIDException if the extracted ID does not match the expected format
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

    /// Attempts to extract and validate a Spotify ID from an input string
    ///
    /// This function is a non-throwing wrapper around @c extractID
    /// If any input fails validation, the function returns @c std::nullopt
    /// and optionally provides an error message describing the failure
    ///
    /// @param input Spotify URL or URI to parse
    /// @param error Optional output parameter to receive the error message
    ///              if extraction fails
    /// @return An optional string of a valid Spotify ID, or @c std::nullopt
    ///         if an error occurs
    ///
    /// @note This function does not throw exceptions
    /// @see extractID
    inline std::optional<std::string> tryExtractID(const std::string& input, std::string* error = nullptr) {
        try {
            return extractID(input);
        }
        catch (const InvalidIDException& e) {
            if (error) *error = e.what();
            return std::nullopt;
        }
    }


    /// Extracts and validates Spotify IDs from a list of input strings
    /// @param input Vector of Spotify URLs or URIs
    /// @return Vector of validated Spotify IDs
    /// @throws InvalidIDException if any extracted ID is invalid
    inline std::vector<std::string> extractIDs(const std::vector<std::string>& input) {
        std::vector<std::string> ids;
        ids.reserve(input.size());

        for (const auto& i : input ) {
            ids.push_back(extractID(i));
        }

        return ids;
    }

    /// Attempts to extract and validate Spotify IDs from a list of input strings
    ///
    /// This function is a non-throwing wrapper around @c extractIDs
    /// If any input fails validation, the function returns @c std::nullopt
    /// and optionally provides an error message describing the failure
    ///
    /// @param input Vector of Spotify URLs or URIs to parse
    /// @param error Optional output parameter to receive the error message
    ///              if extraction fails
    /// @return An optional vector of valid Spotify IDs, or @c std::nullopt
    ///         if an error occurs
    ///
    /// @note This function does not throw exceptions
    /// @see extractIDs
    inline std::optional<std::vector<std::string>> tryExtractIDs(const std::vector<std::string>& input, std::string* error = nullptr) {
        try {
            return extractIDs(input);
        }
        catch (const InvalidIDException& e) {
            if (error) *error = e.what();
            return std::nullopt;
        }
    }


    // --- URIs ---

    /// Converts a Spotify URL or URI into a validated Spotify URI
    /// @param input Spotify URL or URI
    /// @throws InvalidResourceException if the resource type is unsupported or invalid
    /// @throws InvalidIDException if the extracted ID is not a valid Spotify ID
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

    /// Attempts to extract and validate a Spotify URI from an input string
    ///
    /// This function is a non-throwing wrapper around @c extractURI
    /// If any input fails validation, the function returns @c std::nullopt
    /// and optionally provides an error message describing the failure
    ///
    /// @param input Spotify URL or URI to parse
    /// @param error Optional output parameter to receive the error message
    ///              if extraction fails
    /// @return An optional string of a valid Spotify URI, or @c std::nullopt
    ///         if an error occurs
    ///
    /// @note This function does not throw exceptions
    /// @see extractURI
    inline std::optional<std::string> tryExtractURI(const std::string& input, std::string* error = nullptr) {
        try {
            return extractURI(input);
        }
        catch (const InvalidResourceException& e) {
            if (error) *error = e.what();
            return std::nullopt;
        }
        catch (const InvalidIDException& e) {
            if (error) *error = e.what();
            return std::nullopt;
        }
    }


    /// Extracts and validates Spotify URIs from a list of input strings
    /// @param input Vector of Spotify URLs or URIs
    /// @return Vector of validated Spotify URIs
    /// @throws InvalidResourceException if any resource type is invalid
    /// @throws InvalidIDException if any extracted ID is invalid
    inline std::vector<std::string> extractURIs(const std::vector<std::string>& input) {
        std::vector<std::string> uris;
        uris.reserve(input.size());

        for (const auto& i : input ) {
            uris.push_back(extractURI(i));
        }

        return uris;
    }

    /// Attempts to extract and validate Spotify URIs from a list of input strings
    ///
    /// This function is a non-throwing wrapper around @c extractURIs
    /// If any input fails validation, the function returns @c std::nullopt
    /// and optionally provides an error message describing the failure
    ///
    /// @param input Vector of Spotify URLs or URIs to parse
    /// @param error Optional output parameter to receive the error message
    ///              if extraction fails
    /// @return An optional vector of valid Spotify URIs, or @c std::nullopt
    ///         if an error occurs
    ///
    /// @note This function does not throw exceptions
    /// @see extractURIs
    inline std::optional<std::vector<std::string>> tryExtractURIs(const std::vector<std::string>& input, std::string* error = nullptr) {
        try {
            return extractURIs(input);
        }
        catch (const InvalidResourceException& e) {
            if (error) *error = e.what();
            return std::nullopt;
        }
        catch (const InvalidIDException& e) {
            if (error) *error = e.what();
            return std::nullopt;
        }
    }

}

#endif //SPOTIFYPARSER_HPP
