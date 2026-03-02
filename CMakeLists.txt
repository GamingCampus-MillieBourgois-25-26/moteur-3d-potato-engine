cmake_minimum_required(VERSION 3.20)
project(PotatoEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Utilisation de chemins explicites pour éviter l'erreur "No SOURCES"
file(GLOB_RECURSE ENGINE_SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp" 
    "${CMAKE_CURRENT_SOURCE_DIR}/Include/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Include/*.hpp"
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
    JPH_FLOATING_POINT_EXCEPTIONS_ENABLED
    JPH_PROFILE_ENABLED
    JPH_OBJECT_STREAM

)

# ---------------- IMGUI ----------------
set(IMGUI_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/source/Core/ImGui/Config")
set(IMGUI_INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Include/Core/ImGui/Config")

set(IMGUI_SOURCES
    "${IMGUI_SRC_DIR}/imgui.cpp"
    "${IMGUI_SRC_DIR}/imgui_draw.cpp"
    "${IMGUI_SRC_DIR}/imgui_tables.cpp"
    "${IMGUI_SRC_DIR}/imgui_widgets.cpp"
    "${IMGUI_SRC_DIR}/imgui_demo.cpp"
    "${IMGUI_SRC_DIR}/backends/imgui_impl_dx11.cpp"
    "${IMGUI_SRC_DIR}/backends/imgui_impl_win32.cpp"
)



# Création de l'exécutable
add_executable(${PROJECT_NAME} WIN32 ${ENGINE_SOURCES} ${IMGUI_SOURCES} "Include/Maths/Quaternion.h" "source/Maths/Quaternion.cpp")




# Liaison Bibliotheques (DirectX 11 ...)
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        d3d11
        dxgi
        d3dcompiler
        Jolt
)

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/source"
                                                  "${IMGUI_INC_DIR}"
                                                  "${IMGUI_INC_DIR}/backends"
                                                  "${CMAKE_CURRENT_SOURCE_DIR}/Include"
                                                  "${CMAKE_CURRENT_SOURCE_DIR}/external/include"
                                                  
)


# Commande pour copier le dossier des shaders vers le dossier de l'exécutable
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/source/Graphics/RenderPipeline/Shaders"
    "$<TARGET_FILE_DIR:${PROJECT_NAME}>/Shaders"
)




if(MSVC)
    add_compile_definitions(UNICODE _UNICODE)
endif()

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/assets"
    "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets"
)