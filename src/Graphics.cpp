#include "../include/Graphics.h"
#include <d2d1.h>
#include <dwrite.h>
#include <string>

// Link to libs
#pragma comment(lib, "d2d1")
#pragma comment(lib, "dwrite")

Graphics::Graphics()
    : factory(nullptr),
    renderTarget(nullptr),
    brush1(nullptr),
    brush2(nullptr),
    brush3(nullptr),
    currentState(LOGIN_SCREEN),
    homeOptionSelected(0),
    chatSendClicked(false)
{
}

Graphics::~Graphics() {
    if (brush3) brush3->Release();
    if (brush2) brush2->Release();
    if (brush1) brush1->Release();
    if (renderTarget) renderTarget->Release();
    if (factory) factory->Release();
}

bool Graphics::Init(HWND hWnd) {
    HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);
    if (hr != S_OK) {
        return false;
    }

    RECT rect;
    GetClientRect(hWnd, &rect);
    hr = factory->CreateHwndRenderTarget(
        D2D1::RenderTargetProperties(),
        D2D1::HwndRenderTargetProperties(
            hWnd, D2D1::SizeU(rect.right, rect.bottom)),
        &renderTarget
    );
    if (hr != S_OK) {
        return false;
    }

    // Create a few brushes
    renderTarget->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0), &brush1);
    renderTarget->CreateSolidColorBrush(D2D1::ColorF(1, 1, 1), &brush2);
    renderTarget->CreateSolidColorBrush(D2D1::ColorF(0.5f, 0.5f, 1.0f), &brush3);

    return true;
}

void Graphics::BeginDrawing() {
    renderTarget->BeginDraw();
}
void Graphics::EndDrawing() {
    renderTarget->EndDraw();
}

void Graphics::Resize(int newWidth, int newHeight) {
    if (renderTarget) {
        renderTarget->Resize(D2D1::SizeU(newWidth, newHeight));
    }
}

void Graphics::ClearScreen(float r, float g, float b) {
    renderTarget->Clear(D2D1::ColorF(r, g, b));
}

void Graphics::DrawButton(float x, float y, float width, float height,
    float radius, float r, float g, float b, float a)
{
    brush1->SetColor(D2D1::ColorF(r - 0.2f, g - 0.2f, b - 0.2f, a));
    brush2->SetColor(D2D1::ColorF(r, g, b, a));

    D2D1_ROUNDED_RECT rr = D2D1::RoundedRect(
        D2D1::RectF(x, y, x + width, y + height),
        radius, radius
    );
    renderTarget->FillRoundedRectangle(rr, brush2);
    renderTarget->DrawRoundedRectangle(rr, brush1, 2.0f);
}

void Graphics::DrawText(const wchar_t* text, float x, float y,
    float width, float height,
    float sizeWord, float r, float g, float b, float a)
{
    IDWriteFactory* dwFactory = nullptr;
    IDWriteTextFormat* dwFormat = nullptr;
    ID2D1SolidColorBrush* textBrush = nullptr;

    // Create DirectWrite factory
    DWriteCreateFactory(
        DWRITE_FACTORY_TYPE_SHARED,
        __uuidof(IDWriteFactory),
        reinterpret_cast<IUnknown**>(&dwFactory)
    );

    dwFactory->CreateTextFormat(
        L"Arial", nullptr,
        DWRITE_FONT_WEIGHT_REGULAR,
        DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL,
        sizeWord,
        L"en-us",
        &dwFormat
    );

    renderTarget->CreateSolidColorBrush(D2D1::ColorF(r, g, b, a), &textBrush);

    D2D1_RECT_F layoutRect = D2D1::RectF(x, y, x + width, y + height);
    renderTarget->DrawText(
        text, (UINT32)wcslen(text),
        dwFormat, layoutRect, textBrush
    );

    if (textBrush) textBrush->Release();
    if (dwFormat) dwFormat->Release();
    if (dwFactory) dwFactory->Release();
}

