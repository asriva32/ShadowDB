#ifndef RESP_H
#define RESP_H
#include "resp_types.h"

std::shared_ptr<RespType> perform_command(const RespArray &r);
std::string parse_resp(const std::string &input);

#endif //RESP_H