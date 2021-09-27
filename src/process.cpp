#include "proc11/process.h"

namespace proc11
{

process::process(const std::string& path)
{
    std::vector<std::string> args;
    execute(path,args.begin(),args.end());
}

void process::execute(std::vector<char*>& args)
{
#if defined(_WIN32)

#else
    pid_t pid = fork();
    if (pid < 0)
    {
        throw std::runtime_error("failed to fork process");
    }
    else if (pid == 0)
    {
        int child_status = execv(args.front(),args.data());
        if (child_status < 0)
        {
            throw std::runtime_error("child process failed to execute " + errno);
        }
        _exit(child_status);
    }
    else
    {
        _process_id = pid;
    }
#endif
}

process_id_type process::id() const
{
    return _process_id;
}

void process::wait()
{
#if defined(_WIN32)
    
#else
    if (_process_id > 0)
    {
        int exit_status,result;
        result = waitpid(_process_id,&exit_status,0);
        if (result < 0)
        {
            throw std::runtime_error("failed to wait for pid: " + _process_id);
        }
    }
#endif
}

process_id_type current_process_id()
{
#if defined(_WIN32)
    return GetCurrentProcessId();
#else
    return getpid();
#endif
}

}