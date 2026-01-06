//
// Created by Harry Skerritt on 21/12/2025.
//

#include "../../include/spotify/util/parse/JsonMapping.hpp"

#include "spotify/util/parse/InternalHelpers.hpp"

namespace Spotify {

    // Helper for vector mapping since ArduinoJson doesn't do this automatically
    template<typename T>
    void map_vector(JsonVariantConst j, const std::string& key, std::vector<T>& vec) {
        vec.clear();
        JsonArrayConst arr = j[key];
        for (JsonVariantConst v : arr) {
            T item;
            from_json(v, item);
            vec.push_back(item);
        }
    }

    // Helper for simple primitive vectors (strings, ints)
    template<typename T>
    void map_simple_vector(JsonVariantConst j, const std::string& key, std::vector<T>& vec) {
        vec.clear();
        JsonArrayConst arr = j[key];
        for (JsonVariantConst v : arr) {
            vec.push_back(v.as<T>());
        }
    }

    template <typename T>
    void from_json(JsonVariantConst j, std::vector<T>& vec) {
        vec.clear();
        JsonArrayConst arr = j.as<JsonArrayConst>();
        for (JsonVariantConst v : arr) {
            T item;
            from_json(v, item);
            vec.push_back(item);
        }
    }

    void from_json(JsonVariantConst j, std::vector<bool>& vec) {
        vec.clear();
        JsonArrayConst arr = j.as<JsonArrayConst>();
        for (JsonVariantConst v : arr) {
            vec.push_back(v.as<bool>());
        }
    }

    void from_json(JsonVariantConst j, std::vector<std::string>& vec) {
        vec.clear();
        JsonArrayConst arr = j.as<JsonArrayConst>();
        for (JsonVariantConst v : arr) {
            vec.push_back(v.as<std::string>());
        }
    }

    // --- Helpers ---
    template<typename T> struct is_vector : std::false_type {};
    template<typename T> struct is_vector<std::vector<T>> : std::true_type {};

    template<typename T>
    void map_optional(JsonVariantConst j, const std::string &key, std::optional<T> &field) {
        if (j[key] && !j[key].isNull()) {
            // If it's a simple type ArduinoJson knows, use .as<T>()
            if constexpr (std::is_fundamental_v<T> || std::is_same_v<T, std::string>) {
                field = j[key].as<T>();
            }
            // Otherwise, it's one of our custom Spotify structs
            else {
                T obj;
                from_json(j[key], obj);
                field = obj;
            }
        } else {
            field = std::nullopt;
        }
    }

    template<typename T>
    void map_object(JsonVariantConst j, const std::string& key, T& field) {
        if (j[key] && !j[key].isNull()) {
            from_json(j[key], field);
        }
    }


    void map_queue_item(const JsonVariantConst j, Spotify::QueueObject::PlayableItem& target) {
        if (j.isNull()) return;

        std::string type = j["type"] | "";

        if (type == "track") {
            auto track = std::make_shared<Spotify::TrackObject>();
            from_json(j, *track);
            target.data = track;
        }
        else if (type == "episode") {
            auto ep = std::make_shared<Spotify::EpisodeObject>();
            from_json(j, *ep);
            target.data = ep;
        }
    }

    // --- Base Objects ---
    void from_json(JsonVariantConst j, ImageObject &i) {
        i.url = j["url"] | "";
        map_optional(j, "width", i.width);
        map_optional(j, "height", i.height);
    }

    void from_json(JsonVariantConst j, CursorObject &c) {
        c.after = j["after"] | "";
        c.before = j["before"] | "";
    }

    void from_json(JsonVariantConst j, CopyrightObject &c) {
        c.text = j["text"] | "";
        c.type = j["type"] | "";
    }

    void from_json(JsonVariantConst j, ExternalURL &e) {
        e.spotify = j["spotify"] | "";
    }

    void from_json(JsonVariantConst j, URIObject &u) {
        u.uri = j["uri"] | "";
    }

    void from_json(JsonVariantConst j, RestrictionsObject &r) {
        r.reason = j["reason"] | "";
    }

    void from_json(JsonVariantConst j, ExternalID &e) {
        e.isrc = j["isrc"] | "";
        e.ean = j["ean"] | "";
        e.upc = j["upc"] | "";
    }

