#pragma once

#include "imgui.h"

#include <windows.h>
#include <string>

class Menu {
public:

	void barMenu();

};


class Details {
public: 

	void showDetails();

	char searchRubric[64] = "";
	bool isPhysicsActiv = false;

};


class Render {
public:

	bool TRANSFcheckbox = false;
	bool Tcheckbox = false;
	bool Rcheckbox = false;
	bool Scheckbox = false;

	int intTransf = 0;

	void showRender();

};


class Outliner {
public:

	void showOutliner();

	char searchItem[64] = "";
	bool showActor = true;
};


class findFile {
public:

	void showFindFile();
	std::string OpenFileDialog();
};


class TestRender {
public:

	void showtest();
};