#include "../db/rbtree.h"
#include <iostream>
#include <gtest/gtest.h>
#include <string>
#include <set>



template<typename T>
struct Comparator{
    constexpr int operator()(const T& l, const T& r) const {
        if(l < r) return -1;
        if(l > r) return 1;
        return 0;
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
        auto [found, val] = tree.get(i);
        EXPECT_TRUE(found);
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

TEST(RBTests, IteratorTest){
    Comparator<int> comp;
    RBTree<int, Comparator<int>> tree(comp);
    for(int i = 0; i < 10;i++){
        tree.insert(i);
    }
    int expected = 0;
    for(auto it = tree.begin(); it != tree.end(); it++){
        EXPECT_TRUE(*it == expected);
        expected++;
    }
    EXPECT_TRUE(expected == 10);

    auto it = tree.begin();
    ++it;
    EXPECT_TRUE(*it == 1);
    --it;
    EXPECT_TRUE(*it == 0);
}