    void from_json(JsonVariantConst j, LinkedFromObject &l) {
        map_object(j, "external_urls", l.external_urls);
        l.href = j["href"] | "";
        l.id = j["id"] | "";
        l.type = j["type"] | "";
        l.uri = j["uri"] | "";
    }

    void from_json(JsonVariantConst j, FollowersObject &f) {
        map_optional(j, "href", f.href);
        f.total = j["total"] | 0;
    }

    void from_json(JsonVariantConst j, ResumePointObject &r) {
        r.fully_played = j["fully_played"] | false;
        r.resume_position_ms = j["resume_position_ms"] | 0;
    }

    void from_json(JsonVariantConst j, NarratorObject &n) {
        n.name = j["name"] | "";
    }

    void from_json(JsonVariantConst j, AuthorObject &a) {
        a.name = j["name"] | "";
    }

    void from_json(JsonVariantConst j, CategoryObject &c) {
        map_vector(j, "icons", c.icons);
        c.href = j["href"] | "";
        c.id = j["id"] | "";
        c.name = j["name"] | "";
    }

    void from_json(JsonVariantConst j, GenreObject &g) {
        map_simple_vector(j, "genres", g.genres);
    }

    void from_json(JsonVariantConst j, MarketObject &m) {
        map_simple_vector(j, "markets", m.markets);
    }

    void from_json(JsonVariantConst j, DeviceObject& d) {
        map_optional(j, "id", d.id);
        d.is_active = j["is_active"] | false;
        d.is_private_session = j["is_private_session"] | false;
        d.is_restricted = j["is_restricted"] | false;
        d.name = j["name"] | "Unknown";
        d.type = j["type"] | "Unknown";
        map_optional(j, "volume_percent", d.volume_percent);
        d.supports_volume = j["supports_volume"] | false;
    }

    void from_json(JsonVariantConst j, ContextObject &c) {
        c.type = j["type"] | "";
        c.href = j["href"] | "";
        c.uri = j["uri"] | "";
        map_object(j, "external_urls", c.external_urls);
    }

    void from_json(JsonVariantConst j, ActionsObject &a) {
        JsonObjectConst dis = j["disallows"];
        a.interrupting_playback = !(dis["interrupting_playback"] | false);
        a.pausing = !(dis["pausing"] | false);
        a.resuming = !(dis["resuming"] | false);
        a.seeking = !(dis["seeking"] | false);
        a.skipping_next = !(dis["skipping_next"] | false);
        a.skipping_prev = !(dis["skipping_prev"] | false);
        a.toggling_repeat_context = !(dis["toggling_repeat_context"] | false);
        a.toggling_shuffle = !(dis["toggling_shuffle"] | false);
        a.toggling_repeat_track = !(dis["toggling_repeat_track"] | false);
        a.transferring_playback = !(dis["transferring_playback"] | false);
    }

    void from_json(JsonVariantConst j, ExplicitContentObject &e) {
        e.filter_enabled = j["filter_enabled"] | false;
        e.filter_locked = j["filter_locked"] | false;
    }

    void from_json(JsonVariantConst j, AddedByObject &a) {
        map_object(j, "external_urls", a.external_urls);
        a.href = j["href"] | "";
        a.id = j["id"] | "";
        a.type = j["type"] | "";
        a.uri = j["uri"] | "";
    }

    void from_json(JsonVariantConst j, OwnerObject &o) {
        map_object(j, "external_urls", o.external_urls);
        o.href = j["href"] | "";
        o.id = j["id"] | "";
        o.type = j["type"] | "";
        o.uri = j["uri"] | "";
        map_optional(j, "display_name", o.display_name);
    }

    void from_json(JsonVariantConst j, TrackCollectionObject &t) {
        t.href = j["href"] | "";
        t.total = j["total"] | 0;
    }


    // --- Simplified Objects ---
    void from_json(JsonVariantConst j, SimplifiedArtistObject &a) {
        map_object(j, "external_urls", a.external_urls);
        a.href = j["href"] | "";
        a.id = j["id"] | "";
        a.name = j["name"] | "";
        a.type = j["type"] | "";
        a.uri = j["uri"] | "";
    }

