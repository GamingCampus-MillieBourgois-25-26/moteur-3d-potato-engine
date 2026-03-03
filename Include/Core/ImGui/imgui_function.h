#pragma once

#include "imgui.h"

#include <windows.h>
#include <string>
#include "ImGuizmo.h"
#include <DirectXMath.h>


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

		//---inputText x,y,z

		//translate
		char Xpos[64] = "0000.0";
		char Ypos[64] = "0000.0";
		char Zpos[64] = "0000.0";

		//rotate
		char Xaxe[64] = "0000.0";
		char Yaxe[64] = "0000.0";
		char Zaxe[64] = "0000.0";

		//scale
		char Xscale[64] = "0000.0";
		char Yscale[64] = "0000.0";
		char Zscale[64] = "0000.0";

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

	//class Gizmo {
	//public:

	//	// Stocker les données du gizmo comme membres de la classe
	//	XMMATRIX objectMatrix;
	//	ImGuizmo::OPERATION currentOperation;
	//	ImGuizmo::MODE currentMode;

	//	Gizmo() : objectMatrix(XMMatrixIdentity()),
	//		currentOperation(ImGuizmo::TRANSLATE),
	//		currentMode(ImGuizmo::LOCAL) {
	//	}

	//	void showTransformGizmo();

	//};

}