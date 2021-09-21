#include <iostream>
#include <memory>
#include <proc11.h>

int main(int argc, const char ** argv)
{
    std::shared_ptr<proc11::process> process_handle;
    if (argc == 2)
    {
        try 
        {
            std::cout << "parent start" << std::endl;
            process_handle = std::make_shared<proc11::process>(argv[1]);
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