    void from_json(JsonVariantConst j, SimplifiedTrackObject &t) {
        map_vector(j, "artists", t.artists);
        map_simple_vector(j, "available_markets", t.available_markets);
        t.disc_number = j["disc_number"] | 0;
        t.duration_ms = j["duration_ms"] | 0;
        t.is_explicit = j["explicit"] | false;
        map_object(j, "external_urls", t.external_urls);
        t.href = j["href"] | "";
        t.id = j["id"] | "";
        t.is_playable = j["is_playable"] | false;
        map_object(j, "linked_from", t.linked_from);
        map_object(j, "restrictions", t.restrictions);
        t.name = j["name"] | "";
        map_optional(j, "preview_url", t.preview_url);
        t.track_number = j["track_number"] | 0;
        t.type = j["type"] | "";
        t.uri = j["uri"] | "";
        t.is_local = j["is_local"] | false;
    }

    void from_json(JsonVariantConst j, SimplifiedChapterObject &c) {
        map_optional(j, "audio_preview_url", c.audio_preview_url);
        map_simple_vector(j, "available_markets", c.available_markets);
        c.chapter_number = j["chapter_number"] | 0;
        c.description = j["description"] | "";
        c.html_description = j["html_description"] | "";
        c.duration_ms = j["duration_ms"] | 0;
        c.is_explicit = j["explicit"] | false;
        map_object(j, "external_urls", c.external_urls);
        c.href = j["href"] | "" ;
        c.id = j["id"] | "" ;
        map_vector(j, "images", c.images);
        c.is_playable = j["is_playable"] | false ;
        map_simple_vector(j, "languages", c.languages);
        c.name = j["name"] | "" ;
        c.release_date = j["release_date"] | "" ;
        c.release_date_precision = j["release_date_precision"] | "" ;
        map_object(j, "resume_point", c.resume_point);
        c.type = j["type"] | "";
        c.uri = j["uri"] | "";
        c.uri = j["uri"] | "";
        map_object(j, "restrictions", c.restrictions);
    }

    void from_json(JsonVariantConst j, SimplifiedAudiobookObject &a) {
        map_vector(j, "authors", a.authors);
        map_simple_vector(j, "available_markets", a.available_markets);
        map_vector(j, "copyrights", a.copyrights);
        a.description = j["description"] | "" ;
        a.html_description = j["html_description"] | "" ;
        a.edition = j["edition"] | "" ;
        a.is_explicit = j["explicit"] | false ;
        map_object(j, "external_urls", a.external_urls);
        a.href = j["href"] | "" ;
        a.id = j["id"] | "" ;
        map_vector(j, "images", a.images);
        map_simple_vector(j, "languages", a.languages);
        a.media_type = j["media_type"] | "" ;
        a.name = j["name"] | "" ;
        map_vector(j, "narrators", a.narrators);
        a.publisher = j["publisher"] | "" ;
        a.type = j["type"] | "" ;
        a.uri = j["uri"] | "" ;
        a.total_chapters = j["total_chapters"] | 0 ;
    }

    void from_json(JsonVariantConst j, SimplifiedEpisodeObject &e) {
        map_optional(j, "audio_preview_url", e.audio_preview_url);
        e.description = j["description"] | "";
        e.html_description = j["html_description"] | "";
        e.duration_ms = j["duration_ms"] | 0;
        e.is_explicit = j["explicit"] | false;
        map_object(j, "external_urls", e.external_urls);
        e.href = j["href"] | "";
        e.id = j["id"] | "";
        map_vector(j, "images", e.images);
        e.is_externally_hosted = j["is_externally_hosted"] | false;
        e.is_playable = j["is_playable"] | false;
        e.language = j["language"] | "";
        map_simple_vector(j, "languages", e.languages);
        e.name = j["name"] | "";
        e.release_date = j["release_date"] | "";
        e.release_date_precision = j["release_date_precision"] | "";
        map_object(j, "resume_point", e.resume_point);
        e.type = j["type"] | "";
        e.uri = j["uri"] | "";
        map_object(j, "restrictions", e.restrictions);
    }

