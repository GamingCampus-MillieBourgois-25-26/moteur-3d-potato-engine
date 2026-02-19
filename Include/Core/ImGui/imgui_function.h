#pragma once

#include "imgui.h"

#include <windows.h>


class Menu {
public:

	void barMenu();

};


class Details {
public: 

	void showDetails();

	char searchBuffer[64] = "";
	bool isPhysicsActiv;

};


class Render {
public:

	bool TRANSFcheckbox = false;
	bool Tcheckbox = false;
	bool Rcheckbox = false;
	bool Scheckbox = false;

	int jsp = 3;

	void showRender();

};