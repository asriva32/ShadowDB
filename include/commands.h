#ifndef COMMANDS_H
#define COMMANDS_H

#include "resp.h"
#include <string>
#include <unordered_map>
#include <functional>
#include <vector>


std::shared_ptr<RespType> get(const std::vector<BulkString> &resps);
std::shared_ptr<RespType> set(const std::vector<BulkString> &resps);
std::shared_ptr<RespType> echo(const std::vector<BulkString> &resps);
std::shared_ptr<RespType> ping(const std::vector<BulkString> &resps);

const std::unordered_map<std::string, std::function<std::shared_ptr<RespType>(const std::vector<BulkString>&)>> COMMAND_MAP = {
    {"set", set},
    {"get", get},
    {"echo", echo},
    {"ping", ping}
};



#endif // COMMANDS_H