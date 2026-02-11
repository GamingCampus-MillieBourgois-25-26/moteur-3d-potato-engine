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

};


class Render {
public:

	bool TRANSFcheckbox = false;
	bool Tcheckbox = false;
	bool Rcheckbox = false;
	bool Scheckbox = false;

	void showRender();

};