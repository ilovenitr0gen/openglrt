cmake_minimum_required(VERSION 3.31)
project(project123)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()

if (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif ()

if (PROJECT_IS_TOP_LEVEL AND UNIX)
    # Create symlink to compile_commands.json for IDE to pick it up
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E create_symlink
            ${CMAKE_BINARY_DIR}/compile_commands.json
            ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json
    )
endif()

include_directories(.)

add_executable(project123
        main.cpp
		DisplayWindow.cpp
		Shader.cpp
		Raytracer.cpp
		glad/glad.c
	)

IF(WIN32)
		target_link_libraries(project123
            PUBLIC
            glfw3.lib
            opengl32.lib
	)
ENDIF()

IF(LINUX)
    target_link_libraries(project123
            glfw
    )
ENDIF()
