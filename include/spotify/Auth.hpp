//
// Created by Harry Skerritt on 18/12/2025.
//

#ifndef AUTH_H
#define AUTH_H

#include <random>
#include <utility>
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <curl/curl.h>

namespace Spotify {

    struct ClientKeys {
        std::string client_id;
        std::string client_secret;
    };

    struct AuthResponse {
        std::string access_token;
        std::string token_type;
        std::string scope;
        int expires_in;
        std::string refresh_token;
    };

    class Auth {
        // Funcs
        public:
        Auth(ClientKeys keys );
        ~Auth() = default; // Todo: for now

        AuthResponse authenticateClient();



        private:
        std::string generateRandomState(size_t length = 16);
        std::string urlEncode(const std::string &value);
        void requestAuthorisation();

        // Vars
        public:
        private:
        ClientKeys m_keys;
    };
}



#endif //AUTH_H
