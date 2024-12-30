#include "../include/app.h"

int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow ) {
	const wchar_t pClassName[] = L"fakeDiscord";
	
	return App{}.Init();
}