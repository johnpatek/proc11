#ifndef PROC11_SIGNAL_HANDLER_H
#define PROC11_SIGNAL_HANDLER_H
#include "common.h"
namespace proc11
{

typedef std::function<void(signal_type)> signal_callback_type;

typedef std::map<signal_type,signal_callback_type> map_type;

class signal_handler
{
public:

    signal_handler() = default;

    signal_handler(const signal_handler& copy) = delete;

    signal_handler(signal_handler&& move);

    ~signal_handler();

    void add_callback(signal_type signal, signal_callback_type callback);

    void remove_callback(signal_type signal);

    void dispatch();

    void shutdown();

private:
    static void on_signal(int signal);
    static std::unique_ptr<signal_handler> _global_handler;
    map_type _callback_map;
};

void kill(process_id_type process_id,signal_type signal);

void raise(signal_type signal);

}
#endif