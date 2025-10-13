#include "../../include/commands.h"
#include "../../include/db_wrapper.h"
#include <iostream>


std::shared_ptr<RespType> set(const std::vector<BulkString> &resps){
    if(resps.size() != 3){
        return std::make_shared<RespError>("ERR wrong number of arguments for 'set' command");
    }
    DB &kv = DB::getInstance();
    std::string key = resps[1].getRaw();
    std::string value = resps[2].getRaw();
    std::string result = kv.Set(key, value);
    return std::make_shared<SimpleString>(result);
}

std::shared_ptr<RespType> get(const std::vector<BulkString> &resps){
    if(resps.size() != 2){
        return std::make_shared<RespError>("ERR wrong number of arguments for 'get' command");
    }
    DB &kv = DB::getInstance();
    std::string value = kv.Get(resps[1].getRaw());
    if(value == "-1"){
        return std::make_shared<BulkString>("-1");
    }
    return std::make_shared<BulkString>(value);
}

std::shared_ptr<RespType> echo(const std::vector<BulkString> &resps){
    if(resps.size() != 2){
        return std::make_shared<RespError>("ERR wrong number of arguments for 'echo' command");
    }
    return std::make_shared<BulkString>(resps[1]);
}

std::shared_ptr<RespType> ping(const std::vector<BulkString> &resps){
    if(resps.size() == 1){
        return std::make_shared<SimpleString>("PONG");
    }else{
        return std::make_shared<RespError>("ERR wrong number of arguments for 'ping' command");
    }
}