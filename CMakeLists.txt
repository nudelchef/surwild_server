cmake_minimum_required(VERSION 3.22)
project(surwild_server)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(surwild_server
        src/Direction.h
        src/Entity.cpp
        src/Entity.h
        src/main.cpp
        src/MultiServer.cpp
        src/MultiServer.h
        src/PacketManager.cpp
        src/PacketManager.h
        src/Player.cpp
        src/Player.h
        src/SocketHandler.cpp
        src/SocketHandler.h)
