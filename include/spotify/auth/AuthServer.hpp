//
// Created by Harry Skerritt on 20/12/2025.
//

#ifndef AUTHSERVER_H
#define AUTHSERVER_H

#pragma once

#include <optional>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <iostream>

namespace Spotify {
    class AuthServer {
        public:

        /// Waits for an authorization code using a local callback server
        /// @param auth_url Authorization URL to open
        /// @param port Local port to listen on
        /// @param html_file_path HTML file to serve after authorization (optional)
        /// @param suppress Suppresses console messages (optional)
        static std::string waitForCode(
            const std::string &auth_url,
            int port = 8888,
            const std::optional<std::filesystem::path> &html_file_path = std::nullopt,
            bool suppress = false
        );

        /// Open the browser to a url
        /// @param url Webpage to open
        static void openBrowser(const std::string& url);

    };
}

#endif //AUTHSERVER_H
