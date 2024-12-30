#pragma once

#include "window.h"

class App {
public:
	App();
	int Init();
	~App();

private:
	void Update();
private:
	Window wnd;
};
