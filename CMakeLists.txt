cmake_minimum_required(VERSION 3.31.4)
project(ShadowDB)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(.)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS
    "${PROJECT_SOURCE_DIR}/db/*.cpp"
    "${PROJECT_SOURCE_DIR}/resp/*.cpp"
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})