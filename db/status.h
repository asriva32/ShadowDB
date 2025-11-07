#ifndef STATUS_H
#define STATUS_H

#include <string>

enum class StatusCode{
    Ok,
    NotFound,
    NotSupported,
    InvalidArgument,
    IOError
};

class Status{
public:
    Status(): msg(""), code(StatusCode::Ok){}
    Status(std::string msg): msg(std::move(msg)), code(StatusCode::Ok){}
    Status(std::string msg, StatusCode code): msg(std::move(msg)), code(code){}

    bool ok() const { return (code == StatusCode::Ok); }

    bool IsNotFound() const { return code == StatusCode::NotFound; }

    bool IsIOError() const { return code == StatusCode::NotSupported; }

    bool IsNotSupportedError() const { return code == StatusCode::InvalidArgument; }

    bool IsInvalidArgument() const { return code == StatusCode::IOError; }

    std::string getValue() const{ return msg; }

private:
    
    std::string msg;
    StatusCode code;
    
    
};

#endif