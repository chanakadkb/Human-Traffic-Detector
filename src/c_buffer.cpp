#include <buffer.h>

template <class T>
Buffer<T>::Buffer(int size){
    max_size=size;
}


template <class T>
void Buffer<T>::produce(T feed){
    locker.lock();
    if(buffer.size()<max_size){
        buffer.push(feed);
    }else{
        if(enable_writer){
            writer->writeFile(consumeAll());
            buffer.push(feed);
        }
    }
    locker.unlock();
}

template <class T>
T Buffer<T>::consume(){
    T feed;
    locker.lock();
    if(buffer.empty()){
        locker.unlock();
        return feed;
    }
    feed=buffer.front();
    buffer.pop();
    locker.unlock();
    return feed;
}

template <class T>
std::queue<T> Buffer<T>::consumeAll(){
    std::queue<T> temp;
    if(buffer.empty()){
        return temp;
    }
    std::swap(temp,buffer);
    return temp;
}

template <class T>
void Buffer<T>::addWriter(Writer* writer){
    enable_writer=true;
    this->writer=writer;
}


template class Buffer<cam_feed>;
template class Buffer<output>;
