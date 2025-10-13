#ifndef COMMANDS_H
#define COMMANDS_H

#include "resp.h"
#include <string>
#include <unordered_map>
#include <functional>
#include <vector>


Resp get(const std::vector<Resp> &resps);
Resp set(const std::vector<Resp> &resps);
Resp echo(const std::vector<Resp> &resps);
Resp ping(const std::vector<Resp> &resps);

const std::unordered_map<std::string, std::function<Resp(const std::vector<Resp>&)>> COMMAND_MAP = {
    {"set", set},
    {"get", get},
    {"echo", echo},
    {"ping", ping}
};



#endif // COMMANDS_H