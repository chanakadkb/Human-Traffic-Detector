#pragma once

#include <fstream>
#include <queue>
#include <structures.h>

class Writer{
    public:
        Writer(char const* filename);
        void writeFile(std::queue<cam_feed, std::deque<cam_feed, std::allocator<cam_feed>>> out_queue);
        void writeFile(std::queue<output, std::deque<output, std::allocator<output> > > out_queue);
        void close();
    private:
        std::fstream ofs;
        const char* filename;
};