    void from_json(JsonVariantConst j, SimplifiedShowObject &s) {
        map_simple_vector(j, "available_markets", s.available_markets);
        map_vector(j, "copyrights", s.copyrights);
        s.description = j["description"] | "";
        s.html_description = j["html_description"] | "";
        s.is_explicit = j["explicit"] | false;
        map_object(j, "external_urls", s.external_urls);
        s.href = j["href"] | "";
        s.id = j["id"] | "";
        map_vector(j, "images", s.images);
        s.is_externally_hosted = j["is_externally_hosted"] | false;
        map_simple_vector(j, "languages", s.languages);
        s.media_type = j["media_type"] | "";
        s.name = j["name"] | "";
        s.publisher = j["publisher"] | "";
        s.type = j["type"] | "";
        s.uri = j["uri"] | "";
        s.total_episodes = j["total_episodes"] | 0;
    }

    void from_json(JsonVariantConst j, SimplifiedPlaylistObject &p) {
        p.collaborative = j["collaborative"] | false;
        p.description = j["description"] | "";
        map_object(j, "external_urls", p.external_urls);
        p.href = j["href"] | "";
        p.id = j["id"] | "";
        map_vector(j, "images", p.images);
        p.name = j["name"] | "";
        map_object(j, "owner", p.owner);
        p.is_public = j["public"] | false;
        p.snapshot_id = j["snapshot_id"] | "";
        map_object(j, "tracks", p.tracks);
        p.type = j["type"] | "";
        p.uri = j["uri"] | "";
    }

    void from_json(JsonVariantConst j, SimplifiedAlbumObject &a) {
        a.album_type = j["album_type"] | "";
        a.total_tracks = j["total_tracks"] | 0;
        map_simple_vector(j, "available_markets", a.available_markets);
        map_object(j, "external_urls", a.external_urls);
        a.href = j["href"] | "";
        a.id = j["id"] | "";
        map_vector(j, "images", a.images);
        a.name = j["name"] | "";
        a.release_date = j["release_date"] | "";
        a.release_date_precision = j["release_date_precision"] | "";
        map_object(j, "restrictions", a.restrictions);
        a.type = j["type"] | "";
        a.uri = j["uri"] | "";
        map_vector(j, "artists", a.artists);
    }

    // --- Linked Objects ---
    void from_json(const JsonVariantConst j, PlaylistTrackObject& pt) {
        pt.added_at = j["added_at"] | "";
        map_object(j, "added_by", pt.added_by);
        pt.is_local = j["is_local"] | false;

        // Handle Variant
        if (j["track"] && !j["track"].isNull()) {
            JsonVariantConst track_data = j["track"];
            std::string type = track_data["type"] | "";

            if (type == "track") {
                auto t = std::make_shared<TrackObject>();
                from_json(track_data, *t);
                pt.track = t;
            } else if (type == "episode") {
                auto e = std::make_shared<EpisodeObject>();
                from_json(track_data, *e);
                pt.track = e;
            }
        }
    }

    template <typename T>
    void from_json(const JsonVariantConst j, PagingObject<T>& p) {
        p.href = j["href"] | "";
        p.limit = j["limit"] | 0;
        p.total = j["total"] | 0;

        map_optional(j, "offset", p.offset);
        map_optional(j, "next", p.next);
        map_optional(j, "prev", p.prev);

        map_optional(j, "cursors", p.cursors);

        p.items.clear();
        JsonArrayConst itemsArr = j["items"];

        for (JsonVariantConst itemJson : itemsArr) {
            T item;
            from_json(itemJson, item);
            p.items.push_back(item);
        }
    }


    // --- 'Main' Response Objects ---
    void from_json(JsonVariantConst j, AlbumObject &a) {
        a.album_type = j["album_type"] | "";
        a.total_tracks = j["total_tracks"] | 0;
        map_simple_vector(j, "available_markets", a.available_markets);
        map_object(j, "external_urls", a.external_urls);
        a.href = j["href"] | "";
        a.id = j["id"] | "";
        map_vector(j, "images", a.images);
        a.name = j["name"] | "";
        a.release_date = j["release_date"] | "";
        a.release_date_precision = j["release_date_precision"] | "";
        map_object(j, "restrictions", a.restrictions);
        a.type = j["type"] | "";
        a.uri = j["uri"] | "";
        map_vector(j, "artists", a.artists);
        map_object(j, "tracks", a.tracks);
        map_vector(j, "copyrights", a.copyrights);
        map_object(j, "external_ids", a.external_ids);
        map_simple_vector(j, "genres", a.genres);
        a.label = j["label"] | "";
        a.popularity = j["popularity"] | 0;
    }

