#include "../db/rbtree.h"
#include <iostream>
#include <gtest/gtest.h>
#include <string>
#include <set>

template<typename T>
struct Comparator{
    constexpr bool operator()(const T& l, const T& r) const {
        return l < r;
    }
};

TEST(RBTests, EmptyCase){
    Comparator<std::string> comp;
    RBTree<std::string, Comparator<std::string>> tree(comp);
    EXPECT_TRUE(tree.size() == 0);
}

TEST(RBTests, Insert){
    Comparator<int> comp;
    RBTree<int, Comparator<int>> tree(comp);
    std::set<int> s;
    for(int i = 0; i < 5;i++){
        s.insert(i);
        tree.insert(i);
    }
    for(int i = 0; i < 5;i++){
        EXPECT_TRUE(s.count(i) == tree.contains(i));
    }
    EXPECT_FALSE(tree.contains(10000));
}

TEST(RBTests, InsertStress){
    const int N = 1000000;
    Comparator<int> comp;
    RBTree<int, Comparator<int>> tree(comp);
    for(int i = 0; i < N;i++){
        tree.insert(i);
    }
    for(int i = 0; i < N;i++){
        EXPECT_TRUE(tree.contains(i));
    }
}