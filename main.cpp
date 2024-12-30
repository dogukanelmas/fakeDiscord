#include <windows.h>
#include <d2d1.h>
#include "Graphics.h"

Graphics* graphics;

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	/*
	case (WM_PAINT): {
		graphics->BeginDrawing();
			graphics->ClearScreen(0.8f, 0.0f, 0.0f);
		graphics->EndDrawing();

		break;
	}
	*/
	case WM_CLOSE:
		PostQuitMessage(31);
		return 0;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow ) {
	const wchar_t pClassName[] = L"fakeDiscord";

	// Registering the window class.
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = nullptr;
	wc.hCursor = nullptr;
	wc.hbrBackground = (HBRUSH) COLOR_WINDOW;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = pClassName;
	wc.hIconSm = nullptr;
	RegisterClassEx(&wc);

	// Adjustng the drawing area
	RECT rect = { 0, 0, 800, 600 };
	AdjustWindowRectEx(&rect, 0, 0, 0);

	// Creating a window instance.
	HWND hWnd = CreateWindowEx(
		0, pClassName, L"fakeDiscord",
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT, rect.right - rect.left, rect.bottom - rect.top, nullptr, nullptr, hInstance, nullptr
	);

	// We return if no handle is created so there is no window to be shown.
	if (!hWnd) return 0;

	// Create and init the d2d factory.
	graphics = new Graphics();
	if (!graphics->Init(hWnd)) {
		delete graphics;
		return -1;
	}

	// We show the window.
	ShowWindow(hWnd, nCmdShow);

	float y = 0.0f;
	float ySpeed = 0.0f;

	MSG msg;
	msg.message = WM_NULL;
	
	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			ySpeed += 1.0f;
			y += ySpeed;
			if (y > 500) {
				y = 500;
				ySpeed = -ySpeed;
			}
			if (labs(ySpeed) > 0) {
				if(ySpeed > 0) ySpeed -= 0.2f;
				if (ySpeed < 0) ySpeed += 0.2f;
			}

				graphics->BeginDrawing();
					graphics->ClearScreen(0.0f, 0.0f, 0.5f);
					graphics->DrawCircle(
						375.0f, y, 50.0f, 1.0f, 1.0f, 1.0f, 1.0f);
				graphics->EndDrawing();
		}
	}

	/*
	// Message pump
	MSG msg;
	BOOL gResult;
	while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	if (gResult == -1) {
		return -1;
	}
	else {
		return msg.wParam;
	}
	*/

	delete graphics;

	return 0;
}