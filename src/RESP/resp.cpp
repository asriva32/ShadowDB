#include "resp.h"
#include <stdexcept>
#include <iostream>
#include <algorithm>

const std::string CRLF = "\r\n";

std::string parse_commands(const std::vector<RESP> &resps, KVStore &kv){
    if(resps.size() == 0){
        return "-ERR unknown command \r\n";
    }
    if(resps[0].type != RESPType::BULK_STRING){
        return "-ERR unexpected command \r\n";
    }
    std::string command = std::get<std::string>(resps[0].value);
    std::transform(command.begin(), command.end(), command.begin(), ::tolower);
    if(command == "ping"){
        return "+PONG\r\n";
    }else if(command == "echo"){
        if(resps.size() != 2 || resps[1].type != RESPType::BULK_STRING){
            return "-ERR wrong number of arguments for 'echo' command\r\n";
        }
        std::string message = std::get<std::string>(resps[1].value);
        return "$" + std::to_string(message.size()) + CRLF + message + CRLF;
    }else if(command == "get"){
        if(resps.size() != 2 || resps[1].type != RESPType::BULK_STRING){
            return "-ERR wrong number of arguments for 'get' command\r\n";
        }
        std::string key = std::get<std::string>(resps[1].value);
        std::string value = kv.get(key);
        if(value == "-1"){
            return "$-1\r\n";
        }
        return "$" + std::to_string(value.length()) + CRLF + value + CRLF;
    }else if(command == "set"){
        if(resps.size() != 3 || resps[1].type != RESPType::BULK_STRING || resps[2].type != RESPType::BULK_STRING){
            return "-ERR wrong number of arguments for 'set' command\r\n";
        }
        std::string key = std::get<std::string>(resps[1].value);
        std::string value = std::get<std::string>(resps[2].value);
        std::string result = kv.set(key, value);
        return "+" + result + CRLF;
    }else{
        return "-ERR unknown command " + command + "'\r\n";
    }
}


std::string parse_resp(const char* data, size_t length, KVStore &kv){
    if(length == 0){
        return "-ERR Protocol error: invalid request length\r\n";
    }

    std::string sv(data, length);
    if(sv[0] != '*'){
        return "-ERR Protocol error: expected '*'\r\n";
    }
    int p = sv.find(CRLF);
    if(p == std::string::npos){
        return "-ERR Invlaid format no CRLF found\r\n";
    }
    int len = std::stoi(sv.substr(1, p - 1));
    if(len <= 0){
        return "-ERR Protocol error: invalid array length\r\n";
    }
    std::vector<RESP> resps;
    for(int i = p + 2; i < sv.length();i++){
        if(RESP_TYPE_MAP.find(sv[i]) == RESP_TYPE_MAP.end()){
            return "-ERR Protocol error: invalid type\r\n";
        }
        RESPType type = RESP_TYPE_MAP.at(sv[i]);

        int pos = sv.find(CRLF, i);
        if(pos == std::string::npos){
            return "-ERR Protocol error: invalid bulk string format\r\n";
        }
        int s_length = std::stoi(sv.substr(i + 1, pos - i - 1));
        int next_pos = sv.find(CRLF, pos + 2);
        if(next_pos == std::string::npos){
            return "-ERR Protocol error: invalid bulk string format\r\n";
        }
        std::string data = s_length == 0 ? "" : sv.substr(pos + 2, s_length);
        RESP r = RESP(type, data);
        resps.push_back(r);

        i = next_pos + 1;
    }
    if(resps.size() != len){
        return "-ERR Protocol error: invalid multibulk length\r\n";
    }
    return parse_commands(resps, kv);

}