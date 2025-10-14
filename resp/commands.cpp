#include "../include/commands.h"
#include "../include/db_wrapper.h"
#include <iostream>



Resp set(const std::vector<Resp> &resps){
    if(resps.size() != 3){
        return Resp("ERR wrong number of arguments for 'set' command", RespType::ERROR);
    }
    DB &kv = DB::getInstance();
    std::string key = std::get<std::string>(resps[1].getRaw());
    std::string value = std::get<std::string>(resps[2].getRaw());
    std::string result = kv.Set(key, value);
    if(result != "OK"){
        return Resp(result, RespType::ERROR);
    }
    return Resp(result, RespType::SIMPLE_STRING);
}

Resp get(const std::vector<Resp> &resps){
    if(resps.size() != 2){
        return Resp("ERR wrong number of arguments for 'get' command", RespType::ERROR);
    }
    DB &kv = DB::getInstance();
    std::string value = kv.Get(std::get<std::string>(resps[1].getRaw()));
    if(value == "-1"){
        return Resp("-1", RespType::BULK_STRING);
    }
    return Resp(value, RespType::BULK_STRING);
}

Resp echo(const std::vector<Resp> &resps){
    if(resps.size() != 2){
        return Resp("ERR wrong number of arguments for 'echo' command", RespType::ERROR);
    }
    return resps[1];
}

Resp ping(const std::vector<Resp> &resps){
    if(resps.size() == 1){
        return Resp("PONG", RespType::SIMPLE_STRING);
    }else{
        return Resp("ERR wrong number of arguments for 'ping' command", RespType::ERROR);
    }
}