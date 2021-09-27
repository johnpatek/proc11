#include <proc11.h>
#include <fstream>

int main(int argc,char ** argv)
{
    proc11::process_id_type parent_id;
    proc11::signal_type current_signal;

    if(argc >= 3)
    {
        parent_id = static_cast<proc11::process_id_type>(
                std::stoi(argv[1]));

        for(int offset = 2; offset < argc; offset++)
        {
            current_signal = static_cast<proc11::signal_type>(
                std::stoi(argv[offset]));
            proc11::kill(parent_id,current_signal);
        }
    }
    return 0;
}