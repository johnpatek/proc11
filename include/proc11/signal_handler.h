#ifndef PROC11_SIGNAL_HANDLER_H
#define PROC11_SIGNAL_HANDLER_H

#include "common.h"
namespace proc11
{

class signal_handler
{
public:
    signal_handler() = default;
    
    signal_handler(const signal_handler& copy) = delete;

    signal_handler(signal_handler&& copy) = default;

    ~signal_handler();

    void register_callback(
        signal_type signal,
        std::function<void(signal_type)>& callback);

    void remove_callback(signal_type signal);

    void dispatch();

    void shutdown();

private:
    bool _running;
    sigset_t _base_sigset;
    std::map<signal_type,std::function<void(signal_type)>> _callbacks;
};

}
#endif