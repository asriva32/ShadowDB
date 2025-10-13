#ifndef RESP_TYPES_H
#define RESP_TYPES_H

#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

const std::string CRLF = "\r\n";


enum RESPType{
    BASE,
    SIMPLE_STRING,
    ERROR,
    BULK_STRING,
    ARRAY
};

const std::unordered_map<char, RESPType> RESP_TYPE_MAP = {
    {'*', RESPType::ARRAY},
    {'$', RESPType::BULK_STRING},
    {'-', RESPType::ERROR},
    {'+', RESPType::SIMPLE_STRING}
};

class RespType{
public:
static std::shared_ptr<RespType> build_resp_array(const std::string &input);
virtual std::string getSerialized() const = 0;
virtual RESPType getUnderlyingType() const{
    return RESPType::BASE;
}

};

class SimpleString: public RespType{
public:

SimpleString(std::string msg): msg(std::move(msg)) {}
    
std::string getSerialized() const override { return "+" + msg + CRLF; }

std::string getRaw() const {return msg; }

RESPType getUnderlyingType() const override { return RESPType::SIMPLE_STRING; }

private:
std::string msg;
};

class BulkString: public RespType{
public:

BulkString(std::string msg): msg(std::move(msg)) {}


std::string getSerialized() const override { return "$" + std::to_string(msg.length()) + CRLF + msg + CRLF; }

std::string getRaw() const {return msg; }

RESPType getUnderlyingType() const override { return RESPType::BULK_STRING; }

private:
std::string msg;

};

class RespError: public RespType{
public:

RespError(std::string msg): msg(std::move(msg)) {}

std::string getSerialized() const override { return "-" + msg + CRLF; }

std::string getRaw() const {return msg; }

RESPType getUnderlyingType() const override { return RESPType::ERROR; }

private:
std::string msg;

};

class RespArray: public RespType{
public:

RespArray(const std::vector<BulkString> &arr): resps(arr) {}

std::string getSerialized() const override {
    std::string res = "*" + std::to_string(resps.size()) + CRLF;
    for(const BulkString &bs: resps){
        res += bs.getSerialized();
    }
    return res;
}
std::vector<BulkString> getArray() const { return resps; }

RESPType getUnderlyingType() const override { return RESPType::ARRAY; }

private:
std::vector<BulkString> resps;

};




#endif