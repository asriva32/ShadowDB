#ifndef MEMTABLE_H
#define MEMTABLE_H
#include "rbtree.h"

template<typename Key, typename Value, typename Comparator>
class MemTable {
public:

MemTable() = default;

void Insert(const Key &key, const Value &value);

std::pair<bool, Value> Get(const Key &key);

void Delete(const Key &key);

private:
RBTree<std::pair<Key, Value>, Comparator> tree;
Value TOMBSTONE = Value("\0")

};


#endif // MEMTABLE_H