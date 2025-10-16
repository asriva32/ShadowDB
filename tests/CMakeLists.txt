cmake_minimum_required(VERSION 3.31.4)

set(This DBTests)

set(Sources 
    rbtree_test.cpp
    memtable_test.cpp)

add_executable(${This} ${Sources})
target_link_libraries(${This} PUBLIC
    gtest_main
    ShadowCore
)
add_test(
    NAME ${This}
    COMMAND ${This}
)