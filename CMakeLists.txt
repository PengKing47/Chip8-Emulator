cmake_minimum_required(VERSION 3.0.0)
project(chip8_emulator)

set(SourceFiles
    main.cpp
    chip8.cpp
    opdecoder.cpp
    sdlscreen.cpp
    eventhandler.cpp)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
add_executable(${PROJECT_NAME} ${SourceFiles})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})