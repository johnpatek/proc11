#include "proc11/signal_handler.h"

namespace proc11
{

std::unique_ptr<signal_handler> signal_handler::_global_handler(nullptr);

void signal_handler::on_signal(int signal)
{
    map_type::iterator callback_iterator;
    callback_iterator = _global_handler->_callback_map.find(
        static_cast<signal_type>(signal));
    if (callback_iterator == _global_handler->_callback_map.end())
    {
        throw std::runtime_error("no callback registered for signal " + signal);
    }
    callback_iterator->second(callback_iterator->first);
}

signal_handler::signal_handler(signal_handler&& move)
{
    if (_global_handler.get() != nullptr)
    {
        throw std::runtime_error("unable to move dispatched signal handler");
    }
    _callback_map = std::move(move._callback_map);
}

signal_handler::~signal_handler()
{
    if (_global_handler.get() != nullptr)
    {
        shutdown();
    }
}

void signal_handler::add_callback(signal_type signal, signal_callback_type callback)
{
    if (_callback_map.find(signal) != _callback_map.end())
    {
        throw std::runtime_error("callback already registered for signal " + signal);
    }
    _callback_map.emplace(signal,callback);
    std::signal(signal,signal_handler::on_signal);
}

void signal_handler::remove_callback(signal_type signal)
{
    std::signal(signal,SIG_DFL);
    map_type::iterator callback_iterator;
    callback_iterator = _callback_map.find(signal);
    if (callback_iterator == _callback_map.end())
    {
        throw std::runtime_error("no callback registered for signal " + signal);
    }
    _callback_map.erase(callback_iterator);
}

void signal_handler::dispatch()
{
    if (_global_handler.get() != nullptr)
    {
        throw std::runtime_error("another signal handler already dispatched");
    }
    _global_handler = std::unique_ptr<signal_handler>(this);
}

void signal_handler::shutdown()
{
    _global_handler.release();
}

}