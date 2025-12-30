# Getting Started

## Step 1 - Creating a Spotify Developer App

To use this library you need a Spotify developer account, along with an active Spotify developer app

- Go to [Spotify Developer Dashboard](https://developer.spotify.com/dashboard)
- Create a new app and obtain a **Client ID** and **Client Secret**
- Set the redirect URI (e.g. `http://127.0.0.1:8888/callback`)

## Step 2 - Load Credentials

There are different ways to load the credentials in. 

This library does provide a way to load from a `.env` file an example of which is below

```c++
#include <spotify/spotify.hpp>
#include <Tools.hpp>

Tools::loadEnv("/path/to/.env");
const char* client_key = std::getenv("SPOTIFY_CLIENT_KEY");
const char* client_secret = std::getenv("SPOTIFY_CLIENT_SECRET");
Spotify::Auth auth({client_key, client_secret});
```

## Step 3 - Authorisation

The steps to authorise you app are [here!](/docs/Authentication.md)