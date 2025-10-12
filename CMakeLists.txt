cmake_minimum_required(VERSION 3.31.4)
project(ShadowDB)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(.)

add_executable(${PROJECT_NAME} 
                RESP/Server.cpp 
                RESP/Client.cpp
                RESP/resp.cpp
                Commands/commands.cpp)