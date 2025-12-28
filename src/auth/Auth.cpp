//
// Created by Harry Skerritt on 18/12/2025.
//

#include "spotify/auth/Auth.hpp"

#include "spotify/core/Errors.hpp"


namespace Spotify {
    // CURL Helper
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
        ((std::string*)userp)->append((char*)contents, size * nmemb);
        return size * nmemb;
    }



    Spotify::Auth::Auth(const ClientCredentials& keys) {
        if (keys.client_id.empty() || keys.client_secret.empty()) {
            throw Spotify::LogicException("ClientCredentials cannot be empty");
        }
        m_credentials = keys;
    }

    std::string Auth::createAuthoriseURL(
        const std::string& redirect_uri,
        const std::vector<Scope>& scopes,
        const std::optional<std::string>& state)
    {
        if (redirect_uri.empty()) throw LogicException("Redirect URI cannot be empty.");

        std::string scope_str = buildScopeString(scopes);
        auto actual_state = state.value_or(WebTools::generateRandomState());
        m_redirectUri = redirect_uri;

        std::ostringstream oss;
        oss << "response_type=code"
        << "&client_id=" << WebTools::urlEncode(m_credentials.client_id)
        << "&scope=" << WebTools::urlEncode(scope_str)
        << "&redirect_uri=" << WebTools::urlEncode(redirect_uri)
        << "&state=" << WebTools::urlEncode(actual_state);

        return "https://accounts.spotify.com/authorize?"+ oss.str();
    }

    void Auth::exchangeCode(const std::string &code) {

        if (code.empty()) throw Spotify::LogicException("Authorization Code cannot be empty.");

        CURL *curl;
        CURLcode result;
        curl_slist *headers = NULL;

#if WIN32
    result = curl_global_init(CURL_GLOBAL_ALL);
    if (result)
        return (int) result;
#endif

        // Post Fields
        std::ostringstream post_fields;
        post_fields << "code=" << WebTools::urlEncode(code)
                    << "&redirect_uri=" << WebTools::urlEncode(m_redirectUri)
                    << "&grant_type=authorization_code";
        std::string body_str = post_fields.str();


        // Auth Header
        std::string auth_header = "Authorization: Basic " + encodeClientCredentials();

        long http_code = 0;
        std::string response_str;

        curl = curl_easy_init();
        if (curl) {
            // Setting headers
            headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");
            headers = curl_slist_append(headers, auth_header.c_str());


            curl_easy_setopt(curl, CURLOPT_URL, "https://accounts.spotify.com/api/token");
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
            curl_easy_setopt(curl, CURLOPT_POST, 1L);

            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body_str.c_str());
            curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)body_str.length());

            curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_str);

            result = curl_easy_perform(curl);

            // Handle a CURL error - Network Level
            if (result != CURLE_OK) {
                std::string err = curl_easy_strerror(result);
                curl_slist_free_all(headers);
                curl_easy_cleanup(curl);
                throw Spotify::NetworkException(err);
            }

            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
            curl_slist_free_all(headers);
            curl_easy_cleanup(curl);
        }
#if WIN32
    curl_global_cleanup();
#endif


        // API bad response
        if (http_code != 200) {
            HTTP::Result fake_result { static_cast<RFC2616_Code>(http_code), response_str };
            ErrorHandler::verifyResponse(fake_result);
        }

        // API Good response
        buildAuthResponse(response_str);
    }

    void Spotify::Auth::refreshAccessToken(const std::optional<std::string>& refresh_token) {
        std::string token_to_use = refresh_token.value_or(m_refresh_token);
        if (token_to_use.empty()) {
            throw Spotify::LogicException("No refresh token available");
        }

        CURL *curl;
        CURLcode result;
        curl_slist *headers = NULL;


#if WIN32
    result = curl_global_init(CURL_GLOBAL_ALL);
    if (result)
        return (int) result;
#endif

        // Post Fields
        std::ostringstream post_fields;
        post_fields << "grant_type=refresh_token"
                    << "&refresh_token=" << WebTools::urlEncode(refresh_token.value_or(m_refresh_token))
                    << "&client_id=" << WebTools::urlEncode(m_credentials.client_id);
        std::string body_str = post_fields.str();

        std::string auth_header = "Authorization: Basic " + encodeClientCredentials();

        long http_code = 0;
        std::string response_str;

        curl = curl_easy_init();
        if (curl) {
            // Setting headers
            headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");
            headers = curl_slist_append(headers, auth_header.c_str());

            curl_easy_setopt(curl, CURLOPT_URL, "https://accounts.spotify.com/api/token");
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
            curl_easy_setopt(curl, CURLOPT_POST, 1L);

            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body_str.c_str());
            curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)body_str.length());

            curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_str);

            result = curl_easy_perform(curl);

            // Handle a CURL error - Network Level
            if (result != CURLE_OK) {
                std::string err = curl_easy_strerror(result);
                curl_slist_free_all(headers);
                curl_easy_cleanup(curl);
                throw Spotify::NetworkException(err);
            }

            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
            curl_slist_free_all(headers);
            curl_easy_cleanup(curl);
        }
#if WIN32
    curl_global_cleanup();
#endif

        // API bad response
        if (http_code != 200) {
            HTTP::Result fake_result { static_cast<RFC2616_Code>(http_code), response_str };
            ErrorHandler::verifyResponse(fake_result);
        }

        // API Good response
        buildAuthResponse(response_str);
    }

    // Getters
    std::string Spotify::Auth::getAccessToken() {
        if (isTokenExpired()) {
            refreshAccessToken();
        }

        return m_authResponse.access_token;
    }


    Spotify::AuthResponse Spotify::Auth::getAuthResponse() const {
        return m_authResponse;
    }


    // --- PRIVATE ---
    // Helpers
    Spotify::AuthResponse Spotify::Auth::buildAuthResponse(const std::string &json) {
        AuthResponse response;

        // API good response
        // Store 'easy' values
        response.access_token = WebTools::extractValue(json, "access_token");
        response.token_type = WebTools::extractValue(json, "token_type");
        response.scope = WebTools::extractValue(json, "scope");

        // Workout when the expiry time is
        int expires_in = WebTools::extractIntValue(json, "expires_in");
        response.expire_time = std::chrono::system_clock::now() + std::chrono::seconds(expires_in);

        // Store the refresh on its own too
        m_refresh_token = WebTools::extractValue(json, "refresh_token");
        response.refresh_token = m_refresh_token;

        if (response.access_token.empty()) {
            throw Spotify::ParseException("No access token provided in response", "");
        }

        response.response_code = RFC2616_Code::OK;
        m_authResponse = response;
        return response;
    }

    std::string Spotify::Auth::encodeClientCredentials() const {
        std::string client_creds = m_credentials.client_id + ":" +  m_credentials.client_secret;
        std::string encoded = base64_encode(client_creds);
        return encoded;
    }

    bool Spotify::Auth::isTokenExpired() const {
        return std::chrono::system_clock::now() >= m_authResponse.expire_time;
    }
}



