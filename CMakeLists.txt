cmake_minimum_required(VERSION 3.5.1)
project(chip8_emulator)

set(SourceFiles
    main.cpp
    chip8.cpp
    opdecoder.cpp
    sdlscreen.cpp
    eventhandler.cpp)

find_package(SDL2 REQUIRED)
find_package(SDL2_mixer REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${SourceFiles})

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2_MIXER_LIBRARIES} -lSDL2_mixer)
