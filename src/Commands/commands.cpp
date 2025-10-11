#include "../../include/commands.h"
#include <iostream>

const std::string CRLF = "\r\n";


std::string set(const std::vector<RESP> &resps){
    if(resps.size() != 3 && resps.size() != 5){
        return "-ERR wrong number of arguments for 'set' command" + CRLF;
    }

    for(int i = 1; i < resps.size();i++){
        if(resps[i].type != RESPType::BULK_STRING){
            return "-ERR expected bulk string arguments" + CRLF;
        }
    }
    int64_t expiry = -1;
    if(resps.size() == 5){
        if(resps[3].value == "PX"){
            expiry = stoll(resps[4].value);
        }else{
            return "-ERR 4th argument is invalid" + CRLF;
        }
    }
    KVStore &kv = KVStore::getInstance();
    std::string key = resps[1].value;
    std::string value = resps[2].value;
    std::string result = kv.set(key, value, expiry);
    return "+" + result + CRLF;
}

std::string get(const std::vector<RESP> &resps){
    if(resps.size() != 2 || resps[1].type != RESPType::BULK_STRING){
        return "-ERR wrong number of arguments for 'get' command" + CRLF;
    }
    KVStore &kv = KVStore::getInstance();
    std::string key = resps[1].value;
    std::string value = kv.get(key);
    if(value == "-1"){
        return "$-1" + CRLF;
    }
    return "$" + std::to_string(value.length()) + CRLF + value + CRLF;
}

std::string echo(const std::vector<RESP> &resps){
    if(resps.size() != 2 || resps[1].type != RESPType::BULK_STRING){
        return "-ERR wrong number of arguments for 'echo' command" + CRLF;
    }
    std::string message = resps[1].value;
    return "$" + std::to_string(message.size()) + CRLF + message + CRLF;
}

std::string ping(const std::vector<RESP> &resps){
    if(resps.size() == 1){
        return "+PONG" + CRLF;
    }else{
        return "-ERR wrong number of arguments for 'ping' command" + CRLF;
    }
}