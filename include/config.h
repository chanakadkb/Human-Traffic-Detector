
#include <tinyxml.h>
#include <structures.h>

#ifndef CONFIGURATION_H
#define CONFIGURATION_H


class Configurations{
    private:
        const char* config_file="config.xml";
        CONFIG config;
    public:
        void load();
        CONFIG get();
};

#endif
