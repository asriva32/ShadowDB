#include "../../include/resp.h"
#include "../../include/commands.h"
#include <stdexcept>
#include <iostream>
#include <algorithm>

const std::string CRLF = "\r\n";

std::string parse_commands(const std::vector<RESP> &resps){
    if(resps.size() == 0){
        return "-ERR unknown command \r\n";
    }
    if(resps[0].type != RESPType::BULK_STRING){
        return "-ERR unexpected command \r\n";
    }

    std::string command = resps[0].value;
    std::transform(command.begin(), command.end(), command.begin(), ::tolower);
    if(COMMAND_MAP.find(command) != COMMAND_MAP.end()){
        return COMMAND_MAP.at(command)(resps);
    }else{
        return "-ERR unknown command " + command + "'\r\n";
    }
}


std::string parse_resp(const char* data, size_t length){
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
        RESP r(type, data);
        resps.push_back(r);

        i = next_pos + 1;
    }
    if(resps.size() != len){
        return "-ERR Protocol error: invalid multibulk length\r\n";
    }
    return parse_commands(resps);

}