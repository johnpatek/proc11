#include <fstream> // std::ofstream

int main(int argc, char ** argv)
{
    std::ofstream arg_log("arg_log.txt");
    if(argc > 1)
    {
        for(int offset = 1; offset < argc; offset++)
        {
            arg_log << argv[offset] << std::endl;
        }
    }
    return 0;
}