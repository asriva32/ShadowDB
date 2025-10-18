#ifndef MEMTABLE_H
#define MEMTABLE_H
#include "rbtree.h"
#include <string>

namespace ShadowDB{

class MemTable {

public:

struct KeyComparator {
    int operator()(const std::pair<std::string, std::string> &a, const std::pair<std::string, std::string> &b) const;
};

MemTable(const KeyComparator& comparator): tree(comparator), comparator(comparator) {}

void Insert(const std::string &key, const std::string &value);

std::pair<bool, std::string> Get(const std::string &key);

void Delete(const std::string &key);

class Iterator {
public:

Iterator(const RBTree<std::pair<std::string, std::string>, KeyComparator>::Iterator& it): it(it) {}

Iterator& operator++() {
    ++it;
    return *this;
}

Iterator operator++(int) {
    Iterator temp = *this;
    ++it;
    return temp;
}

Iterator& operator--() {
    --it;
    return *this;
}

Iterator operator--(int) {
    Iterator temp = *this;
    --it;
    return temp;
}

std::pair<std::string, std::string>& operator*() {
    return *it;
}
bool operator==(const Iterator& other) const {  return it == other.it; }
bool operator!=(const Iterator& other) const { return !(*this == other); }

private:
RBTree<std::pair<std::string, std::string>, KeyComparator>::Iterator it;

};

Iterator begin() {
    return Iterator(tree.begin());
}

Iterator end(){
    return Iterator(tree.end());
}

private:

RBTree<std::pair<std::string, std::string>, KeyComparator> tree;
KeyComparator comparator;
const std::string TOMBSTONE = "tombstone\0";

};

}

#endif // MEMTABLE_H