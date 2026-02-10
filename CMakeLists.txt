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

# Jolt Physics
add_library(Jolt STATIC IMPORTED)

set(EXTERNAL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external")
set(EXTERNAL_LIBS_DIR "${EXTERNAL_DIR}/libs")
set(EXTERNAL_INCLUDE_DIR "${EXTERNAL_DIR}/include")

set(JOLT_INCLUDE_DIR "${EXTERNAL_INCLUDE_DIR}/Jolt")
set(JOLT_LIB_DIR     "${EXTERNAL_LIBS_DIR}/Jolt")

set_target_properties(Jolt PROPERTIES
    IMPORTED_LOCATION_DEBUG   "${JOLT_LIB_DIR}/Debug/Jolt.lib"
    IMPORTED_LOCATION_RELEASE   "${JOLT_LIB_DIR}/Release/Jolt.lib"
    INTERFACE_INCLUDE_DIRECTORIES "${JOLT_INCLUDE_DIR}"
)

target_compile_definitions(Jolt INTERFACE
    JPH_DEBUG_RENDERER
)

# Création de l'exécutable
add_executable(${PROJECT_NAME} WIN32 ${ENGINE_SOURCES})

# Inclusion du dossier 'source'
target_include_directories(${PROJECT_NAME}
    PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/source"
    "${EXTERNAL_INCLUDE_DIR}"
)

# Liaison Bibliotheques (DirectX 11 ...)
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        d3d11
        dxgi
        d3dcompiler
        Jolt
)

if(MSVC)
    add_compile_definitions(UNICODE _UNICODE)
endif()