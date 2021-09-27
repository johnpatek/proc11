#include <gtest/gtest.h>
#include <proc11/process.h>
#include <fstream>
#include <random>


const std::string ALPHANUMERIC_CHARACTERS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";


template<class RNG>
std::string generate_random_string(
    int length,
    RNG& generator)
{
    std::string characters(ALPHANUMERIC_CHARACTERS);
    std::shuffle(characters.begin(),characters.end(),generator);
    return characters.substr(0,static_cast<size_t>(length));
}

TEST(process,args_test)
{
    std::random_device random_device;
    std::default_random_engine generator(random_device());
    std::uniform_int_distribution<int> arg_count_distribution(5,10);
    std::uniform_int_distribution<int> arg_length_distribution(1,10);
    std::vector<std::string> args,logged_args;
    
    int arg_count = arg_count_distribution(generator);
    args.reserve(arg_count);
    logged_args.reserve(arg_count);

    while(args.size() < args.capacity())
    {
        args.push_back(generate_random_string(
            arg_length_distribution(generator),
            generator));
    }

    proc11::process subprocess(
        "test/arg_logger",
        args.begin(),
        args.end());

    EXPECT_NE(proc11::current_process_id(),subprocess.id());

    subprocess.wait();

    std::ifstream arg_log("arg_log.txt");

    for(std::string line_buffer; std::getline(arg_log,line_buffer);)
    {
        logged_args.push_back(line_buffer);
    }

    for(size_t arg_index = 0; arg_index < args.size(); arg_index++)
    {
        EXPECT_EQ(args[arg_index],logged_args[arg_index]);
    }
    
    arg_log.close();

    std::remove("arg_log.txt");
}