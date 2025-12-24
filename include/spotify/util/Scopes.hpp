//
// Created by Harry Skerritt on 21/12/2025.
//

#ifndef SCOPES_HPP
#define SCOPES_HPP

#include <string>

namespace Spotify {
    enum class Scope {
        UGCImageUpload,
        UserReadPlaybackState,
        UserModifyPlaybackState,
        UserReadCurrentlyPlaying,
        AppRemoteControl,
        Streaming,
        PlaylistReadPrivate,
        PlaylistReadCollaborative,
        PlaylistModifyPrivate,
        PlaylistModifyPublic,
        UserFollowModify,
        UserFollowRead,
        UserReadPlaybackPosition,
        UserTopRead,
        UserReadRecentlyPlayed,
        UserLibraryModify,
        UserLibraryRead,
        UserReadEmail,
        UserReadPrivate,
        UserPersonalized,
        UserSOALink,
        UserSOAUnlink,
        SOAManageEntitlements,
        SOAManagePartner,
        SOACreatePartner
    };

    inline std::string scopeToString(const Scope scope) {
        switch (scope) {
            case Scope::UGCImageUpload:            return "ugc-image-upload";
            case Scope::UserReadPlaybackState:     return "user-read-playback-state";
            case Scope::UserModifyPlaybackState:   return "user-modify-playback-state";
            case Scope::UserReadCurrentlyPlaying:  return "user-read-currently-playing";
            case Scope::AppRemoteControl:          return "app-remote-control";
            case Scope::Streaming:                 return "streaming";
            case Scope::PlaylistReadPrivate:       return "playlist-read-private";
            case Scope::PlaylistReadCollaborative: return "playlist-read-collaborative";
            case Scope::PlaylistModifyPrivate:     return "playlist-modify-private";
            case Scope::PlaylistModifyPublic:      return "playlist-modify-public";
            case Scope::UserFollowModify:          return "user-follow-modify";
            case Scope::UserFollowRead:            return "user-follow-read";
            case Scope::UserReadPlaybackPosition:  return "user-read-playback-position";
            case Scope::UserTopRead:               return "user-top-read";
            case Scope::UserReadRecentlyPlayed:    return "user-read-recently-played";
            case Scope::UserLibraryModify:         return "user-library-modify";
            case Scope::UserLibraryRead:           return "user-library-read";
            case Scope::UserReadEmail:             return "user-read-email";
            case Scope::UserReadPrivate:           return "user-read-private";
            case Scope::UserPersonalized:          return "user-personalized";
            case Scope::UserSOALink:               return "user-soa-link";
            case Scope::UserSOAUnlink:             return "user-soa-unlink";
            case Scope::SOAManageEntitlements:     return "soa-manage-entitlements";
            case Scope::SOAManagePartner:          return "soa-manage-partner";
            case Scope::SOACreatePartner:          return "soa-create-partner";
            default: return "";
        }
    }

    inline std::string buildScopeString(const std::vector<Scope>& scopes) {
        if (scopes.empty()) return "";

        std::string result;
        for (size_t i = 0; i < scopes.size(); ++i) {
            result += scopeToString(scopes[i]);
            if (i < scopes.size() - 1) {
                result += " ";
            }
        }
        return result;
    }
}

#endif //SCOPES_HPP
