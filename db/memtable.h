// #ifndef MEMTABLE_H
// #define MEMTABLE_H
// #include "rbtree.h"
// #include <string>

// namespace ShadowDB{

// class MemTable {

// struct KeyComparator;

// public:

// MemTable(const KeyComparator& comparator): tree(comparator), comparator(comparator) {}

// void Insert(const std::string &key, const std::string &value);

// std::pair<bool, std::string> Get(const std::string &key);

// void Delete(const std::string &key);

// private:

// struct KeyComparator {
//     int operator()(const std::pair<std::string, std::string> &a, const std::pair<std::string, std::string> &b) const;
// };

// RBTree<std::pair<std::string, std::string>, KeyComparator> tree;
// KeyComparator comparator;
// const std::string TOMBSTONE = "tombstone\0";

// };

// }



// #endif // MEMTABLE_H