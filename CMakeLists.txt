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

# Création de l'exécutable
add_executable(${PROJECT_NAME} WIN32 ${ENGINE_SOURCES} "source/Logic/Actor.h" "source/Logic/Actor.cpp" "source/Logic/Component.h" "source/Logic/Scene.h" "source/Logic/Scene.cpp" "source/Logic/SceneManager.h" "source/Logic/SceneManager.cpp" "source/Logic/UUID.h")

# Inclusion du dossier 'source'
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/source")

# Liaison DirectX 11
target_link_libraries(${PROJECT_NAME} PRIVATE d3d11.lib dxgi.lib d3dcompiler.lib)

if(MSVC)
    add_compile_definitions(UNICODE _UNICODE)
endif()