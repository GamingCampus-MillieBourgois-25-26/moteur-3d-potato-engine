#pragma once

#include "imgui.h"

#include <windows.h>
#include <string>
#include "ImGuizmo.h"
#include <DirectXMath.h>
#include "Logic/SceneManager.h"
#include "Engine.h"

namespace MyGui {

	class Menu {
	public:

		void barMenu();

	};


	class Details {
	public:

		int winPosX = 1460;
		int winPosY = 635;
		int winSizeX = 450;
		int winSizeY = 430;

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

	class Gizmo {
	public:

		// Stocker les données du gizmo comme membres de la classe
		DirectX::XMMATRIX objectMatrix;
		DirectX::XMMATRIX viewMatrix;
		DirectX::XMMATRIX projectionMatrix;
		ImGuizmo::OPERATION currentOperation;
		ImGuizmo::MODE currentMode;

		Gizmo() : objectMatrix(DirectX::XMMatrixIdentity()),
			viewMatrix(DirectX::XMMatrixIdentity()),
			projectionMatrix(DirectX::XMMatrixIdentity()),
			currentOperation(ImGuizmo::TRANSLATE),
			currentMode(ImGuizmo::LOCAL) {
		}

		void drawGizmo(ImVec2 pos, ImVec2 size, DirectX::XMMATRIX& view, DirectX::XMMATRIX& proj, DirectX::XMMATRIX& matrix);

	};

	class Render {
	public:

		Gizmo gizmo;
		//int intTransf = 0;

		void showRender();

	};


	class Outliner {
	public:

		int winPosX = 1460;
		int winPosY = 25;
		int winSizeX = 450;
		int winSizeY = 400;

		void showOutliner();

		char searchItem[64] = "";
		bool showActor = true;
	};


	class findFile {
	public:

		int winPosX = 1460;
		int winPosY = 430;
		int winSizeX = 450;
		int winSizeY = 200;

		void showFindFile();
		std::string OpenFileDialog();
	};

	

}