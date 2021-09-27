#include <gtest/gtest.h>
#include <proc11.h>
#include <fstream>

std::initializer_list<proc11::signal_type> signals(
{
#if defined(_WIN32)
    proc11::signal_type::PROC11_SIGBREAK,
#endif
    proc11::signal_type::PROC11_SIGTERM,
    proc11::signal_type::PROC11_SIGSEGV,
    proc11::signal_type::PROC11_SIGINT,
    proc11::signal_type::PROC11_SIGILL,
    proc11::signal_type::PROC11_SIGABRT,
    proc11::signal_type::PROC11_SIGFPE
});

TEST(signal,raise_test)
{
    proc11::signal_handler handler;

    proc11::signal_type current;    

    proc11::signal_callback_type callback(
        [&](proc11::signal_type signal)
        {
            current = signal;
        });

    for(proc11::signal_type signal : signals)
    {
        handler.add_callback(
            signal,
            callback);
    }

    handler.dispatch();

    for(proc11::signal_type signal : signals)
    {
        std::raise(static_cast<int>(signal));
        EXPECT_EQ(current,signal);
    }
}

#if defined(_WIN32)

#else

TEST(signal,kill_test)
{
    proc11::signal_handler handler;
    std::map<proc11::signal_type,bool> signal_collector;
    std::vector<std::string> subprocess_args;
    std::shared_ptr<proc11::process> subprocess;
    
    proc11::signal_callback_type callback(
        [&](proc11::signal_type signal)
        {
            // record signal
            signal_collector[signal] = true;
        });

    subprocess_args.reserve(signals.size() + 1);

    subprocess_args.push_back(
        std::to_string(
            proc11::current_process_id()));

    for(proc11::signal_type signal : signals)
    {
        // add all expected signals
        signal_collector.emplace(signal,false);
        // bind callback to each signal
        handler.add_callback(signal,callback);
        // add signal value as arg for subprocess
        subprocess_args.push_back(std::to_string(signal));
    }

    handler.dispatch();

    // Start child process to send signals back to parent
    subprocess = std::make_shared<proc11::process>(
        "test/signaler",
        subprocess_args.begin(),
        subprocess_args.end());
    
    subprocess->wait();

    for(proc11::signal_type signal : signals)
    {
        // verify signal was received
        EXPECT_TRUE(signal_collector[signal]);
    }
}
#endif