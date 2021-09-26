#include <gtest/gtest.h>
#include <proc11.h>

TEST(signal_handler,basic_test)
{
    proc11::signal_handler handler;

    proc11::signal_type current;    

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

    proc11::signal_callback_type callback(
        [&](proc11::signal_type signal)
        {
            current = signal;
        });

    std::for_each(
        signals.begin(),
        signals.end(),
        [&](proc11::signal_type signal)
        {
            handler.add_callback(
                signal,
                callback);
        });

    handler.dispatch();

    std::for_each(
        signals.begin(),
        signals.end(),
        [&](proc11::signal_type signal)
        {
            std::raise(static_cast<int>(signal));
            EXPECT_EQ(current,signal);
        });
}