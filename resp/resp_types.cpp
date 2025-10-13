#include "include/resp_types.h"

std::shared_ptr<RespType> RespType::build_resp_array(const std::string &input){
    if(input.length() == 0){
        return std::make_shared<RespError>("ERR Protocol error: invalid request length");
    }

    if(input[0] != '*'){
        return std::make_shared<RespError>("-ERR Protocol error: expected '*'");
    }

    int p = input.find(CRLF);
    if(p == std::string::npos){
        return std::make_shared<RespError>("-ERR Invalid format no CRLF found");
    }

    int len = std::stoi(input.substr(1, p - 1));
    if(len <= 0){
        return std::make_shared<RespError>("-ERR Protocol error: invalid array length");
    }
    std::vector<BulkString> resps;
    for(int i = p + 2; i < input.length();i++){
        if(RESP_TYPE_MAP.find(input[i]) == RESP_TYPE_MAP.end()){
            return std::make_shared<RespError>("-ERR Protocol error: invalid type");
        }

        RESPType type = RESP_TYPE_MAP.at(input[i]);

        int pos = input.find(CRLF, i);
        if(pos == std::string::npos){
            return std::make_shared<RespError>("-ERR Protocol error: invalid bulk string format");
        }

        int s_length = std::stoi(input.substr(i + 1, pos - i - 1));

        int next_pos = input.find(CRLF, pos + 2);
        if(next_pos == std::string::npos){
            return std::make_shared<RespError>("-ERR Protocol error: invalid bulk string format");
        }

        std::string input = s_length == 0 ? "" : input.substr(pos + 2, s_length);
        resps.emplace_back(BulkString(input));

        i = next_pos + 1;
    }

    if(resps.size() != len){
        return std::make_shared<RespError>("-ERR Protocol error: invalid multibulk length");
    }
    return std::make_shared<RespArray>(resps);
}