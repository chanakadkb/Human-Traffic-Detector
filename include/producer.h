#include <buffer.h>
#include <opencv2/videoio.hpp>
#include <unistd.h>
#include <thread>
#include <ctime>


class Producer{
    public :
        Producer(Camera cam,CONFIG config,Buffer<cam_feed>* buf);
        void run();//should be run in a thread
        bool connected();
    private:
        CONFIG config;
        Buffer<cam_feed>* buffer;
        bool isconnected=false;
        Camera cam;
        std::string id;
};
