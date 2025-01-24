#include "../include/app.h"

App::App()
	:
	wnd(800, 600, L"Escord")
{}

int App::Init() {
	//This could change
	if (!network.initialize()) {
		return -1;
	}

	while (true) {
		if (const auto ecode = Window::ProccessMessages()) {
			network.cleanup();
			return *ecode;
		}

		network.checkNetworkEvents();

		Update();
	}
}

App::~App()
{}

void App::Update() {
	wnd.Gfx().BeginDrawing();
		wnd.Gfx().ClearScreen(0.3f, 0.3f, 0.3f);
	wnd.Gfx().EndDrawing();
}