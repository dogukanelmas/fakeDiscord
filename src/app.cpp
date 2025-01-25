#include "../include/app.h"
#include <Windows.h>
#include <string>

// Example hardcoded port for demonstration
static constexpr int DEFAULT_PORT = 54000;

// If you need user-typed input for IP addresses,
// you'd implement a custom dialog or an edit control. 
// For now, we hardcode or "simulate" an IP prompt.
std::string PromptForIP() {
    // Return a placeholder IP. If using Hamachi, put your Hamachi IP here.
    return "25.47.50.203";
}

App::App()
    : wnd(800, 600, L"Escord")
{
}

int App::Init() {
    if (!network.initialize()) {
        return -1;
    }

    while (true) {
        if (auto ecode = Window::ProccessMessages()) {
            network.cleanup();
            return *ecode;
        }

        // Check for incoming messages from server/clients
        network.checkNetworkEvents();

        Update();
    }
}

App::~App() {
    network.cleanup();
}

void App::Update() {
    auto& gfx = wnd.Gfx();

    // If we're on HOME_SCREEN, see if the user clicked "Create Server," "Join Server," etc.
    if (gfx.GetState() == HOME_SCREEN) {
        HandleHomeActions();
    }
    else if (gfx.GetState() == CHAT_SCREEN) {
        HandleChatActions();
    }

    // Render
    gfx.BeginDrawing();
    gfx.DrawInterface();
    gfx.EndDrawing();
}

void App::HandleHomeActions() {
    auto& gfx = wnd.Gfx();
    switch (gfx.homeOptionSelected) {
    case 1: { // Create Server
        std::string ip = PromptForIP();
        if (!network.startServer(ip, DEFAULT_PORT)) {
            MessageBoxA(nullptr, "Could not start server!", "Error", MB_OK);
        }
        else {
            // The host also connects to their own server
            if (!network.connectToServer(ip, DEFAULT_PORT)) {
                MessageBoxA(nullptr, "Failed to connect to our own server!", "Error", MB_OK);
            }
            else {
                gfx.SetState(CHAT_SCREEN);
            }
        }
    } break;

    case 2: { // Join Server
        std::string ip = PromptForIP();
        if (!network.connectToServer(ip, DEFAULT_PORT)) {
            MessageBoxA(nullptr, "Could not connect to server!", "Error", MB_OK);
        }
        else {
            gfx.SetState(CHAT_SCREEN);
        }
    } break;

    case 3: { // Delete Server (not implemented)
        MessageBoxA(nullptr, "Delete server not implemented yet!", "Info", MB_OK);
    } break;

    default:
        // No action
        break;
    }

    // Reset the selection to avoid repeating the same action
    gfx.homeOptionSelected = 0;
}

void App::HandleChatActions() {
    auto& gfx = wnd.Gfx();
    if (gfx.chatSendClicked) {
        // The user clicked "Send Test Msg"
        network.sendMessageToAll("Hello from me!");
        gfx.chatSendClicked = false;
    }
}
