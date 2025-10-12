#ifndef RESP_H
#define RESP_H
#include <string>
#include <vector>
#include <cstdint>
#include <unordered_map>

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
    std::string value;
    RESP() = default;
    RESP(RESPType t, std::string v) : type(t), value(std::move(v)) {}
};


std::string parse_resp(std::string data);





#endif // RESP_H