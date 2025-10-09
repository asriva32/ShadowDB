#ifndef KVSTORE_H
#define KVSTORE_H

#include <string>
#include <unordered_map>
#include <mutex>

class KVStore {
private:
    std::unordered_map<std::string, std::string> store;
    std::unordered_map<std::string, double> key_expiry;
    std::mutex mutex_;
public:
    KVStore() = default;

    std::string get(const std::string &key) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (store.find(key) != store.end()) {
            return store[key];
        } else {
            return "-1";
        }
    }

    std::string set(const std::string &key, const std::string &value) {
        std::lock_guard<std::mutex> lock(mutex_);
        store[key] = value;
        return "OK";
    }
};


#endif // KVSTORE_H