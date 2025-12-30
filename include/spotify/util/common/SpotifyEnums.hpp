//
// Created by Harry Skerritt on 29/12/2025.
//

#ifndef SPOTIFYENUMS_HPP
#define SPOTIFYENUMS_HPP

#pragma once


#include <string>
#include <vector>

namespace Spotify {

    // --- Include Groups ---
    enum class IncludeGroups {
        Album,
        Single,
        AppearsOn,
        Compilation
    };

    inline std::string includeGroupToString(const IncludeGroups group) {
        switch (group) {
            case IncludeGroups::Album:       return "album";
            case IncludeGroups::Single:      return "single";
            case IncludeGroups::AppearsOn:   return "appears_on";
            case IncludeGroups::Compilation: return "compilation";
            default: return "";
        }
    }

    inline std::string buildIncludeGroupsString(const std::vector<IncludeGroups>& groups) {
        if (groups.empty()) return "";

        std::string result;
        for (size_t i = 0; i < groups.size(); ++i) {
            result += includeGroupToString(groups[i]);
            if (i < groups.size() - 1) {
                result += ",";
            }
        }
        return result;
    }

    // --- Additional Types ---
    enum class AdditionalType {
        Track,
        Episode,
        All
    };

    inline std::string additionalTypeToString(const AdditionalType type) {
        switch (type) {
            case AdditionalType::Track:   return "track";
            case AdditionalType::Episode: return "episode";
            case AdditionalType::All:    return "track,episode";
            default: return "";
        }
    }

    // --- Search Types ---
    enum class SearchType {
        Album,
        Artist,
        Playlist,
        Track,
        Show,
        Episode,
        Audiobook
    };

    inline std::string searchTypeToString(const SearchType type) {
        switch (type) {
            case SearchType::Album:       return "album";
            case SearchType::Artist:      return "artist";
            case SearchType::Playlist:    return "playlist";
            case SearchType::Track:       return "track";
            case SearchType::Show:        return "show";
            case SearchType::Episode:     return "episode";
            case SearchType::Audiobook:   return "audiobook";
            default: return "";
        }
    }


    inline std::string buildSearchTypeString(const std::vector<SearchType>& types) {
        if (types.empty()) return "";

        std::string result;
        for (size_t i = 0; i < types.size(); ++i) {
            result += searchTypeToString(types[i]);
            if (i < types.size() - 1) {
                result += ",";
            }
        }
        return result;
    }
}

#endif //SPOTIFYENUMS_HPP
