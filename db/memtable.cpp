#include "memtable.h"

namespace ShadowDB{

void MemTable::Put(const std::string &key, const std::string &value) {
    tree.insert(std::make_pair(key, value));
}

std::pair<bool, std::string> MemTable::Get(const std::string &key) {
    auto [exists, kv] = tree.get(std::make_pair(key, std::string()));
    if (exists && kv.second == TOMBSTONE) {
        return std::make_pair(false, "");
    }
    return std::make_pair(exists, kv.second);
}

int MemTable::KeyComparator::operator()(const std::pair<std::string, std::string> &a, const std::pair<std::string, std::string> &b) const {
    if (a.first < b.first) return -1;
    if (a.first > b.first) return 1;
    return 0;
}

}
