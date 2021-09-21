#ifndef PROC11_COMMON_H
#define PROC11_COMMON_H
// std c++ headers
#include <algorithm> // std::for_each()
#include <functional> // std::function
#include <stdexcept> // std::runtime_error
#include <string> // std::string
#include <vector> // std::vector
#include <map> // std::map
// C headers
#include <cstring> // std::memcpy
#ifdef WIN32
// windows headers    
#else
// posix headers
#include <signal.h> // sigaction
#include <sys/types.h> // pid_t 
#include <sys/wait.h> // waitpid()
#include <unistd.h> // fork(), execv()
#endif

#define SIGNALDEF(SIGNAL) PROC11_ ## SIGNAL = SIGNAL 

namespace proc11
{
enum signal_type
{
    SIGNALDEF(SIGTERM),
    SIGNALDEF(SIGSEGV),
    SIGNALDEF(SIGINT),
    SIGNALDEF(SIGILL),
    SIGNALDEF(SIGABRT),
    SIGNALDEF(SIGFPE),
#ifndef WIN32
    // TODO: add unix specific signals
#endif
};
#ifdef WIN32
    
#else
    typedef pid_t process_handle_type;
#endif
}
#endif