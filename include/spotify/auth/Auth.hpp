//
// Created by Harry Skerritt on 18/12/2025.
//

#ifndef AUTH_H
#define AUTH_H

#pragma once

#include <random>
#include <utility>
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>

#include "spotify/models/Scopes.hpp"
#include "spotify/internal.hpp"



namespace Spotify {

    class Auth {
        // Funcs
        public:
        explicit Auth(const ClientCredentials& credentials);
        ~Auth() = default;

        // OAuth2 Flow
        /// Creates a Spotify authorisation URL for OAuth authentication
        /// @param redirectUri Redirect URI configured in the Spotify Developer Dashboard
        /// @param scopes Scopes to request access for
        /// @param state Optional state value for CSRF protection
        /// @return Authorisation URL
        std::string createAuthoriseURL(
            const std::string &redirectUri,
            const std::vector<Scope> &scopes,
            const std::optional<std::string>& state = std::nullopt);

        /// Exchanges an authorization code for access and refresh tokens
        /// @param code Authorization code received from Spotify
        void exchangeCode(const std::string &code);

        /// Refreshes the current access token
        /// @param refresh_token Optional refresh token to use instead of the stored one
        void refreshAccessToken(const std::optional<std::string>& refresh_token = std::nullopt);


        // Getters
        /// Returns the current access token
        std::string getAccessToken();

        private:
        AuthResponse buildAuthResponse(const std::string& json);
        [[nodiscard]] std::string encodeClientCredentials() const;
        bool isTokenExpired() const;


        // Vars
        private:
        ClientCredentials m_credentials;
        std::string m_redirectUri;
        AuthResponse m_authResponse;
        std::string m_refresh_token;

    };
}



#endif //AUTH_H
