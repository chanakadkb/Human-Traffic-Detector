#pragma once
#include <ctime>
#include "opencv2/core/core.hpp"
#include <string>
#include <vector>


typedef  struct{
    cv::Mat frame;
    time_t time;
    std::string id;
} cam_feed;

typedef struct{
    int count;
    time_t time;
    std::string id;
} output;


typedef struct
{
    std::string address;
    int type=1;   //local=0|remote=1
    std::string id;
} Camera;

typedef struct
{
    int x;
    int y;
} POINT;

/*
casecade
double scale_factor
int min_neighbors
int flags
minSize x,y
maxSize x,y
*/
typedef struct
{
    double scale_factor;
    int min_neighbors;
    int flags;
    POINT minSize;
    POINT maxSize;
    std::string casecade_file;
} Casecade;

/*
hogdetect
double hit_threshold
win_stride x,y
padding x,y
double scale
double final_threshold
*/
typedef struct
{
    double hit_threshold=0;
    POINT win_stride;
    POINT padding;
    double scale=1.1;
    double final_threshold=0;
}Hogconf;
/*
image_size width, hieght
algorithm int 0=casecade | 1= hog detection
*/
//double filter_threshol 0.8

typedef struct
{
    POINT image_size;
    int algorithm =0; //0=casecade | 1= hog detection
    double filter_threshol= 0.8;
    Hogconf hogconf;
    Casecade casecadeconf;
    int img_show=1;
}OperateConf;

typedef struct{
    std::string appname;
    std::vector<Camera> cameras;
    int producer_interval;
    int consumer_interval;
    int output_buf;
    int input_buf;
    const char * output_file;
    int consumer_threads;
    OperateConf operate_conf;
} CONFIG;
