#ifndef db_H
#define db_H

#include "status.h"
#include <expected>

namespace ShadowDB{
    class DB{
        public:

        DB() = default;
        DB(const DB&) = delete;
        DB& operator=(const DB&) = delete;

        virtual ~DB() = default;

        virtual Status Put(const std::string &key, const std::string &value) = 0;

        virtual Status Get(const std::string &key) = 0;

        virtual Status Delete(const std::string &key) = 0;
    };

    
    
}

#endif // db_H