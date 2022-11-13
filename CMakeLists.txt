cmake_minimum_required(VERSION 3.7)

project(sockets)

set(CLIENT  src/socket.cpp src/client.cpp src/player.cpp src/network.cpp src/parser.cpp)

add_compile_options(-Wall -Werror)

add_executable(robotclient ${CLIENT})
