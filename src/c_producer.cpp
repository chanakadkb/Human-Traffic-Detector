#include<producer.h>

/**
    start VideoCapture from given address
    if it is opened and campture returned true set isconnected true;

*/
Producer::Producer(Camera cam,CONFIG config,Buffer<cam_feed>* buf){
    buffer=buf;
    this->config=config;
    this->id=cam.id;
    this->cam=cam;
}


/**
    __thread function__
    read video frame;
    get time
    add to buffer
*/
void Producer::run(){
    cv::VideoCapture* capture;
    if(cam.type==0){
        capture=new cv::VideoCapture(stoi(cam.address));
        if(capture->isOpened()){
            isconnected=true;
        }
    }else{
        capture=new cv::VideoCapture();
        if(capture->open(cam.address)){
            isconnected=true;
        }
    }
    cv::Mat temp;
    while(capture->read(temp)){
        cam_feed op;
        op.id=id;
        op.time = time(0);
        op.frame=temp;
        buffer->produce(op);
        usleep(config.producer_interval);
    }
    isconnected=false;
}

bool Producer::connected(){
    return isconnected;
}
