#include <iostream>
#include <thread>
#include <proc11.h>

int main(int argc, const char ** argv)
{
    proc11::signal_handler handler;
    
    std::cout << "child start" << std::endl;
    
    std::function<void(proc11::signal_type)> callback(
        [&](proc11::signal_type signal)
    {
        std::cout << "child received signal: " << signal << std::endl;
        handler.shutdown();
    });

    handler.register_callback(proc11::signal_type::PROC11_SIGINT,callback);

    handler.dispatch();

    std::cout << "child end" << std::endl;

    return 0;
}