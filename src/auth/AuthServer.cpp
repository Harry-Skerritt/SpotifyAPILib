//
// Created by Harry Skerritt on 20/12/2025.
//

#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>


#include "spotify/auth/AuthServer.hpp"

#include "spotify/core/Errors.hpp"

namespace Spotify {
    void AuthServer::openBrowser(const std::string &url) {
#if defined(_WIN32)
        std::string command = "start " + url;
#elif defined(__APPLE__)
        std::string command = "open \"" + url + "\"";
#else
        std::string command = "xdg-open \"" + url + "\"";
#endif
        int result = std::system(command.c_str());
        if (result != 0) {
            throw Spotify::Exception("AuthServer: Failed to execute browser open command");
        }
    }

    std::string AuthServer::waitForCode(
    const std::string &auth_url, // On desktop this was the host, on ESP32 we usually ignore or use for logging
    int port,
    const std::optional<std::string> &custom_html, // Now a string, not a path
    bool suppress)
    {
        WebServer server(port);
        std::string captured_code;

        // Default HTML if custom_html isn't provided
        std::string response_html = "<html><body style='font-family:sans-serif; text-align:center; padding-top:50px;'>"
                                    "<h1>Authenticated!</h1><p>You can close this tab and return to the app.</p>"
                                    "</body></html>";

        if (custom_html.has_value()) {
            response_html = custom_html.value();
        }

        // Setup server endpoint
        server.on("/callback", [&]() {
            if (server.hasArg("code")) {
                captured_code = server.arg("code").c_str();
                server.send(200, "text/html", response_html.c_str());

                // We can't call server.stop() immediately inside the lambda
                // because we need to finish sending the response.
            } else {
                server.send(400, "text/plain", "Error: No code received");
            }
        });

        server.begin();

        // Loop until code is captured
        // Note: In a production library, you should add a timeout here
        // so the ESP32 doesn't hang forever if the user never logs in.
        while (captured_code.empty()) {
            server.handleClient();
            delay(2); // Feed the watchdog timer
        }

        server.stop();
        return captured_code;
    }
}


