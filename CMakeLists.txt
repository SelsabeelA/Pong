cmake_minimum_required(VERSION 3.23.2)

project(weebking)

add_executable(${PROJECT_NAME}
    src/renderer.cpp
    src/win32_platform.cpp
)

target_include_directories(${PROJECT_NAME}
    PUBLIC include
)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall)
