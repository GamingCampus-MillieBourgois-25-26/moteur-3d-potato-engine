#pragma once

#include "imgui.h"

#include <windows.h>
#include <string>


namespace MyGui {

	class Menu {
	public:

		void barMenu();

	};


	class Details {
	public:

		int winPosX = 1460;
		int winPosY = 710;
		int winSizeX = 450;
		int winSizeY = 300;

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

		int winPosX = 1460;
		int winPosY = 25;
		int winSizeX = 450;
		int winSizeY = 300;

		void showOutliner();

		char searchItem[64] = "";
		bool showActor = true;
	};


	class findFile {
	public:

		void showFindFile();
		std::string OpenFileDialog();
	};

}