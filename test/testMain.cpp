#ifndef ELPP_NO_LOG_TO_FILE
    #define ELPP_NO_LOG_TO_FILE
#endif
#ifndef ELPP_NO_DEFAULT_LOG_FILE
    #define ELPP_NO_DEFAULT_LOG_FILE
#endif

#include "gtest/gtest.h"
#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP

int main(int argc, char* argv[])
{
    el::Configurations conf("log.conf");
    el::Loggers::reconfigureAllLoggers( conf);

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
