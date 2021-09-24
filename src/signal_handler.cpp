#include "proc11/signal_handler.h"


#if defined(_WIN32)

void handler_function(int signal)
{
    if(!proc11::signal_handler::_initialized.load())
    {
        throw std::runtime_error("no signal handler exists for this process");
    }
    proc11::signal_handler::_pending.emplace(
        static_cast<proc11::signal_type>(signal));
}


proc11::signal_handler::signal_handler()
{
    if (_initialized.load())
    {
        throw std::runtime_error("signal handler already exists for this process");
    }
    _initialized.store(true);
}
#endif


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
#if defined(_WIN32)
    std::signal(signal,handler_function);
#else
    sigaddset(&_base_sigset,signal);
#endif
}

void proc11::signal_handler::remove_callback(
    proc11::signal_type signal)
{
    _callbacks.erase(signal);
#if defined(_WIN32)
    std::signal(signal,SIG_DFL);
#else    
    sigdelset(&_base_sigset,signal);
#endif
}

void proc11::signal_handler::dispatch()
{
    signal_type current_signal;
#if defined(_WIN32)
    while(_running)
    {
        while(!_pending.empty())
        {
            current_signal = _pending.front();
            std::function<void(signal_type)>& callback = _callbacks.at(current_signal);
            if(callback)
            {
                callback(current_signal);
            }
            _pending.pop();
        }
    }
#else
    sigset_t pending_sigset;
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
#endif
}

void proc11::signal_handler::shutdown()
{
    _running = false;

    for (const std::pair<signal_type,std::function<void(signal_type)>>& callback : _callbacks)
    {
        remove_callback(callback.first);
    }

#if defined(_WIN32)    
    _initialized.store(false);
#endif
}