    void from_json(JsonVariantConst j, ArtistObject &a) {
        map_object(j, "external_urls", a.external_urls);
        map_object(j, "followers", a.followers);
        map_simple_vector(j, "genres", a.genres);
        a.href = j["href"] | "";
        map_vector(j, "images", a.images);
        a.name = j["name"] | "";
        a.popularity = j["popularity"] | 0;
        a.type = j["type"] | "";
        a.uri = j["uri"] | "";
    }

    void from_json(JsonVariantConst j, TrackObject &a) {
        map_object(j, "album", a.album);
        map_vector(j, "artists", a.artists);
        map_simple_vector(j, "available_markets", a.available_markets);
        a.disc_number = j["disc_number"] | 0;
        a.duration_ms = j["duration_ms"] | 0;
        a.is_explicit = j["explicit"] | false;
        map_object(j, "external_ids", a.external_ids);
        map_object(j, "external_urls", a.external_urls);
        a.href = j["href"] | "";
        a.id = j["id"] | "";
        a.is_playable = j["is_playable"] | false;
        map_object(j, "linked_from", a.linked_from);
        map_object(j, "restrictions", a.restrictions);
        a.name = j["name"] | "";
        a.popularity = j["popularity"] | 0;
        map_optional(j, "preview_url", a.preview_url);
        a.track_number = j["track_number"] | 0;
        a.type = j["type"] | "";
        a.uri = j["uri"] | "";
        a.is_local = j["is_local"] | false;
    }

    void from_json(JsonVariantConst j, AudiobookObject &a) {
        map_vector(j, "authors", a.authors);
        map_simple_vector(j, "available_markets", a.available_markets);
        map_vector(j, "copyrights", a.copyrights);
        a.description = j["description"] | "";
        a.html_description = j["html_description"] | "";
        a.edition = j["edition"] | "";
        a.is_explicit = j["explicit"] | false;
        map_object(j, "external_urls", a.external_urls);
        a.href = j["href"] | "";
        a.id = j["id"] | "";
        map_vector(j, "images", a.images);
        map_simple_vector(j, "languages", a.languages);
        a.media_type = j["media_type"] | "";
        a.name = j["name"] | "";
        map_vector(j, "narrators", a.narrators);
        a.publisher = j["publisher"] | "";
        a.type = j["type"] | "";
        a.uri = j["uri"] | "";
        a.total_chapters = j["total_chapters"] | 0;
        map_object(j, "chapters", a.chapters);
    }

    void from_json(JsonVariantConst j, ChapterObject &c) {
        map_optional(j, "audio_preview_url", c.audio_preview_url);
        map_simple_vector(j, "available_markets" , c.available_markets);
        c.chapter_number = j["chapter_number"] | 0;
        c.description = j["description"] | "";
        c.html_description = j["html_description"] | std::string{};
        c.duration_ms = j["duration_ms"] | 0;
        c.is_explicit = j["explicit"] | false;
        map_object(j, "external_urls", c.external_urls);
        c.href = j["href"] | "";
        c.id = j["id"] | "";
        map_vector(j, "images", c.images);
        c.is_playable = j["is_playable"] | false;
        map_simple_vector(j, "languages", c.languages);
        c.name = j["name"] | "";
        c.release_date = j["release_date"] | "";
        c.release_date_precision = j["release_date_precision"] | "";
        map_object(j, "resume_point", c.resume_point);
        c.type = j["type"] | "";
        c.uri = j["uri"] | "";
        map_object(j, "restrictions", c.restrictions);
        map_object(j, "audiobook", c.audiobook);
    }

