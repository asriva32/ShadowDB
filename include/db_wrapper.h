#ifndef DB_WRAPPER_H
#define DB_WRAPPER_H

#include <mutex>
#include <memory>
#include "db/db.h"
#include "db/status.h"


class DB {
private:
    std::unique_ptr<ShadowDB::DB> db;
    std::mutex mutex_;

    DB() {}
    DB(const DB&) = delete;
    DB& operator=(const DB&) = delete;
public:

    static DB& getInstance(){
        static DB instance;
        return instance;
    }

    std::string Get(const std::string &key) {
        std::lock_guard<std::mutex> lock(mutex_);
        Status s = db->Get(key);
        if(s.ok()){
            return s.getValue();
        }else{
            return "-1";
        }
    }

    std::string Set(const std::string &key, const std::string &value) {
        std::lock_guard<std::mutex> lock(mutex_);
        Status s = db->Set(key, value);
        return (s.ok() ? "OK": "-ERR Faulty set");
    }

    void Delete(const std::string &key) {
        std::lock_guard<std::mutex> lock(mutex_);
        Status s = db->Delete(key);
    }
};

#endif //DB_WRAPPER_H