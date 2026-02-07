cmake_minimum_required(VERSION 3.20)
project(PotatoEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Utilisation de chemins explicites pour éviter l'erreur "No SOURCES"
file(GLOB_RECURSE ENGINE_SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp" 
    "${CMAKE_CURRENT_SOURCE_DIR}/source/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/source/*.hpp"
)

# ---------------- IMGUI ----------------
set(IMGUI_PATH ${CMAKE_CURRENT_SOURCE_DIR}/source/Core/ImGui)

set(IMGUI_SOURCES
    ${IMGUI_PATH}/imgui.cpp
    ${IMGUI_PATH}/imgui_draw.cpp
    ${IMGUI_PATH}/imgui_tables.cpp
    ${IMGUI_PATH}/imgui_widgets.cpp
    ${IMGUI_PATH}/imgui_demo.cpp
    ${IMGUI_PATH}/backends/imgui_impl_dx11.cpp
    ${IMGUI_PATH}/backends/imgui_impl_win32.cpp
)

# Création de l'exécutable
add_executable(${PROJECT_NAME} WIN32 ${ENGINE_SOURCES} ${IMGUI_SOURCES})

# Inclusion du dossier 'source'
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/source"
                                                  "${IMGUI_PATH}"
                                                  "${IMGUI_PATH}/backends"
)

# Liaison DirectX 11
target_link_libraries(${PROJECT_NAME} PRIVATE d3d11.lib dxgi.lib d3dcompiler.lib)

if(MSVC)
    add_compile_definitions(UNICODE _UNICODE)
endif()