#include "../include/resp.h"
#include "../include/commands.h"
#include "../include/resp_types.h"
#include <stdexcept>
#include <iostream>
#include <algorithm>

Resp build_resp_array(const std::string &input){
    if(input.length() == 0){
        return Resp("ERR Protocol error: invalid request length", RespType::ERROR);
    }

    if(input[0] != '*'){
        return Resp("ERR Protocol error: expected '*'", RespType::ERROR);
    }

    int p = input.find(CRLF);
    if(p == std::string::npos){
        return Resp("ERR Invalid format no CRLF found", RespType::ERROR);
    }

    int len = std::stoi(input.substr(1, p - 1));
    if(len <= 0){
        return Resp("ERR Protocol error: invalid array length", RespType::ERROR);
    }
    std::vector<Resp> resps;
    for(int i = p + 2; i < input.length();i++){
        if(RESP_TYPE_MAP.find(input[i]) == RESP_TYPE_MAP.end()){
            return Resp("ERR Protocol error: invalid type", RespType::ERROR);
        }

        RespType type = RESP_TYPE_MAP.at(input[i]);

        int pos = input.find(CRLF, i);
        if(pos == std::string::npos){
            return Resp("ERR Protocol error: invalid bulk string format", RespType::ERROR);
        }

        int s_length = std::stoi(input.substr(i + 1, pos - i - 1));

        int next_pos = input.find(CRLF, pos + 2);
        if(next_pos == std::string::npos){
            return Resp("ERR Protocol error: invalid bulk string format", RespType::ERROR);
        }

        std::string data = s_length == 0 ? "" : input.substr(pos + 2, s_length);
        resps.emplace_back(Resp(data, RespType::BULK_STRING));

        i = next_pos + 1;
    }

    if(resps.size() != len){
        return Resp("ERR Protocol error: invalid multibulk length", RespType::ERROR);
    }
    return Resp(resps, RespType::ARRAY);
}


Resp perform_command(const Resp &r){
    std::vector<Resp> resps = std::get<std::vector<Resp>>(r.getRaw());
    if(resps.size() == 0){
        return Resp("ERR unknown command", RespType::ERROR);
    }

    std::string command = std::get<std::string>(resps[0].getRaw());
    std::transform(command.begin(), command.end(), command.begin(), ::tolower);

    if(COMMAND_MAP.find(command) != COMMAND_MAP.end()){
        return COMMAND_MAP.at(command)(resps);
    }else{
        return Resp("ERR unknown command " + command, RespType::ERROR);
    }
}

std::string parse_request(const std::string &input){
    return perform_command(build_resp_array(input)).getSerialized();
}