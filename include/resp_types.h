#ifndef RESP_TYPES_H
#define RESP_TYPES_H

#include <string>
#include <unordered_map>
#include <vector>
#include <variant>

const std::string CRLF = "\r\n";


enum RespType{
    BASE,
    SIMPLE_STRING,
    ERROR,
    BULK_STRING,
    ARRAY
};

const std::unordered_map<char, RespType> RESP_TYPE_MAP = {
    {'*', RespType::ARRAY},
    {'$', RespType::BULK_STRING},
    {'-', RespType::ERROR},
    {'+', RespType::SIMPLE_STRING}
};

class Resp{
public:

Resp(const std::string &data, RespType r): data(data), r(r) {}
Resp(const std::vector<Resp> &data, RespType r): data(data), r(r) {}

std::string getSerialized() const {
    switch(r){
        case RespType::SIMPLE_STRING:
            return serialize_simple_string(std::get<std::string>(data));
        case RespType::ERROR:
            return serialize_error(std::get<std::string>(data));
        case RespType::BULK_STRING:
            return serialize_bulk_string(std::get<std::string>(data));
        case RespType::ARRAY:
            return serialize_array(std::get<std::vector<Resp>>(data));
        default:
            // Should not reach here
            return "";
    }
}

std::variant<std::string, std::vector<Resp>> getRaw() const {
    return data;
}

private:
std::variant<std::string, std::vector<Resp>> data;
RespType r;

std::string serialize_simple_string(const std::string &str) const{
    return "+" + str + CRLF;
}

std::string serialize_error(const std::string &str) const{
    return "-" + str + CRLF;
}

std::string serialize_bulk_string(const std::string &str) const{
    return "$" + std::to_string(str.length()) + CRLF + str + CRLF;
}

std::string serialize_array(const std::vector<Resp> &arr) const{
    std::string serialized = "*" + std::to_string(arr.size()) + CRLF;
    for(const Resp &item : arr){
        serialized += item.getSerialized();
    }
    return serialized;
}

};




#endif