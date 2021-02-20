# Define the project name
project(wolfenstein)

cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread") #agregar -Werror


# Client

file(GLOB SRC_FILES_CLIENT RELATIVE ${CMAKE_SOURCE_DIR} client_src/*.cpp client_src/Map/*.cpp common_src/*.cpp common_src/SDLWrappers/*.cpp)
add_executable(${PROJECT_NAME}_client client_src/client.cpp ${SRC_FILES_CLIENT})
target_include_directories(${PROJECT_NAME}_client PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/client_src)

# Server

file(GLOB SRC_FILES_SERVER RELATIVE ${CMAKE_SOURCE_DIR} server_src/*.cpp server_src/weapons/*.cpp common_src/*.cpp)
add_executable(${PROJECT_NAME}_server server_src/server.cpp ${SRC_FILES_SERVER})
target_include_directories(${PROJECT_NAME}_server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/server_src)

# Editor

file(GLOB SRC_FILES_EDITOR RELATIVE ${CMAKE_SOURCE_DIR} editor_src/*.cpp common_src/*.cpp common_src/SDLWrappers/*.cpp)
add_executable(${PROJECT_NAME}_editor editor_src/editor.cpp ${SRC_FILES_EDITOR})
target_include_directories(${PROJECT_NAME}_editor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/editor_src)

INCLUDE(FindPkgConfig)

# Add SDL2, Image, Mixer & TTF
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
PKG_SEARCH_MODULE(SDL2MIXER REQUIRED SDL2_mixer>=2.0.0)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)

# Add yaml-cpp library
PKG_SEARCH_MODULE(YAML_CPP REQUIRED yaml-cpp)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${YAML_CPP_INCLUDEDIR})
TARGET_LINK_LIBRARIES(${PROJECT_NAME}_client ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2MIXER_LIBRARIES} ${SDL2TTF_LIBRARIES} ${YAML_CPP_LIBRARIES}) 
TARGET_LINK_LIBRARIES(${PROJECT_NAME}_server ${YAML_CPP_LIBRARIES}) 
TARGET_LINK_LIBRARIES(${PROJECT_NAME}_editor ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2MIXER_LIBRARIES} ${SDL2TTF_LIBRARIES} ${YAML_CPP_LIBRARIES})


file(COPY resources DESTINATION ./)

message("[INFO] Adding Installation directives")
install(TARGETS ${PROJECT_NAME}_client ${PROJECT_NAME}_server ${PROJECT_NAME}_editor DESTINATION /usr/bin) #va a ir a :${CMAKE_INSTALL_PREFIX}/usr/bin
install(DIRECTORY resources/config 
resources/fonts 
resources/music 
resources/sounds 
resources/textures 
DESTINATION /var/${PROJECT_NAME}) #va a ir a :${CMAKE_INSTALL_PREFIX}/var/wolfenstein

