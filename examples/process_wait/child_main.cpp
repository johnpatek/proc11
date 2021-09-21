#include <iostream>
#include <thread>

int main(int argc, const char ** argv)
{
    std::cout << "child start" << std::endl;
    std::cout << "child sleep" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cout << "child end" << std::endl;
    return 0;
}