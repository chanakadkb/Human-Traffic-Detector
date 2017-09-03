#include <producer.h>
#include "Poco/Thread.h"
#include "Poco/Runnable.h"

class ProducerPool: public Poco::Runnable{  //start each cam-connection in a seperate thread;
    public :
        ProducerPool(Buffer<cam_feed>* buf,CONFIG config);
        virtual void run();  //start and join listeners for all cams given in config file
        void stop();  //stop all threads that has started
    private:
        CONFIG config;
        Buffer<cam_feed>* buf;
};
