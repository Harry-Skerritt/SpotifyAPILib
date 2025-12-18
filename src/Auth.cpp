//
// Created by Harry Skerritt on 18/12/2025.
//

#include <iostream>
#include <spotify/Auth.hpp>


Spotify::Auth::Auth(ClientKeys keys) {
    m_keys = std::move(keys);
}

Spotify::AuthResponse Spotify::Auth::authenticateClient() {
    AuthResponse response;
    requestAuthorisation();

    // Post to /authorize
    // Exchange code for token
    // POST to /api/token
    // Get reponse

    return response;
}

void Spotify::Auth::requestAuthorisation() {
    CURL *curl;
    CURLcode result;

    result = curl_global_init(CURL_GLOBAL_DEFAULT);
    if (result)
    {
        std::cout << result << std::endl;
        return;
    }

    auto scope = "user-read-private user-read-email";
    auto redirect_uri = "http://127.0.0.1:8888/callback";
    auto state = generateRandomState();

    std::ostringstream oss;
    oss << "response_type=code"
    << "&client_id=" << urlEncode(m_keys.client_id)
    << "&scope=" << urlEncode(scope)
    << "&redirect_uri=" << urlEncode(redirect_uri)
    << "&state=" << urlEncode(state);

    std::cout << "Please visit the following url: " << std::endl;
    std::cout << " https://accounts.spotify.com/authorize?" << oss.str() << std::endl;

    /*
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://accounts.spotify.com/authorize");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, oss.str().c_str());

        result = curl_easy_perform(curl);
        if (result != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));

        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
    */
}

// Helpers
std::string Spotify::Auth::generateRandomState(size_t length) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 255);

    std::ostringstream oss;
    for (size_t i = 0; i < length; ++i) {
        oss << std::hex << std::setw(2) << std::setfill('0') << dis(gen);
    }
    return oss.str();
}

std::string Spotify::Auth::urlEncode(const std::string &value) {
    std::ostringstream escaped;
    escaped.fill('0');
    escaped << std::hex;

    for (char c : value) {
        if (isalnum((unsigned char)c) || c == '-' || c == '_' || c == '.' || c == '~') {
            escaped << c;
        } else {
            escaped << '%' << std::uppercase << std::setw(2) << int((unsigned char)c) << std::nouppercase;
        }
    }

    return escaped.str();
}
