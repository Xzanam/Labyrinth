cmake_minimum_required(VERSION 3.10)

project(Labyrinth)


set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


include(Dependencies.cmake)

#Projects
add_subdirectory(Game)
add_subdirectory(Core)


