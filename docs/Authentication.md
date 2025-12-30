# Authentication

## Authorization Code Flow
*Note: [Authorisation Code Flow](https://developer.spotify.com/documentation/web-api/tutorials/code-flow) is the only flow implemented within the library at the moment*

The steps below outline how to use OAuth2 to obtain a Spotify authorisation token.

## Step 1 - Generate an Authorisation URL
The library provides an easy way to generate an authorisation URL

This method can be seen below

```c++
// Step 1: Generate the authorization URL
auto url = auth.createAuthoriseURL(
    "http://127.0.0.1:8888/callback",
    {
        Spotify::Scope::UserReadPlaybackState, 
        Spotify::Scope::UserReadCurrentlyPlaying
    });
```

**⚠️ The redirect URI must match exactly what is registered in your Spotify developer app, including trailing slashes.**

See information on [`Scopes`]()

## Step 2 - Capture the code
Once you have the authorisation URL the user will need to click it an allow the app access.

This will then send them to the input redirect uri with a code as part of its url. 
This can either be captured manually in a way you choose, but the library does provide easy ways of doing this

The [`AuthServer`]() can make capturing the code easy:

```c++
// Step 2: Capture the access code
Spotify::AuthServer::openBrowser(url);
std::string code = Spotify::AuthServer::waitForCode("127.0.0.1", 8888);
```

The `waitForCode` function will return the code

## Step 3 - Exchange the Code

The code is not the token we need quite yet, however the one line of code below can exchange the code for the token

```c++
// Step 3: Exchange code for token
auth.exchangeCode(code);
```

See information on [`AuthReponse`]()


## Step 4 - Refreshing Access Token

The access token is only valid for 3600 seconds (1 hour)

After this time it needs refreshing

The `.getAccessToken()` method within the `Client` handles this refresh automatically,
but it can be done manually as explained below.

```c++
// Step 4: Refresh access token once expired
auth.refreshAccessToken();
```

See more on [`.getAccessToken()`]()

# Full Flow Example

```c++
Auth auth({client_key, client_secret});
auto url = auth.createAuthoriseURL("http://127.0.0.1:8888/callback", {Scope::UserReadPlaybackState});
AuthServer::openBrowser(url);
std::string code = AuthServer::waitForCode("127.0.0.1", 8888);
auth.exchangeCode(code);

Client client(auth); // Now ready to make API requests
```

### Notes
- Keep your Client ID and Secret private. **Do not** commit them publicly.
- Tokens expire - refresh them for long-running applications.
- Scopes must match the endpoints you intend to call.