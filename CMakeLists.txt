cmake_minimum_required(VERSION 3.0.0)
project(yugioh-game)

set(SourceFiles
  src/Card.cpp 
  src/DuelState.cpp 
  src/Game.cpp 
  src/main.cpp
  src/MenuState.cpp
  src/NPC.cpp
  src/OverworldState.cpp 
  src/Player.cpp
  src/StoryState.cpp
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)
pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)

add_executable(${PROJECT_NAME}
  ${SourceFiles}
)

target_include_directories(${PROJECT_NAME} PRIVATE 
  ${SDL2_INCLUDE_DIRS}
  ${SDL2_IMAGE_INCLUDE_DIRS}
  ${SDL2_TTF_INCLUDE_DIRS}
  ${CMAKE_CURRENT_SOURCE_DIR} # for #include <src/window.h> 
)

target_link_directories(${PROJECT_NAME} PRIVATE 
  ${SDL2_LIBRARY_DIRS}
  ${SDL2_IMAGE_LIBRARY_DIRS}
  ${SDL2_TTF_LIBRARY_DIRS}
)

target_link_libraries(${PROJECT_NAME} 
  ${SDL2_LIBRARIES}
  ${SDL2_IMAGE_LIBRARIES}
  ${SDL2_TTF_LIBRARIES}
)

# Copy icons
file(COPY assets/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/assets)