void Graphics::DrawInterface() {
    float w = renderTarget->GetSize().width;
    float h = renderTarget->GetSize().height;
    ClearScreen(0.2f, 0.2f, 0.2f);

    switch (currentState)
    {
    case LOGIN_SCREEN:
        // Basic login placeholders
        DrawText(L"LOGIN SCREEN", 10, 10, 300, 50, 24.f, 1, 1, 1, 1);
        DrawText(L"Username", 50, 100, 200, 30, 18.f, 0.8f, 0.8f, 0.8f, 1);
        DrawText(L"Password", 50, 150, 200, 30, 18.f, 0.8f, 0.8f, 0.8f, 1);

        // "Login" button
        DrawButton(50, 200, 100, 40, 5.f, 0.3f, 0.7f, 0.3f, 1.f);
        DrawText(L"Login", 60, 205, 80, 30, 18.f, 0, 0, 0, 1.f);
        break;

    case HOME_SCREEN:
        DrawText(L"HOME SCREEN", 10, 10, 300, 50, 24.f, 1, 1, 1, 1);

        // "Create Server"
        DrawButton(50, 100, 120, 40, 5.f, 0.3f, 0.5f, 0.7f, 1.f);
        DrawText(L"Create Server", 60, 105, 110, 30, 14.f, 0, 0, 0, 1.f);

        // "Join Server"
        DrawButton(50, 160, 120, 40, 5.f, 0.7f, 0.5f, 0.2f, 1.f);
        DrawText(L"Join Server", 60, 165, 110, 30, 14.f, 0, 0, 0, 1.f);

        // "Delete Server" placeholder
        DrawButton(50, 220, 120, 40, 5.f, 0.5f, 0.2f, 0.2f, 1.f);
        DrawText(L"Delete Server", 60, 225, 110, 30, 14.f, 0, 0, 0, 1.f);
        break;

    case CHAT_SCREEN:
        DrawText(L"CHAT SCREEN", 10, 10, 300, 50, 24.f, 1, 1, 1, 1);
        DrawText(L"Connected. Click 'Send Test Msg' to send a message.", 50, 80, 500, 40,
            18.f, 0.8f, 0.8f, 0.8f, 1.f);

        // Button: "Send Test Msg"
        DrawButton(50, 160, 160, 40, 5.f, 0.3f, 0.8f, 0.3f, 1.f);
        DrawText(L"Send Test Msg", 60, 165, 140, 30, 16.f, 0, 0, 0, 1.f);
        break;
    }
}

void Graphics::UpdateMouseClick(float mouseX, float mouseY) {
    // Reset flags each time
    homeOptionSelected = 0;
    chatSendClicked = false;

    switch (currentState) {
    case LOGIN_SCREEN:
        // "Login" button is (50,200), size 100x40
        if (HitTest(mouseX, mouseY, 50, 200, 100, 40)) {
            // For now, pretend login success => go to HOME_SCREEN
            currentState = HOME_SCREEN;
        }
        break;

    case HOME_SCREEN:
        // "Create Server" => (50,100), 120x40
        if (HitTest(mouseX, mouseY, 50, 100, 120, 40)) {
            homeOptionSelected = 1;
        }
        // "Join Server" => (50,160), 120x40
        else if (HitTest(mouseX, mouseY, 50, 160, 120, 40)) {
            homeOptionSelected = 2;
        }
        // "Delete Server" => (50,220), 120x40
        else if (HitTest(mouseX, mouseY, 50, 220, 120, 40)) {
            homeOptionSelected = 3;
        }
        break;

    case CHAT_SCREEN:
        // "Send Test Msg" => (50,160), 160x40
        if (HitTest(mouseX, mouseY, 50, 160, 160, 40)) {
            chatSendClicked = true;
        }
        break;
    }
}

bool Graphics::HitTest(float mouseX, float mouseY, float x, float y,
    float width, float height)
{
    return (mouseX >= x && mouseX <= x + width &&
        mouseY >= y && mouseY <= y + height);
}
