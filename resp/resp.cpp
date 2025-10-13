#include "../include/resp.h"
#include "../include/commands.h"
#include <stdexcept>
#include <iostream>
#include <algorithm>


std::shared_ptr<RespType> perform_command(std::shared_ptr<RespArray> r){
    std::vector<BulkString> resps = r->getArray();
    if(resps.size() == 0){
        return std::make_shared<RespError>("ERR unknown command");
    }

    std::string command = resps[0].getRaw();
    std::transform(command.begin(), command.end(), command.begin(), ::tolower);

    if(COMMAND_MAP.find(command) != COMMAND_MAP.end()){
        return COMMAND_MAP.at(command)(resps);
    }else{
        return std::make_shared<RespError>("ERR unknown command " + command);
    }
}

std::string parse_resp(const std::string &input){
    std::shared_ptr<RespType> res = RespType::build_resp_array(input);
    switch(res->getUnderlyingType()){
        case RESPType::ERROR:
            return res->getSerialized();
        case RESPType::ARRAY:
            return perform_command(std::dynamic_pointer_cast<RespArray>(res))->getSerialized();
        default:
            return "-ERRUnexpected Result - This branch should not execute" + CRLF;
    }
}