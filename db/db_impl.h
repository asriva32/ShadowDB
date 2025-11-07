#ifndef db_impl_H
#define db_impl_H
#include "db.h"
#include "memtable.h"
#include <string>
#include <memory>
#include <cstddef>
#include <mutex>

namespace ShadowDB{
    class DBImpl: DB{
        public:
            DBImpl();

            Status Put(const std::string &key, const std::string &value);
            Status Get(const std::string &key);
            Status Delete(const std::string &key);
            // Status Write



        private:
            std::shared_ptr<MemTable> memtable;
            std::vector<std::shared_ptr<MemTable>> imm_memtables;
            LsmStorageOptions storage_options;
            std::mutex mutex_;

    };  

    struct LsmStorageOptions {
        // in bytes
        int block_size;
        int target_sst_size;
        // ~3
        int num_memtable_limit;
        CompactionOptions compaction_options;
        bool enable_wal;
        bool serializable;
    };
    
    enum class CompactionOptions{
        Leveled,
        Tiered,
        Simple,
        NoCompaction
    };
}




#endif // db_impl_H