#include "proc11/signal_handler.h"


proc11::signal_handler::~signal_handler()
{
    if (_running)
    {
        shutdown();
    }
}

void proc11::signal_handler::register_callback(
    proc11::signal_type signal,
    std::function<void(proc11::signal_type)>& callback)
{
    _callbacks.emplace(signal,callback);
    sigaddset(&_base_sigset,signal);
}

void proc11::signal_handler::remove_callback(
    proc11::signal_type signal)
{
    _callbacks.erase(signal);
    sigdelset(&_base_sigset,signal);
}

void proc11::signal_handler::dispatch()
{
    sigset_t pending_sigset;
    signal_type current_signal;
    _running = true;
    while(_running)
    {
        std::memcpy(&pending_sigset,&_base_sigset,sizeof(sigset_t));
        
        if (sigprocmask(SIG_SETMASK,&pending_sigset,nullptr) < 0)
        {
            throw std::runtime_error("error: sigprocmask " + errno);
        }
        
        if (sigpending(&pending_sigset) < 0)
        {
            throw std::runtime_error("error: sigpending " + errno);    
        }

        std::for_each(
            _callbacks.begin(),
            _callbacks.end(),
        [&](const std::pair<signal_type,std::function<void(signal_type)>>& callback)
        {
            current_signal = callback.first;
            if(sigismember(&pending_sigset,current_signal) == 1)
            {
                callback.second(callback.first);
            }
        });
    }
}

void proc11::signal_handler::shutdown()
{
    _running = false;
}