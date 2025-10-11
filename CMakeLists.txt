cmake_minimum_required(VERSION 3.31.4)
project(KVStore)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(.)

add_executable(${PROJECT_NAME} 
                src/Server.cpp 
                src/Client.cpp
                src/RESP/resp.cpp
                src/Commands/commands.cpp)