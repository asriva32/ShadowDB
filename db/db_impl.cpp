#include "db_impl.h"


namespace ShadowDB{
    Status DBImpl::Put(const std::string &key, const std::string &value){
        memtable->Put(key, value);
        return Status();
    }

    Status DBImpl::Get(const std::string &key){
        auto [found, value] = memtable->Get(key);
        if(found){
            return Status(value);
        }
        return Status("not found", StatusCode::NotFound);
    }

    Status DBImpl::Delete(const std::string &key){
        memtable->Put(key, "");
        return Status();
    }
}