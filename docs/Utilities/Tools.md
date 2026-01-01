# Tools

This page documents the utility tools provided by the library.

All tools are available under the `Tools::` namespace, e.g., `Tools::loadEnv()`.

--- 
## `loadEnv(const std::string& filename)`

Loads environment variables from a `.env` file so they can be accessed with `std::getenv`.

| Parameter    | Type                   | Description           |
|--------------|------------------------|-----------------------|
| `filename`   | `const std::string&`   | Path to a `.env` file |

**Example:**

```cpp
Tools::loadEnv("/path/to/.env");
const char* client_key = std::getenv("SPOTIFY_CLIENT_KEY");
```
---

## `isValidMarket(const std::string& market)`
Checks if the given market string is a valid ISO 3166 country code.

| Parameter | Type                   | Description                                            |
|-----------|------------------------|--------------------------------------------------------|
| `market`  | `const std::string&`   | ISO 3166-1 alpha-2 country code (e.g., `"GB"`, `"US"`) |


**Example**
```c++
bool valid = isMarketValid("GB");
```


**Returns:**
`true` if the market is valid, `false` otherwise.

---

## `getISOTimestamp()`

Returns the current time as an ISO 8601 formatted timestamp, e.g., `2023-01-15T14:30:00Z`

**Example**
```c++
std::string timestamp = Tools::getISOTimestamp();
std::cout << timestamp; // "2026-01-01T12:00:00Z"
```

---
## `formatMs(long long ms)`

Converts a duration in milliseconds into a human-readable string in HH:MM format.

| Parameter | Type        | Description                |
|-----------|-------------|----------------------------|
| `ms`      | `long long` | Duration in milliseconds   |

**Example**
```c++
std::string duration = Tools::formatMs(185000);
std::cout << duration; // "3:05"
```
---

## Notes
- Use loadEnv() at the start of your program to easily access your Spotify keys.
- isValidMarket() is useful when making API calls that require a country/market parameter.
- getISOTimestamp() is handy for logging or timestamping events.
- formatMs() simplifies converting track durations to a user-friendly display format.