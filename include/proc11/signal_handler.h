#ifndef PROC11_SIGNAL_HANDLER_H
#define PROC11_SIGNAL_HANDLER_H

#include "common.h"
namespace proc11
{

class signal_handler
{
public:
#if defined(_WIN32)
    signal_handler();
#else
    signal_handler() = default;
#endif    
    signal_handler(const signal_handler& copy) = delete;

    signal_handler(signal_handler&& copy) = default;

    ~signal_handler();

    void register_callback(
        signal_type signal,
        std::function<void(signal_type)>& callback);

    void remove_callback(signal_type signal);

    void dispatch();

    void shutdown();
#if defined(_WIN32)
    static std::queue<signal_type> _pending;
    static std::atomic<bool> _initialized;
private:
#else
private:
    sigset_t _base_sigset;
#endif
    bool _running;
    std::map<signal_type,std::function<void(signal_type)>> _callbacks;
};

}
#endif