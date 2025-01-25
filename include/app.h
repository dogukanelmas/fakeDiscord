#pragma once

#include "../include/window.h"
#include "../include/network.h"

class App {
public:
    App();
    int Init();
    ~App();

private:
    void Update();

    // Helper to handle home screen actions
    void HandleHomeActions();

    // Helper to handle chat screen (sending test msg)
    void HandleChatActions();

private:
    Window wnd;
    Network network;
};
