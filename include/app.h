#pragma once

#include "../include/window.h"
#include "../include/network.h"

class App {
public:
	App();
	int Init();
	~App();

private:
	void Update();
private:
	Window wnd;
	Network network;
};
