#include "../include/Graphics.h"

Graphics::Graphics() {
	factory = nullptr;
	renderTarget = nullptr;
	brush1 = nullptr;
	brush2 = nullptr;
}

Graphics::~Graphics() {
	// Release all the COM objects.
	if (factory) {
		factory->Release();
	}
	if (renderTarget) {
		renderTarget->Release();
	}
	if (brush1) {
		brush1->Release();
	}
	if (brush2) {
		brush2->Release();
	}
}

bool Graphics::Init(HWND hWnd) {

	// Configure the factory.
	HRESULT hr = D2D1CreateFactory(
		D2D1_FACTORY_TYPE_SINGLE_THREADED,
		&factory);

	if (hr != S_OK) {
		return false;
	}

	// Specify where the drawing will happen.
	RECT rect;
	GetClientRect(hWnd, &rect);
	hr = factory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(
			hWnd, D2D1::SizeU(rect.right, rect.bottom)),
		&renderTarget);

	if (hr != S_OK) {
		return false;
	}

	// Create the drawing type with the brush.
	hr = renderTarget->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0, 0), &brush1);
	hr = renderTarget->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0, 0), &brush2);

	if (hr != S_OK) {
		return false;
	}

	// If every hResult is fine return true and continue.
	else {
		return true;
	}
}

void Graphics::ClearScreen(float r, float g, float b) {
	// Clearing the background.
	renderTarget->Clear(D2D1::ColorF(r, g, b));
}

// A simple draw circle for testing.
void Graphics::DrawCircle(float x, float y, float radius, float r, float g, float b, float a) {
	brush1->SetColor(D2D1::ColorF(r, g, b, a));
	renderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), brush1, 3.0f);
}

void Graphics::DrawButton(float x, float y, float width, float height, float radius, float r, float g, float b, float a)
{
	brush1->SetColor(D2D1::ColorF(r - 0.1f, g - 0.1f, b - 0.1f, a));
	brush2->SetColor(D2D1::ColorF(r, g, b, a));
	renderTarget->FillRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(x, y, x + width, y + height), radius, radius), brush2);
	renderTarget->DrawRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(x, y, x + width, y + height), radius, radius), brush1, 2.0f);
}
