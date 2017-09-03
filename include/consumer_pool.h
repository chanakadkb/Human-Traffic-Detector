#include <consumer.h>
#include "Poco/ThreadPool.h"


class ConsumerPool: public Poco::Runnable{  //start some number of thread to process Mats
    public :
        ConsumerPool(Buffer<cam_feed>* in_buf,CONFIG config,Buffer<output>* out_buf);
        virtual void run();  //start threads to operate each feed
        void stop();  //stop all threads that have started
    private:
        CONFIG config;
        Buffer<cam_feed>* in_buf;
        Buffer<output>* out_buf;
};
