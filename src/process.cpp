#include "proc11/process.h"

proc11::process::process(const std::string& path)
{
    std::vector<std::string> args;
    execute(path,args.begin(),args.end());
}

void proc11::process::execute(std::vector<char*>& args)
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
        _exit(child_status);
    }
    else
    {
        _process_id = pid;
    }
#endif
}

void proc11::process::send_signal(proc11::signal_type signal)
{
#if defined(_WIN32)
    if (true)
    {
        
    }
#else
    if (kill(_process_id,signal) == -1)
    {
        throw std::runtime_error("kill failed: " + errno);
    }
#endif
}


void proc11::process::wait()
{
#if defined(_WIN32)
    
#else
    if (_process_id > 0)
    {
        int exit_status,result;
        result = waitpid(_process_id,&exit_status,0);
        if (result < 0)
        {

        }
    }
#endif
}