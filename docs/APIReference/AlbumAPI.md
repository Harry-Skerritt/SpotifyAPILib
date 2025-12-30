# Album API

Provides access to Spotify Album endpoints

## Functions

### `getAlbum(const std::string& id, const std::optional<std::string>& market = std::nullopt)`

Retrieves a single album by its Spotify ID.

*See Also: [Spotify API Reference - Get Album](https://developer.spotify.com/documentation/web-api/reference/get-an-album)*


#### Parameters:

| Name  | Type                         | Description                      |
|-------|------------------------------|----------------------------------|
| id    | `std::string`                | Spotify album ID                 |
| market| `std::optional<std::string>` | Optional ISO 3166-1 Country Code |

#### Returns: [`AlbumObject`]()

#### Throws:

- [`Spotify::APIException`]() on an API Error
- [`Spotify::NetworkException`]() on network failure

#### Example:

[Try It Yourself]()

```c++
auto album_id = Spotify::Parse::extractID("https://open.spotify.com/album/1U3qu4gDfohAqFrmpLT11l");
auto album = client.album().getAlbum(album_id);
std::cout << "Album Name: " << album.name << std::endl;
```

#### Web Details:
| Endpoint                         | Method |
|----------------------------------|--------|
|https://api.spotify.com/v1/albums | GET    |

#### Notes:
None

---

### `getAlbums(const std::vector<std::string>& ids, const std::optional<std::string>& market = std::nullopt)`

Retrieves mulitple albums by their Spotify IDs.

*See Also [Spotify API Reference - Get Several Albums](https://developer.spotify.com/documentation/web-api/reference/get-multiple-albums)*

#### Parameters:

| Name  | Type                         | Description                      |
|-------|------------------------------|----------------------------------|
| id    | `std::vector<std::string>`   | Spotify album IDs                |
| market| `std::optional<std::string>` | Optional ISO 3166-1 Country Code |

#### Returns: [`AlbumListObject`]()

#### Throws:

- [`Spotify::APIException`]() on an API Error
- [`Spotify::NetworkException`]() on network failure

#### Example:

[Try It Yourself]()

```c++
std::vector<std::string> album_ids = {
	Spotify::Parse::extractID("https://open.spotify.com/album/1U3qu4gDfohAqFrmpLT11l"),
	Spotify::Parse::extractID("https://open.spotify.com/album/6bpiy8pVcojYwKAHYknp0A")
};
auto albums = client.album().getAlbums(album_ids);

for (const auto album : albums) {
	std::cout << "Album Name: " << album.name << std::endl;
}
```

#### Web Details:
| Endpoint                         | Method |
|----------------------------------|--------|
|https://api.spotify.com/v1/albums | GET    |

#### Notes:
- A Maximum of 20 ids can be submitted in the `id` field at once

---

### `getAlbumTracks(const std::string& id, const std::optional<std::string>& market, const std::optional<int>& limit, const std::optional<int>& offset)`

Retrieves the tracks of an album from an album ID

*See Also: [Spotify API Reference - Get Album Tracks](https://developer.spotify.com/documentation/web-api/reference/get-an-albums-tracks)*


#### Parameters:

| Name   | Type                         | Description                          |
|--------|------------------------------|--------------------------------------|
| id     | `std::string`                | Spotify album ID                     |
| market | `std::optional<std::string>` | Optional ISO 3166-1 Country Code     |
| limit  | `std::optional<int>`         | The maximum number of items to return|
| offset | `std::optional<int>`         |The index of the first item to return |

#### Returns: [`PagedTrackObject`]()

#### Throws:

- [`Spotify::APIException`]() on an API Error
- [`Spotify::NetworkException`]() on network failure

#### Example:

[Try It Yourself]()

```c++
auto album_id = Spotify::Parse::extractID("https://open.spotify.com/album/1U3qu4gDfohAqFrmpLT11l");
auto tracks = client.album().getAlbumTracks(album_id);

for (const auto tracks : tracks) {
	std::cout << "Track Name: " << track.name << std::endl;
}
```

#### Web Details:
| Endpoint                                     | Method |
|----------------------------------------------|--------|
|https://api.spotify.com/v1/albums/{id}/tracks | GET    |

#### Notes:
- `limit` parameter has range 1-50 (inclusive)
- If the `limit` parameter is omitted 20 items will be returned.
- If the `offset` parameter is omitted it will start at 0

---

### Continue