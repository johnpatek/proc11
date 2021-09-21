#include <iostream>
#include <memory>
#include <proc11.h>
#include <thread>
int main(int argc, const char ** argv)
{
    std::shared_ptr<proc11::process> process_handle;
    if (argc == 2)
    {
        try 
        {
            std::cout << "parent start" << std::endl;
            process_handle = std::make_shared<proc11::process>(argv[1]);
            std::cout << "parent sleep" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(3));
            process_handle->send_signal(proc11::signal_type::PROC11_SIGINT);
            process_handle->wait();
            std::cout << "parent end" << std::endl;
        }
        catch(const std::exception& exception)
        {
            std::cerr << "error:" << exception.what() << std::endl;   
        }
    }
    else
    {
        std::cerr << "usage: parent <child executable>" << std::endl;
    }
    return 0;
}