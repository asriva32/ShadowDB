#ifndef KVSTORE_H
#define KVSTORE_H

#include <string>
#include <unordered_map>
#include <mutex>

class KVStore {
private:
    std::unordered_map<std::string, std::string> store;
    std::unordered_map<std::string, int64_t> key_expiry;
    std::mutex mutex_;

    KVStore() {}
    KVStore(const KVStore&) = delete;
    KVStore& operator=(const KVStore&) = delete;
public:

    static KVStore& getInstance(){
        static KVStore instance;
        return instance;
    }

    int64_t getCurTime(){
        auto now = std::chrono::system_clock::now();
        auto duration = now.time_since_epoch();
        int64_t milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
        return milliseconds;
    }

    std::string get(const std::string &key) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (store.find(key) != store.end()) {
            if(key_expiry.find(key) != key_expiry.end()){
                if(key_expiry.at(key) < getCurTime()){
                    store.erase(key);
                    key_expiry.erase(key);
                    return "-1";
                }
            }
            return store[key];
        } else {
            return "-1";
        }
    }

    std::string set(const std::string &key, const std::string &value, int64_t expiry) {
        std::lock_guard<std::mutex> lock(mutex_);

        if(expiry > -1){
            key_expiry[key] = expiry + getCurTime();
        }else{
            key_expiry.erase(key);
        }

        store[key] = value;
        return "OK";
    }

    void del(const std::string &key) {
        std::lock_guard<std::mutex> lock(mutex_);
        store.erase(key);
        key_expiry.erase(key);
    }
};


#endif // KVSTORE_H