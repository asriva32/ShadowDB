#include "../db/memtable.h"
#include <iostream>
#include <gtest/gtest.h>

TEST(MemTableTests, PutAndGet){
    ShadowDB::MemTable::KeyComparator comp;
    ShadowDB::MemTable table(comp);
    table.Put("key1", "value1");
    table.Put("key2", "value2");
    auto [found1, val1] = table.Get("key1");
    auto [found2, val2] = table.Get("key2");
    auto [found3, val3] = table.Get("key3");
    EXPECT_TRUE(found1);
    EXPECT_TRUE(found2);
    EXPECT_FALSE(found3);
    EXPECT_TRUE(val1 == "value1");
    EXPECT_TRUE(val2 == "value2");
}


TEST(MemTableTests, IteratorTest){
    ShadowDB::MemTable::KeyComparator comp;
    ShadowDB::MemTable table(comp);
    table.Put("key1", "value1");
    table.Put("key2", "value2");
    table.Put("key3", "value3");
    std::vector<std::pair<std::string, std::string>> expected = {
        {"key1", "value1"},
        {"key2", "value2"},
        {"key3", "value3"}
    };
    int index = 0;
    for(auto it = table.begin(); it != table.end(); it++){
        EXPECT_TRUE(*it == expected[index]);
        index++;
    }
}