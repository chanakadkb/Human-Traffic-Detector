#include "operate.h"
#include <iostream>

int Operator::operate(cv::Mat frame){
    cv::resize(frame, frame, cv::Size(config.image_size.x, config.image_size.y));
    return (config.algorithm==0)?people_casecade_detect(frame):people_hog_detect(frame);
}

Operator::Operator(OperateConf config){
    this->config=config;
    if(config.algorithm==0){
        if( !full_body.load(config.casecadeconf.casecade_file) ){
            std::cout<<"ERROR : casecade file openning failed"<<std::endl;
     	}
    }
}

int Operator::people_casecade_detect(cv::Mat cal){
    std::vector<cv::Rect> faces;
	cv::Mat frame_gray;
    Casecade casecade=config.casecadeconf;
	cv::cvtColor( cal, frame_gray, CV_BGR2GRAY );
	cv::equalizeHist( frame_gray, frame_gray );
    full_body.detectMultiScale( frame_gray, faces,casecade.scale_factor, casecade.min_neighbors, casecade.flags, cv::Size(casecade.minSize.x, casecade.minSize.y),cv::Size(casecade.maxSize.x, casecade.maxSize.y));
    faces = filter(faces);
	for( size_t i = 0; i < faces.size(); i++ )
	{
        cv::rectangle(frame_gray, faces[i].tl(),faces[i].br(),cv::Scalar( 255, 0, 255 ),2,8,0);
	}
    if(config.img_show==1){
        cv::imshow("debug",frame_gray);
        cv::waitKey(30);
    }
    return faces.size();
}

int Operator::people_hog_detect(cv::Mat frame) {
    std::vector<cv::Rect> people;
	cv::Mat frame_gray;
    Hogconf hogconf=config.hogconf;
	cv::cvtColor( frame, frame_gray, CV_BGR2GRAY );
	cv::equalizeHist( frame_gray, frame_gray );

    cv::HOGDescriptor hog=cv::HOGDescriptor();
    hog.setSVMDetector(cv::HOGDescriptor::getDefaultPeopleDetector());
    hog.detectMultiScale(frame_gray,people,hogconf.hit_threshold,cv::Size(hogconf.win_stride.x,hogconf.win_stride.y),cv::Size(hogconf.padding.x,hogconf.padding.y),hogconf.scale,hogconf.final_threshold);

    people = filter(people);
    for( size_t i = 0; i < people.size(); i++ )
	{
        cv::rectangle(frame_gray, people[i].tl(),people[i].br(),cv::Scalar( 255, 0, 255 ),2,8,0);
    }
    if(config.img_show==1){
        cv::imshow("debug",frame_gray);
        cv::waitKey(30);
    }
    return people.size();

}

std::vector<cv::Rect> Operator::filter(std::vector<cv::Rect> rects){
    std::sort (rects.begin(), rects.end(), myfunction);
    std::vector<cv::Rect> temp;
    bool coll=true;
    for(int i=0;i<rects.size();i++){
        coll=true;
        for(int j=i+1;j<rects.size();j++){
            if((rects[i]&rects[j]).area()>=(rects[i].area()*config.filter_threshol)){
                coll=false;
                break;
            }
        }
        if(coll){
            temp.push_back(rects[i]);
        }
    }
    return temp;
}

bool Operator::myfunction (cv::Rect i,cv::Rect j) { return (i.area()<j.area()); }
