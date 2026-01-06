//
// Created by Harry Skerritt on 21/12/2025.
//

#ifndef JSONMAPPING_H
#define JSONMAPPING_H

#pragma once

#include <memory>
#include <ArduinoJson.h>
#include "spotify/models/Types.hpp"

namespace Spotify {

    template <typename T>
    void from_json(JsonVariantConst j, std::vector<T>& vec);

    template <>
    void from_json(JsonVariantConst j, std::vector<bool>& vec);

    template <>
    void from_json(JsonVariantConst j, std::vector<std::string>& vec);

    template <typename T>
    void map_optional(JsonVariantConst j, const std::string& key, std::optional<T>& field);

    template <typename T>
    void map_object(JsonVariantConst j, const std::string& key, T& field);

    template <typename T>
    void from_json(JsonVariantConst j, PagingObject<T>& p);


    // --- Base Objects ---
    void from_json(JsonVariantConst j, ImageObject& i);
    void from_json(JsonVariantConst j, CursorObject& c);
    void from_json(JsonVariantConst j, CopyrightObject& c);
    void from_json(JsonVariantConst j, ExternalURL& e);
    void from_json(JsonVariantConst j, URIObject& u);
    void from_json(JsonVariantConst j, RestrictionsObject& r);
    void from_json(JsonVariantConst j, ExternalID& e);
    void from_json(JsonVariantConst j, LinkedFromObject& l);
    void from_json(JsonVariantConst j, FollowersObject& f);
    void from_json(JsonVariantConst j, ResumePointObject& r);
    void from_json(JsonVariantConst j, NarratorObject& n);
    void from_json(JsonVariantConst j, AuthorObject& a);
    void from_json(JsonVariantConst j, CategoryObject& c);
    void from_json(JsonVariantConst j, GenreObject& g);
    void from_json(JsonVariantConst j, MarketObject& m);
    void from_json(JsonVariantConst j, DeviceObject& d);
    void from_json(JsonVariantConst j, ContextObject& c);
    void from_json(JsonVariantConst j, ActionsObject& a);
    void from_json(JsonVariantConst j, ExplicitContentObject& e);
    void from_json(JsonVariantConst j, AddedByObject& a);
    void from_json(JsonVariantConst j, OwnerObject& o);
    void from_json(JsonVariantConst j, TrackCollectionObject& t);

    // --- Simplified Objects ---
    void from_json(JsonVariantConst j, SimplifiedArtistObject& a);
    void from_json(JsonVariantConst j, SimplifiedTrackObject& t);
    void from_json(JsonVariantConst j, SimplifiedChapterObject& c);
    void from_json(JsonVariantConst j, SimplifiedAudiobookObject& a);
    void from_json(JsonVariantConst j, SimplifiedEpisodeObject& e);
    void from_json(JsonVariantConst j, SimplifiedShowObject& s);
    void from_json(JsonVariantConst j, SimplifiedPlaylistObject& p);
    void from_json(JsonVariantConst j, SimplifiedAlbumObject& a);

    // --- Linked Objects ---
    void from_json(JsonVariantConst j, PlaylistTrackObject& p);

    // --- 'Main' Response Objects
    void from_json(JsonVariantConst j, AlbumObject& a);
    void from_json(JsonVariantConst j, ArtistObject& a);
    void from_json(JsonVariantConst j, TrackObject& a);
    void from_json(JsonVariantConst j, AudiobookObject& a);
    void from_json(JsonVariantConst j, ChapterObject& c);
    void from_json(JsonVariantConst j, EpisodeObject& e);
    void from_json(JsonVariantConst j, ShowObject& s);
    void from_json(JsonVariantConst j, PlaybackObject& p);
    void from_json(JsonVariantConst j, PlaylistObject& p);
    void from_json(JsonVariantConst j, UserObject& u);
    void from_json(JsonVariantConst j, PlayHistoryObject& p);
    void from_json(JsonVariantConst j, QueueObject& q);

    // --- Search ---
    void from_json(JsonVariantConst j, SearchObject& s);

    // --- List Objects ---
    void from_json(JsonVariantConst j, DeviceListObject& dl);
    void from_json(JsonVariantConst j, AlbumListObject& al);
    void from_json(JsonVariantConst j, ArtistListObject& al);
    void from_json(JsonVariantConst j, AudiobookListObject& ab);
    void from_json(JsonVariantConst j, ChapterListObject& cl);
    void from_json(JsonVariantConst j, EpisodeListObject& el);
    void from_json(JsonVariantConst j, ShowListObject& sl);
    void from_json(JsonVariantConst j, TrackListObject& tl);


    void from_json(JsonVariantConst j, SavedAlbumObject& s);
    void from_json(JsonVariantConst j, SavedEpisodeObject& e);
    void from_json(JsonVariantConst j, SavedShowObject& s);
    void from_json(JsonVariantConst j, SavedTrackObject& t);


    // --- Explicit Paging Instantiations ---
    extern template void from_json<TrackObject>(JsonVariantConst j, PagingObject<TrackObject>&);
    extern template void from_json<SimplifiedChapterObject>(JsonVariantConst j, PagingObject<SimplifiedChapterObject>& p);
    extern template void from_json<ArtistObject>(JsonVariantConst j, PagingObject<ArtistObject>&);
    extern template void from_json<SimplifiedAlbumObject>(JsonVariantConst j, PagingObject<SimplifiedAlbumObject>&);
    extern template void from_json<SimplifiedTrackObject>(JsonVariantConst j, PagingObject<SimplifiedTrackObject>&);
    extern template void from_json<PlaylistTrackObject>(JsonVariantConst j, PagingObject<PlaylistTrackObject>&);
    extern template void from_json<SimplifiedPlaylistObject>(JsonVariantConst j, PagingObject<SimplifiedPlaylistObject>&);
    extern template void from_json<SavedAlbumObject>(JsonVariantConst j, PagingObject<SavedAlbumObject>&);
    extern template void from_json<SavedEpisodeObject>(JsonVariantConst j, PagingObject<SavedEpisodeObject>&);
    extern template void from_json<SavedShowObject>(JsonVariantConst j, PagingObject<SavedShowObject>&);
    extern template void from_json<SavedTrackObject>(JsonVariantConst j, PagingObject<SavedTrackObject>&);
    extern template void from_json<PlayHistoryObject>(JsonVariantConst j, PagingObject<PlayHistoryObject>&);
    extern template void from_json<CategoryObject>(JsonVariantConst j, PagingObject<CategoryObject>&);




}


#endif //JSONMAPPING_H
