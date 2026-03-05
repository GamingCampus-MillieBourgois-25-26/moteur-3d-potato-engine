#pragma once

#include <windows.h>
#include <iostream>
#include <thread>
#include <memory>
#include <vector>
#include <DirectXMath.h>

// En-têtes de ton moteur
#include "Graphics/RenderPipeline/Renderer.h"
#include "Graphics/FileParser.h"
#include "Logic/SceneManager.h"
#include "Logic/MeshComponent.h"
#include "Audio/AudioComponent.h"
#include "Physics/PhysicsSystem.h"
#include "Physics/physicsBodyFactory.h"
#include "Physics/physicsBody.h"
#include "Maths/Vector3.h"
#include "Maths/Quaternion.h"

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include "Core/ImGui/imgui_function.h"

#include "Camera.h"
#include <chrono>

class PotatoEngine {
public:
    void Initialize(HINSTANCE hInstance, int nCmdShow);
    void run();
    HWND GetHwnd() const { return m_hwnd; }

private:
    HINSTANCE m_hInstance;
    HWND m_hwnd;
};