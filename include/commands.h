#ifndef COMMANDS_H
#define COMMANDS_H
#include "resp.h"
#include <string>
#include <unordered_map>
#include <functional>
#include <vector>


std::string get(const std::vector<RESP> &resps);
std::string set(const std::vector<RESP> &resps);
std::string echo(const std::vector<RESP> &resps);
std::string ping(const std::vector<RESP> &resps);

const std::unordered_map<std::string, std::function<std::string(const std::vector<RESP>&)>> COMMAND_MAP = {
    {"set", set},
    {"get", get},
    {"echo", echo},
    {"ping", ping}
};



#endif // COMMANDS_H