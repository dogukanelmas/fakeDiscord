#include "Graphics.h"

Graphics::Graphics() {
	factory = nullptr;
	renderTarget = nullptr;
	brush = nullptr;
}

Graphics::~Graphics() {
	if (factory) {
		factory->Release();
	}
	if (renderTarget) {
		renderTarget->Release();
	}
	if (brush) {
		brush->Release();
	}
}

bool Graphics::Init(HWND hWnd) {

	HRESULT hr = D2D1CreateFactory(
		D2D1_FACTORY_TYPE_SINGLE_THREADED,
		&factory);

	if (hr != S_OK) {
		return false;
	}

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

	hr = renderTarget->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0, 0), &brush);

	if (hr != S_OK) {
		return false;
	}

	else {
		return true;
	}
}

void Graphics::ClearScreen(float r, float g, float b) {
	renderTarget->Clear(D2D1::ColorF(r, g, b));
}

void Graphics::DrawCircle(float x, float y, float radius, float r, float g, float b, float a) {
	brush->SetColor(D2D1::ColorF(r, g, b, a));
	renderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), brush, 3.0f);
}