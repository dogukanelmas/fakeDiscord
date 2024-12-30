#pragma once

#include <windows.h>
#include <d2d1.h>

class Graphics {
	ID2D1Factory* factory;
	ID2D1HwndRenderTarget* renderTarget;
	ID2D1SolidColorBrush* brush;
public:
	Graphics();
	~Graphics();

	bool Init(HWND hWnd);

	void BeginDrawing() {
		renderTarget->BeginDraw();
	}

	void EndDrawing() {
		renderTarget->EndDraw();
	}

	void ClearScreen(float r, float g, float b);
	void DrawCircle(float x, float y, float radius, float r, float g, float b, float a);
};
