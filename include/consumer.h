#include <config.h>
#include <buffer.h>
#include <operate.h>
#include "Poco/Thread.h"
#include "Poco/Runnable.h"

class Consumer{
    public :
        Consumer(Buffer<cam_feed>* in_buf,CONFIG config,Buffer<output>* out_buf);
        void run();//should be run in a thread
    private:

        int interval;
        CONFIG config;
        Buffer<output>* out_buf;
        Buffer<cam_feed>* in_buf;
};
