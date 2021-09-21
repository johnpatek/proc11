#ifndef PROC11_PROCESS_H
#define PROC11_PROCESS_H

#include "common.h"

#define DEBUGLN(message) std::cerr << message << std::endl


namespace proc11
{

class process
{
private:

public:
    process() = default;

    process(const std::string& path);

    template<class InputIt> process(const std::string& path,InputIt first, InputIt last)
    {
        execute(path,first,last);
    }

    process(process& copy)= delete;

    process(process&& move) = default;

    ~process() = default;

    template<class InputIt> void execute(const std::string& path,InputIt first, InputIt last)
    {
        std::vector<char*> args;
        args.reserve(std::distance(first,last) + 2);
        args.push_back(const_cast<char*>(path.c_str()));
        std::for_each(first,last,[&](const std::string& arg)
        {
            args.push_back(const_cast<char*>(arg.c_str()));
        });
        args.push_back(nullptr);
        execute(args);
    }


    void send_signal(signal_type signal);

    void wait();

private:
    void execute(std::vector<char*>& args);
    process_handle_type _process_id;
};

}

#endif