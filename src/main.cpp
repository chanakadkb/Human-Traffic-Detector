#include "easylogging++.h"
#include <buffer.h>
#include <producer_pool.h>
#include <consumer_pool.h>

INITIALIZE_EASYLOGGINGPP


int main (int argc, char *argv[])
{
    el::Configurations conf("log.conf");
    el::Loggers::reconfigureAllLoggers( conf);

    Configurations config;
    config.load();

    Buffer<cam_feed> input_buff(config.get().input_buf);  //input buffer
    Buffer<output> output_buff(config.get().output_buf);   //output buffer

    Writer writer(config.get().output_file);
    output_buff.addWriter(&writer);


    Poco::ThreadPool threadpool;


    ProducerPool producer(&input_buff,config.get());
    ConsumerPool consumer(&input_buff,config.get(),&output_buff);

    threadpool.start(producer);
    threadpool.start(consumer);

    threadpool.joinAll();

    return 0;
}
