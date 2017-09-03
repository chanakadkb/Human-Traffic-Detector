#include <producer_pool.h>

ProducerPool::ProducerPool(Buffer<cam_feed>* buf,CONFIG config){
    this->buf=buf;
    this->config=config;
}
/**
    get each camera connection from configurations
    start connection
    if success call its produce method in a thread  and put it into thread pool
    else throw an error saying cam connection faild;

    finnaly join all threads together;
*/
void ProducerPool::run(){
    std::vector<std::thread> threads;
    threads.reserve(config.cameras.size());

    for (const auto &cam : config.cameras)
    {
        Producer producer(cam,config,buf);
        threads.push_back(std::thread(&Producer::run,producer));
    }
    for(std::thread & t1 : threads){
        t1.join();
    }
    threads.clear();
}

/**
    stop all running connections from the pool
*/
void ProducerPool::stop(){

}
