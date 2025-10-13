#ifndef RESP_H
#define RESP_H
#include "resp_types.h"

Resp build_resp_array(const std::string &input);
Resp perform_command(const Resp &r);
std::string parse_request(const std::string &input);

#endif //RESP_H