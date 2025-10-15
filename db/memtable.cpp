#include "memtable.h"

template<typename Key, typename Value, typename Comparator>
void MemTable<Key, Value, Comparator>::Insert(const Key &key, const Value &value) {
    tree.insert(std::make_pair(key, value));
}

template<typename Key, typename Value, typename Comparator>
std::pair<bool, Value> MemTable<Key, Value, Comparator>::Get(const Key &key) {
    auto [exists, kv] = tree.get(std::make_pair(key, Value()));
    return std::make_pair(exists, kv.second);
}

template<typename Key, typename Value, typename Comparator>
void MemTable<Key, Value, Comparator>::Delete(const Key &key) {
    tree.insert(std::make_pair(key, TOMBSTONE))
}