    void from_json(JsonVariantConst j, EpisodeObject &e) {
        map_optional(j, "audio_preview_url", e.audio_preview_url);
        e.description = j["description"] | "";
        e.html_description = j["html_description"] | std::string{};
        e.duration_ms = j["duration_ms"] | 0;
        e.is_explicit = j["explicit"] | false;
        map_object(j, "external_urls", e.external_urls);
        e.href = j["href"] | "";
        e.id = j["id"] | "";
        map_vector(j, "images", e.images);
        e.is_externally_hosted = j["is_externally_hosted"] | false;
        e.is_playable = j["is_playable"] | false;
        e.language = j["language"] | "";
        map_simple_vector(j, "languages", e.languages);
        e.name = j["name"] | "";
        e.release_date = j["release_date"] | "";
        e.release_date_precision = j["release_date_precision"] | "";
        map_object(j, "resume_point", e.resume_point);
        e.type = j["type"] | "";
        e.uri = j["uri"] | "";
        map_object(j, "restrictions", e.restrictions);
        map_object(j, "show", e.show);
    }

    void from_json(JsonVariantConst j, ShowObject &s) {
        map_simple_vector(j, "available_markets", s.available_markets);
        map_vector(j, "copyrights", s.copyrights);
        s.description = j["description"] | "";
        s.html_description = j["html_description"] | std::string{};
        s.is_explicit = j["explicit"] | false;
        map_object(j, "external_urls", s.external_urls);
        s.href = j["href"] | "";
        s.id = j["id"] | "";
        map_vector(j, "images", s.images);
        s.is_externally_hosted = j["is_externally_hosted"] | false;
        map_simple_vector(j, "languages", s.languages);
        s.media_type = j["media_type"] | "";
        s.name = j["name"] | "";
        s.publisher = j["publisher"] | "";
        s.type = j["type"] | "";
        s.uri = j["uri"] | "";
        s.total_episodes = j["total_episodes"] | 0;
        map_object(j, "episodes", s.episodes);
    }

    void from_json(JsonVariantConst j, PlaybackObject &p) {
        map_object(j, "device", p.device);
        p.repeat_state = detail::repeatStateFromString(
            j["repeat_state"] | ""
        );
        p.shuffle_state = j["shuffle_state"] | false;
        map_object(j, "context", p.context);
        p.timestamp = j["timestamp"] | 0LL;
        p.progress_ms = j["progress_ms"] | 0;
        p.is_playing = j["is_playing"] | false;
        p.currently_playing_type = j["currently_playing_type"] | "track";

        if (j["item"] && !j["item"].isNull()) {
            JsonVariantConst item_data = j["item"];
            if (p.currently_playing_type == "track") {
                auto track = std::make_shared<TrackObject>();
                from_json(item_data, *track);
                p.item = track;
            } else if (p.currently_playing_type == "episode") {
                auto episode = std::make_shared<EpisodeObject>();
                from_json(item_data, *episode);
                p.item = episode;
            }
        }
        map_object(j, "actions", p.actions);
    }

    void from_json(JsonVariantConst j, PlaylistObject &p) {
        p.collaborative = j["collaborative"] | false;
        map_optional(j, "description", p.description);
        map_object(j, "external_urls", p.external_urls);
        p.href = j["href"] | "";
        p.id = j["id"] | "";
        map_vector(j, "images", p.images);
        p.name = j["name"] | "";
        map_object(j, "owner", p.owner);
        p.is_public = j["public"] | false;
        p.snapshot_id = j["snapshot_id"] | "";
        map_object(j, "tracks", p.tracks);
        p.type = j["type"] | "";
        p.uri = j["uri"] | "";
    }

    void from_json(JsonVariantConst j, UserObject &u) {
        u.country = j["country"] | "";
        u.display_name = j["display_name"] | "";
        u.email = j["email"] | "";
        map_object(j, "explicit_content", u.explicit_content);
        map_object(j, "external_urls", u.external_urls);
        map_object(j, "followers", u.followers);
        u.href = j["href"] | "";
        u.id = j["id"] | "";
        map_vector(j, "images", u.images);
        u.product = j["product"] | "";
        u.type = j["type"] | "";
        u.uri = j["uri"] | "";
    }

    void from_json(JsonVariantConst j, PlayHistoryObject &p) {
        map_object(j, "track", p.track);
        p.played_at = j["played_at"] | "";
        map_object(j, "context", p.context);
    }

