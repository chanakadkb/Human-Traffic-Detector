#include <iostream>
#include <ctime>
#include "opencv2/core/core.hpp"
#include "config.h"
#include <queue>
#include <thread>
#include <mutex>
#include <writer.h>
#include <structures.h>

#ifndef BUFFER_H
#define BUFFER_H


template <class T> class Buffer{
    private:
        std::queue<T> buffer;
        int max_size=20;
        std::mutex locker;
        Writer* writer;
        bool enable_writer=false;

    public:
        Buffer(int size);
        void produce(T feed);
        T consume();
        std::queue<T> consumeAll();
        void addWriter(Writer* writer);
};
#endif
