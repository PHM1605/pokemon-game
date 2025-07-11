cmake_minimum_required(VERSION 3.0.0)
project(pokemon-game)

set(SourceFiles
  src/Background.cpp
  src/base64.cpp
  src/Camera.cpp 
  src/Game.cpp 
  src/GameObjectFactory.cpp
  src/GameStateMachine.cpp
  src/InputHandler.cpp
  src/Level.cpp
  src/LevelParser.cpp
  src/main.cpp
  src/MainMenuState.cpp
  src/MenuButton.cpp
  src/MenuState.cpp
  src/NPC.cpp
  src/ObjectLayer.cpp
  src/PlayState.cpp 
  src/Player.cpp
  src/StateParser.cpp
  src/StoryState.cpp
  src/TextureManager.cpp
  src/TileLayer.cpp
  src/tinystr.cpp 
  src/tinyxml.cpp 
  src/tinyxmlerror.cpp 
  src/tinyxmlparser.cpp
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)
pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)

find_package(ZLIB REQUIRED)

add_executable(${PROJECT_NAME}
  ${SourceFiles}
)

target_include_directories(${PROJECT_NAME} PRIVATE 
  ${SDL2_INCLUDE_DIRS}
  ${SDL2_IMAGE_INCLUDE_DIRS}
  ${SDL2_TTF_INCLUDE_DIRS}
  ${CMAKE_CURRENT_SOURCE_DIR} # for #include <src/window.h> 
  ${ZLIB_INCLUDE_DIRS}
)

target_link_directories(${PROJECT_NAME} PRIVATE 
  ${SDL2_LIBRARY_DIRS}
  ${SDL2_IMAGE_LIBRARY_DIRS}
  ${SDL2_TTF_LIBRARY_DIRS}
  ${ZLIB_LIBRARY_DIRS}
)

target_link_libraries(${PROJECT_NAME} 
  ${SDL2_LIBRARIES}
  ${SDL2_IMAGE_LIBRARIES}
  ${SDL2_TTF_LIBRARIES}
  ${ZLIB_LIBRARIES}
)

# Copy icons
file(COPY assets/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/assets)
