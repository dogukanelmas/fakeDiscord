#include "../include/app.h"

App::App()
	:
	wnd(800, 600, L"Fake Discord")
{}

int App::Init() {
	while (true) {
		if (const auto ecode = Window::ProccessMessages()) {
			return *ecode;
		}
		Update();
	}
}

App::~App()
{}

void App::Update() {
	wnd.Gfx().BeginDrawing();
		wnd.Gfx().ClearScreen(0.3f, 0.3f, 0.3f);
		wnd.Gfx().DrawButton(300.0f, 260.0f, 200.0f, 80.0f, 10.0f, 0.2f, 0.2f, 0.2f, 1.0f);
	wnd.Gfx().EndDrawing();
}