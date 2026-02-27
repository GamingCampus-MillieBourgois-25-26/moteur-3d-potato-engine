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

		/*Details(int PosX, int PosY, int SizeX, int SizeY);

		int winPosX;
		int winPosY;
		int winSizeX;
		int winSizeY;*/

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

}