    void from_json(JsonVariantConst j, QueueObject &q) {
        if (j["currently_playing"] && !j["currently_playing"].isNull()) {
            map_queue_item(j["currently_playing"], q.currently_playing);
        }

        q.queue.clear();
        JsonArrayConst queueArr = j["queue"];
        for (JsonVariantConst item_json : queueArr) {
            Spotify::QueueObject::PlayableItem item;
            map_queue_item(item_json, item);
            q.queue.push_back(item);
        }
    }



    // --- Search ---
    void from_json(JsonVariantConst j, SearchObject &s) {
        map_optional(j, "tracks", s.tracks);
        map_optional(j, "artists",s.artists);
        map_optional(j, "albums", s.albums);
        map_optional(j, "playlists", s.playlists);
        map_optional(j, "shows", s.shows);
        map_optional(j, "episodes", s.episodes);
        map_optional(j, "audiobooks", s.audiobook);
    }

    // --- List Objects ---
    void from_json(JsonVariantConst j, DeviceListObject &dl) {
        map_vector(j, "devices", dl.devices);
    }

    void from_json(JsonVariantConst j, AlbumListObject &al) {
        map_vector(j, "albums", al.albums);
    }

    void from_json(JsonVariantConst j, ArtistListObject &al) {
        map_vector(j, "artists", al.artists);
    }

    void from_json(JsonVariantConst j, AudiobookListObject &ab) {
        map_vector(j, "audiobooks", ab.audiobooks);
    }

    void from_json(JsonVariantConst j, ChapterListObject &cl) {
        map_vector(j, "chapters", cl.chapters);
    }

    void from_json(JsonVariantConst j, EpisodeListObject &el) {
        map_vector(j, "episodes", el.episodes);
    }

    void from_json(JsonVariantConst j, ShowListObject &sl) {
        map_vector(j, "shows", sl.shows);
    }

    void from_json(JsonVariantConst j, TrackListObject &tl) {
        map_vector(j, "tracks", tl.tracks);
    }



    void from_json(JsonVariantConst j, SavedAlbumObject &s) {
        s.added_at = j["added_at"] | "";
        map_object(j, "album", s.album);
    }

    void from_json(JsonVariantConst j, SavedEpisodeObject &e) {
        e.added_at = j["added_at"] | "";
        map_object(j, "episode", e.episode);
    }

    void from_json(JsonVariantConst j, SavedShowObject &s) {
        s.added_at = j["added_at"] | "";
        map_object(j, "show", s.show);
    }

    void from_json(JsonVariantConst j, SavedTrackObject &t) {
        t.added_at = j["added_at"] | "";
        map_object(j, "track", t.track);
    }

    // --- Explicit Paging Implementation ---

    template void from_json<TrackObject>(JsonVariantConst j, PagingObject<TrackObject>& p);
    template void from_json<SimplifiedChapterObject>(JsonVariantConst j, PagingObject<SimplifiedChapterObject>& p);
    template void from_json<ArtistObject>(JsonVariantConst j, PagingObject<ArtistObject>& p);
    template void from_json<SimplifiedAlbumObject>(JsonVariantConst j, PagingObject<SimplifiedAlbumObject>& p);
    template void from_json<SimplifiedTrackObject>(JsonVariantConst j, PagingObject<SimplifiedTrackObject>& p);
    template void from_json<PlaylistTrackObject>(JsonVariantConst j, PagingObject<PlaylistTrackObject>& p);
    template void from_json<SimplifiedPlaylistObject>(JsonVariantConst j, PagingObject<SimplifiedPlaylistObject>& p);
    template void from_json<SavedAlbumObject>(JsonVariantConst j, PagingObject<SavedAlbumObject>& p);
    template void from_json<SavedEpisodeObject>(JsonVariantConst j, PagingObject<SavedEpisodeObject>& p);
    template void from_json<SavedShowObject>(JsonVariantConst j, PagingObject<SavedShowObject>& p);
    template void from_json<SavedTrackObject>(JsonVariantConst j, PagingObject<SavedTrackObject>& p);
    template void from_json<PlayHistoryObject>(JsonVariantConst j, PagingObject<PlayHistoryObject>& p);
    template void from_json<CategoryObject>(JsonVariantConst j, PagingObject<CategoryObject>& p);

}

