#include <consumer.h>

Consumer::Consumer(Buffer<cam_feed>* in_buf,CONFIG config,Buffer<output>* out_buf){
    this->out_buf=out_buf;
    this->config=config;
    this->in_buf=in_buf;
    this->interval=this->config.consumer_interval;
}

void Consumer::run(){
    Operator operat(config.operate_conf);
    int null_rtn=0;
    while(true){
        Poco::Thread::sleep(interval);
        cam_feed feed=in_buf->consume();
        if(feed.id.length()==0){
            null_rtn++;
            if(null_rtn>10){
                Poco::Thread::sleep(interval*10);
            }
            continue;
        }else{null_rtn=0;}
        output op;
        op.id=feed.id;
        op.time=feed.time;
        op.count=operat.operate(feed.frame);
        out_buf->produce(op);
    }
}
