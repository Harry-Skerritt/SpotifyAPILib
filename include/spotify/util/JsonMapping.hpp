//
// Created by Harry Skerritt on 21/12/2025.
//

#ifndef JSONMAPPING_H
#define JSONMAPPING_H

#include "../thirdparty/nlohmann/json.hpp"
#include "spotify/util/Types.h"

using json = nlohmann::json;

namespace Spotify {

    template <typename T>
    void map_optional(const json& j, const std::string& key, std::optional<T>& field);

    template <typename T>
    void map_object(const json& j, const std::string& key, T& field);

    template <typename T>
    void from_json(const json& j, PagingObject<T>& p);

    // --- Base Objects ---
    void from_json(const json& j, ImageObject& i);
    void from_json(const json& j, CursorObject& c);
    void from_json(const json& j, CopyrightObject& c);
    void from_json(const json& j, ExternalURL& e);
    void from_json(const json& j, RestrictionsObject& r);
    void from_json(const json& j, ExternalID& e);
    void from_json(const json& j, LinkedFromObject& l);
    void from_json(const json& j, FollowersObject& f);
    void from_json(const json& j, ResumePointObject& r);
    void from_json(const json& j, NarratorObject& n);
    void from_json(const json& j, AuthorObject& a);
    void from_json(const json& j, CategoryObject& c);
    void from_json(const json& j, GenreObject& g);
    void from_json(const json& j, MarketObject& m);
    void from_json(const json& j, DeviceObject& d);
    void from_json(const json& j, ContextObject& c);
    void from_json(const json& j, ActionsObject& a);
    void from_json(const json& j, ExplicitContentObject& e);
    void from_json(const json& j, AddedByObject& a);
    void from_json(const json& j, OwnerObject& o);
    void from_json(const json& j, TrackCollectionObject& t);

    // --- Simplified Objects ---
    void from_json(const json& j, SimplifiedArtistObject& a);
    void from_json(const json& j, SimplifiedTrackObject& t);
    void from_json(const json& j, SimplifiedChapterObject& c);
    void from_json(const json& j, SimplifiedAudioBookObject& a);
    void from_json(const json& j, SimplifiedEpisodeObject& e);
    void from_json(const json& j, SimplifiedShowObject& s);
    void from_json(const json& j, SimplifiedPlaylistObject& p);
    void from_json(const json& j, SimplifiedAlbumObject& a);

    // --- Linked Objects ---
    void from_json(const json& j, PlaylistTrackObject& p);

    // --- 'Main' Response Objects
    void from_json(const json& j, AlbumObject& a);
    void from_json(const json& j, ArtistObject& a);
    void from_json(const json& j, TrackObject& a);
    void from_json(const json& j, AudioBookObject& a);
    void from_json(const json& j, ChapterObject& c);
    void from_json(const json& j, EpisodeObject& e);
    void from_json(const json& j, ShowObject& s);
    void from_json(const json& j, PlaybackObject& p);
    void from_json(const json& j, PlaylistObject& p);
    void from_json(const json& j, UserObject& u);
    void from_json(const json& j, PlayHistoryObject& p);
    void from_json(const json& j, QueueObject& q);

    // --- Search ---
    void from_json(const json& j, SearchObject& s);

    // --- List Objects ---
    void from_json(const json& j, DeviceListObject& dl);
    void from_json(const json& j, AlbumListObject& al);
    void from_json(const json& j, ArtistListObject& al);
    void from_json(const json& j, TrackListObject& tl);

    void from_json(const json& j, SavedAlbumObject& s);


}


#endif //JSONMAPPING_H
