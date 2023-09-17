cmake_minimum_required(VERSION 3.20)

set_property(GLOBAL PROPERTY CXX_STANDARD 20)
set_property(GLOBAL PROPERTY CXX_STANDARD_REQUIRED TRUE)

project(opengl_runner)

add_executable(${PROJECT_NAME} src/main.cpp)
target_compile_options(${PROJECT_NAME} PUBLIC -Wall -Wextra -pedantic -Werror)
target_include_directories(${PROJECT_NAME} PRIVATE 
    ${PROJECT_SOURCE_DIR}/include
    # third party
    ${PROJECT_SOURCE_DIR}/3rdparty/glfw/include
    ${PROJECT_SOURCE_DIR}/3rdparty/glm
    ${PROJECT_SOURCE_DIR}/3rdparty/OpenGL-Registry/api
)
set(${PROJECT_NAME}_SOURCES
    ${PROJECT_SOURCE_DIR}/src/window.cpp
    ${PROJECT_SOURCE_DIR}/src/gl_loader.cpp
    ${PROJECT_SOURCE_DIR}/src/shader.cpp
)
target_sources(${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_SOURCES})

add_subdirectory(${PROJECT_SOURCE_DIR}/3rdparty/glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE 
    ${CMAKE_BINARY_DIR}/3rdparty/glfw/src/libglfw3.a
)

set(scenes_SOURCES
    ${PROJECT_SOURCE_DIR}/src/scene_1.cpp
)
add_library(scenes STATIC ${scenes_SOURCES})
target_compile_options(scenes PUBLIC -Wall -Wextra -pedantic -Werror)
target_include_directories(scenes PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/models
    # third party
    ${PROJECT_SOURCE_DIR}/3rdparty/glm
    ${PROJECT_SOURCE_DIR}/3rdparty/stb
)
target_link_libraries(${PROJECT_NAME} PRIVATE 
    scenes
)

set(camera_SOURCES
    ${PROJECT_SOURCE_DIR}/src/camera.cpp
)
add_library(camera STATIC ${camera_SOURCES})
target_compile_options(camera PUBLIC -Wall -Wextra -pedantic -Werror)
target_include_directories(camera PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    # third party
    ${PROJECT_SOURCE_DIR}/3rdparty/glm
)
target_link_libraries(${PROJECT_NAME} PRIVATE 
    camera
)

set(stb_image_SOURCES
    ${PROJECT_SOURCE_DIR}/src/stb_image_impl.cpp
)
add_library(stb_image STATIC ${stb_image_SOURCES})
target_compile_options(stb_image PUBLIC -Wall -Wextra -pedantic -Werror)
target_include_directories(stb_image PRIVATE
    # third party
    ${PROJECT_SOURCE_DIR}/3rdparty/stb
)
target_link_libraries(${PROJECT_NAME} PRIVATE 
    stb_image
)
