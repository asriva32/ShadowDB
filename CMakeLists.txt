cmake_minimum_required(VERSION 3.31.4)
project(ShadowDB)

set(This ShadowCore)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)


enable_testing()
add_subdirectory("third_party/googletest")

include_directories(.)

set(Headers
    include/client.h
    include/commands.h
    include/db_wrapper.h
    include/resp_types.h
    include/resp.h
    db/db_impl.h
    db/db.h
    db/rbtree.h
    db/status.h
    db/memtable.h
)

set(Sources
    resp/client.cpp
    resp/commands.cpp
    resp/resp.cpp
    db/db_impl.cpp
    db/memtable.cpp
)


add_library(${This} STATIC ${Sources} ${Headers})
add_executable(${PROJECT_NAME} resp/server.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${This})

add_subdirectory(tests)