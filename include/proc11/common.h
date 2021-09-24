#ifndef PROC11_COMMON_H
#define PROC11_COMMON_H
// std c++ headers
#include <algorithm> // std::for_each()
#include <atomic> // std::atomic<bool>
#include <functional> // std::function
#include <map> // std::map
#include <queue> // std::queue
#include <stdexcept> // std::runtime_error
#include <string> // std::string
#include <vector> // std::vector
// C headers
#include <cstring> // std::memcpy
#include <csignal> // sigaction, SIG{TERM,SEGV,INT,ILL,ABRT,FPE}
#ifdef _WIN32
// windows headers    
#include <Windows.h>
#else
// posix headers
#include <sys/types.h> // pid_t 
#include <sys/wait.h> // waitpid()
#include <unistd.h> // fork(), execv()
#endif
#define SIGNALDEF(SIGNAL) PROC11_ ## SIGNAL = SIGNAL 

namespace proc11
{
enum signal_type
{
#if defined(_WIN32)
    SIGNALDEF(SIGBREAK),
#endif
    SIGNALDEF(SIGTERM),
    SIGNALDEF(SIGSEGV),
    SIGNALDEF(SIGINT),
    SIGNALDEF(SIGILL),
    SIGNALDEF(SIGABRT),
    SIGNALDEF(SIGFPE)
};
#ifdef _WIN32
    typedef DWORD process_handle_type;
#else
    typedef pid_t process_handle_type;
#endif
}
#endif