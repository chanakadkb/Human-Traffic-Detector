#include <writer.h>

Writer::Writer(char const* filename){

    std::string ff(filename);
    ofs.open(ff, std::fstream::out | std::fstream::app);
    this->filename=filename;
}

void Writer::writeFile(std::queue<cam_feed, std::deque<cam_feed, std::allocator<cam_feed> > > out_queue){}

void Writer::writeFile(std::queue<output, std::deque<output, std::allocator<output>>> out_queue){
    if(!ofs.is_open()){
        ofs.open(filename, std::ofstream::out | std::ofstream::app);
    }
    if(out_queue.empty()){return;}
    while ((!out_queue.empty()) && ofs.is_open())
    {
        output q_element = out_queue.front();
        out_queue.pop();
        ofs<<q_element.id<<","<<q_element.time<<","<<q_element.count<<"\n";
    }
    ofs.flush();
}

void Writer::close(){
    if(ofs.is_open()){
        ofs.close();
    }
}
