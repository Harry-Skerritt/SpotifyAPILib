# Parsing

This page documents the `Spotify::Parse` namespace, which provides utility functions for extracting and validating **Spotify IDs** and **Spotify URIs** from URLs or URIs

All functions can be used via the `Spotify::Parse::` namespace

---

## Table of Contents

- [Overview](#overview)
- [ID Functions](#id-functions)
- [URI Functions](#uri-functions)


## Overview

The Spotify Parser allows you to:

- Validate Spotify IDs (`22-character Base62 strings`)
- Extract IDs from Spotify URLs or URIs
- Convert URLs into Spotify URIs
- Handle errors gracefully with throwing and non-throwing variants


## ID Functions

### `isValidID(const std::string &id)`

Checks whether a string matches the **Spotify ID format**

| Parameter | Type                  | Description                                   |
|-----------|-----------------------|-----------------------------------------------|
| `id`      |  `const std::string&` | Spotify ID (e.g., `"6IVkf5av5jnraZpLPszoZR"`) |

**Returns:**

`true` if the ID is 22 alphanumeric characters, otherwise `false`

**Example:**

```c++
bool valid = Spotify::Parse::isValidID("6IVkf5av5jnraZpLPszoZR");

```
---

### `extractID(const std::string &input)`

Extracts and validates a Spotify ID from a URL or URI

| Parameter   | Type                 | Description                                                                        |
|-------------|----------------------|------------------------------------------------------------------------------------|
| `input`     | `const std::string&` | Spotify URL or URI (`https://open.spotify.com/track/{id}` or `spotify:track:{id}`) |

**Returns**

A `std::string` containing a valid Spotify ID

**Throws**

`InvalidIDException` if the extracted ID is invalid

**Example**

```c++
std::string id = Spotify::Parse::extractID("https://open.spotify.com/track/6IVkf5av5jnraZpLPszoZR");
```
---

### `tryExtractID(const std::string &input, std::string* error = nullptr)`

Non-throwing version of `extractID`

| Parameter   | Type                 | Description                               |
|-------------|----------------------|-------------------------------------------|
| `input`     | `const std::string&` | Spotify URL or URI                        |
| `error`     | `std::string*`       | Optional pointer to receive error message |

**Returns**
`std::optional<std::string>`: valid Spotify ID or `std::nullopt` on failure

**Example**

```c++
std::string error;
auto id_opt = Spotify::Parse::tryExtractID("spotify:track:INVALID", &error);
if (!id_opt) std::cout << "Failed: " << error << std::endl;
```
---

### `extractIDs(const std::vector<std::string>& input)`

Extracts multiple Spotify IDs from a vector of URLs or URIs

| Parameter    | Type                              | Description                    |
|--------------|-----------------------------------|--------------------------------|
| `input`      | `const std::vector<std::string>&` | Vector of Spotify URLs or URIs |


**Returns**

`std::vector<std::string>` of valid IDs


**Throws**

`InvalidIDException` if any ID is invalid

**Example**

```c++
std::vector<std::string> urls = {
    "https://open.spotify.com/track/6IVkf5av5jnraZpLPszoZR",
    "spotify:track:3n3Ppam7vgaVa1iaRUc9Lp"
};
auto ids = Spotify::Parse::extractIDs(urls);

```

---

### `tryExtractIDs(const std::vector<std::string>& input, std::string* error = nullptr)`

Non-throwing variant of `extractIDs`

| Parameter    | Type                              | Description                               |
|--------------|-----------------------------------|-------------------------------------------|
| `input`      | `const std::vector<std::string>&` | Vector of Spotify URLs or URIs            |
| `error`      | `std::string*`                    | Optional pointer to receive error message |

**Returns** 

`std::optional<std::vector<std::string>>` of valid Spotify IDs, or `std::nullopt` if any fail.

**Example**

```c++
std::string error;
auto ids_opt = Spotify::Parse::tryExtractIDs(urls, &error);
if (!ids_opt) std::cout << "Failed: " << error << std::endl;

```

---

## URI Functions

### `extractURI(const std::string &input)`

Converts a Spotify URL or URI into a validated Spotify URI (`spotify:{type}:{id}`)

| Parameter      | Type                   | Description         |
|----------------|------------------------|---------------------|
| `input`        | `const std::string&`   |  Spotify URL or URI |


**Returns**

`std::string` of the Spotify URI

**Throws**

`InvalidResourceException` if the resource type is unsupported

`InvalidIDException` if the extracted ID is invalid

**Example**

```c++
std::string uri = Spotify::Parse::extractURI("https://open.spotify.com/track/6IVkf5av5jnraZpLPszoZR");
// uri -> "spotify:track:6IVkf5av5jnraZpLPszoZR"
```

---

### `tryExtractURI(const std::string &input, std::string* error = nullptr)`

Non-throwing version of `extractURI`

| Parameter   | Type                 | Description                               |
|-------------|----------------------|-------------------------------------------|
| `input`     | `const std::string&` | Spotify URL or URI                        |
| `error`     | `std::string*`       | Optional pointer to receive error message |


**Returns**

`std::optional<std::string>`: valid Spotify ID or `std::nullopt` on failure

**Example**

```c++
std::string error;
auto uri_opt = Spotify::Parse::tryExtractURI("spotify:track:INVALID", &error);
if (!uri_opt) std::cout << "Failed: " << error << std::endl;
```
---

### `extractURIs(const std::vector<std::string>& input)`

Extracts multiple Spotify URIs from a vector of URLs or URIs

| Parameter    | Type                              | Description                    |
|--------------|-----------------------------------|--------------------------------|
| `input`      | `const std::vector<std::string>&` | Vector of Spotify URLs or URIs |


**Returns**
`std::vector<std::string>` of valid URIs


**Throws**

`InvalidResourceException` if any resource type is invalid

`InvalidIDException` if any ID is invalid


**Example**

```c++
std::vector<std::string> urls = {
    "https://open.spotify.com/track/6IVkf5av5jnraZpLPszoZR",
    "https://open.spotify.com/album/1ATL5GLyefJaxhQzSPVrLX"
};
auto uris = Spotify::Parse::extractURIs(urls);
```
---

### `tryExtractURIs(const std::vector<std::string>& input, std::string* error = nullptr)`

Non-throwing version of `extractURIs`

| Parameter    | Type                              | Description                               |
|--------------|-----------------------------------|-------------------------------------------|
| `input`      | `const std::vector<std::string>&` | Vector of Spotify URLs or URIs            |
| `error`      | `std::string*`                    | Optional pointer to receive error message |

**Returns**

`std::optional<std::vector<std::string>>` of valid URIs, or `std::nullopt` if any fail.

**Example**

```c++
std::string error;
auto uris_opt = Spotify::Parse::tryExtractURIs(urls, &error);
if (!uris_opt) std::cout << "Failed: " << error << std::endl;
```



## Notes

Use `tryExtract*` functions for safe parsing without exceptions.

All ID validation assumes 22-character Base62 strings.

URI functions automatically determine the resource type (`track`, `album`, `playlist`, etc.) from the URL or URI.



