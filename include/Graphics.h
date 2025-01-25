#pragma once

#include "windecs.h"

// Simple enum for the app's UI states.
enum AppState {
    LOGIN_SCREEN,
    HOME_SCREEN,
    CHAT_SCREEN
};

class Graphics {
public:
    Graphics();
    ~Graphics();

    // Initialization
    bool Init(HWND hWnd);

    // Begin/End drawing
    void BeginDrawing();
    void EndDrawing();

    // Resizing
    void Resize(int newWidth, int newHeight);

    // Main UI draw
    void DrawInterface();

    // Helper drawing functions
    void ClearScreen(float r, float g, float b);
    void DrawButton(float x, float y, float width, float height, float radius,
        float r, float g, float b, float a);
    void DrawText(const wchar_t* text, float x, float y, float width, float height,
        float sizeWord, float r, float g, float b, float a);

    // Mouse click handling
    void UpdateMouseClick(float mouseX, float mouseY);
    bool HitTest(float mouseX, float mouseY, float x, float y, float width, float height);

    // State getters/setters
    AppState GetState() const { return currentState; }
    void SetState(AppState s) { currentState = s; }

public:
    // Flags set by UpdateMouseClick that the App reads
    // (so we don't have to re-check exact coordinates in App)
    int  homeOptionSelected; // 0 = none, 1 = create server, 2 = join server, 3 = delete
    bool chatSendClicked;    // Did the user click the "send test message" button?

private:
    // D2D resources
    ID2D1Factory* factory;
    ID2D1HwndRenderTarget* renderTarget;

    // Basic brushes
    ID2D1SolidColorBrush* brush1;
    ID2D1SolidColorBrush* brush2;
    ID2D1SolidColorBrush* brush3;

    // Current screen
    AppState currentState;
};
