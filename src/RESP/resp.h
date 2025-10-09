#ifndef RESP_H
#define RESP_H
#include "../DB/KVStore.h"
#include <string>
#include <vector>
#include <cstdint>
#include <unordered_map>
#include <optional>
#include <variant>

enum RESPType{
    SIMPLE_STRING,
    ERROR,
    INTEGER,
    BULK_STRING,
    ARRAY
};

const std::unordered_map<char, RESPType> RESP_TYPE_MAP = {
    {'*', RESPType::ARRAY},
    {'$', RESPType::BULK_STRING}
};


struct RESP{
    RESPType type;
    std::variant<std::string, int64_t> value;
    RESP() = default;
    RESP(RESPType t, const std::variant<std::string, int64_t> &v) : type(t), value(v) {}
    
};


std::string parse_resp(const char* data, size_t length, KVStore &kv);





#endif // RESP_H