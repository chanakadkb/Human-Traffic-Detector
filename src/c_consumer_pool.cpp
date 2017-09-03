#include <consumer_pool.h>

ConsumerPool::ConsumerPool(Buffer<cam_feed>* in_buf,CONFIG config,Buffer<output>* out_buf){
    this->in_buf=in_buf;
    this->out_buf=out_buf;
    this->config=config;
}

void ConsumerPool::run(){
    std::vector<std::thread> threads;
    threads.reserve(config.consumer_threads);

    for(int i=0;i<config.consumer_threads;i++)
    {
        Consumer consumer(in_buf,config,out_buf);
        threads.push_back(std::thread(&Consumer::run,consumer));
    }
    for(std::thread & t1 : threads){
        t1.join();
    }
    threads.clear();
}

void ConsumerPool::stop(){}
