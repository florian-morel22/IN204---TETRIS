cmake_minimum_required(VERSION 3.14)

# ----------------------------------------------------------------------------- #
# Project name                                                                  #
# ----------------------------------------------------------------------------- #

project(sfml-app)

# ----------------------------------------------------------------------------- #
# C++ standard                                                                  #
# ----------------------------------------------------------------------------- #

set(CMAKE_CXX_COMPILER g++-10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_FLAGS "-Wall")

if(CMAKE_BUILD_TYPE STREQUAL "") 
    MESSAGE("Default CMAKE_BUILD_TYPE = Debug, you can change it by running 'cmake <PathToCMakeLists.txt> -DCMAKE_BUILD_TYPE=Release'")
    set(CMAKE_BUILD_TYPE "Debug")

elseif(NOT (CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL "Release"))
    MESSAGE("CMAKE_BUILD_TYPE = " ${CMAKE_BUILD_TYPE})
    MESSAGE("CMAKE_BUILD_TYPE must either be Debug or Release, you can change it by running 'cmake <PathToCMakeLists.txt> -DCMAKE_BUILD_TYPE=Release'")
    MESSAGE("Changing it to Debug")
    set(CMAKE_BUILD_TYPE "Debug")
endif()

MESSAGE("Build type : " ${CMAKE_BUILD_TYPE})

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(
        -Wall
        -Wextra
        -std=c++20
        -g
    )
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_options(
        -Wall
        -Wextra
        -std=c++20
        -O3
    )
endif()

#----------------------------------------------------------------------- #

file(GLOB_RECURSE SRC_FILES CMAKE_CONFIGURE_DEPENDS
"src/*.cpp"
"src/*.c")

add_executable(sfml-app ${SRC_FILES})

target_include_directories(
  sfml-app
  PRIVATE 
  inc/
)

target_link_libraries(
    sfml-app
    # -lsfml-audio
    -lsfml-network
    -lsfml-graphics
    -lsfml-window
    -lsfml-system
    -pthread
)
