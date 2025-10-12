#include "include/resp.h"
#include "include/commands.h"
#include <stdexcept>
#include <iostream>
#include <algorithm>

const std::string CRLF = "\r\n";

std::string parse_commands(const std::vector<RESP> &resps){
    if(resps.size() == 0){
        return "-ERR unknown command" + CRLF;
    }
    if(resps[0].type != RESPType::BULK_STRING){
        return "-ERR unexpected command" + CRLF;
    }

    std::string command = resps[0].value;
    std::transform(command.begin(), command.end(), command.begin(), ::tolower);

    if(COMMAND_MAP.find(command) != COMMAND_MAP.end()){
        return COMMAND_MAP.at(command)(resps);
    }else{
        return "-ERR unknown command " + command + CRLF;
    }
}


std::string parse_resp(std::string data){

    if(data.length() == 0){
        return "-ERR Protocol error: invalid request length" + CRLF;
    }

    if(data[0] != '*'){
        return "-ERR Protocol error: expected '*'" + CRLF;
    }

    int p = data.find(CRLF);
    if(p == std::string::npos){
        return "-ERR Invalid format no CRLF found" + CRLF;
    }

    int len = std::stoi(data.substr(1, p - 1));
    if(len <= 0){
        return "-ERR Protocol error: invalid array length" + CRLF;
    }

    std::vector<RESP> resps;
    for(int i = p + 2; i < data.length();i++){
        if(RESP_TYPE_MAP.find(data[i]) == RESP_TYPE_MAP.end()){
            return "-ERR Protocol error: invalid type" + CRLF;
        }

        RESPType type = RESP_TYPE_MAP.at(data[i]);

        int pos = data.find(CRLF, i);
        if(pos == std::string::npos){
            return "-ERR Protocol error: invalid bulk string format" + CRLF;
        }

        int s_length = std::stoi(data.substr(i + 1, pos - i - 1));

        int next_pos = data.find(CRLF, pos + 2);
        if(next_pos == std::string::npos){
            return "-ERR Protocol error: invalid bulk string format" + CRLF;
        }

        std::string data = s_length == 0 ? "" : data.substr(pos + 2, s_length);
        resps.push_back(RESP(type, data));

        i = next_pos + 1;
    }

    if(resps.size() != len){
        return "-ERR Protocol error: invalid multibulk length" + CRLF;
    }

    return parse_commands(resps);
}