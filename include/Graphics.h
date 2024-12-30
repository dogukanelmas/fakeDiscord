#pragma once

#include "windecs.h"

class Graphics {
private:
	ID2D1Factory* factory;
	ID2D1HwndRenderTarget* renderTarget;
	ID2D1SolidColorBrush* brush1;
	ID2D1SolidColorBrush* brush2;
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
	void DrawButton(float x, float y, float width, float height, float radius, float r, float g, float b, float a);
};
