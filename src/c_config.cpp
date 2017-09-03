#include <config.h>
#include "easylogging++.h"

void Configurations::load(){
    TiXmlDocument doc(config_file);
    TiXmlHandle docHandle( &doc );
	bool loadOkay = doc.LoadFile();
	if (loadOkay)
	{
        LOG(DEBUG) << "config file loaded successfully";
        TiXmlNode* parent = docHandle.FirstChild("configurations").ToNode();
        switch (1)
        {
        case 1:
                //get title and set value
            {
                TiXmlText* text=parent->FirstChild("name")->FirstChild()->ToText();
                if(text){
                    config.appname=std::string(text->Value());
                    LOG(DEBUG) << "appname : "<< text->Value();
                }
            }
        case 2:
            {
                TiXmlText* text=parent->FirstChild("producer_interval")->FirstChild()->ToText();
                if(text){
                    config.producer_interval=atoi(text->Value());
                    LOG(DEBUG) << "producer_interval : "<< text->Value();
                }
            }
        case 3:
            {
                TiXmlText* text=parent->FirstChild("consumer_interval")->FirstChild()->ToText();
                if(text){
                    config.consumer_interval=atoi(text->Value());
                    LOG(DEBUG) << "consumer_interval : "<< text->Value();
                }
            }
        case 4:
            {
                TiXmlText* text=parent->FirstChild("output_buf")->FirstChild()->ToText();
                if(text){
                    config.output_buf=atoi(text->Value());
                    LOG(DEBUG) << "output_buf : "<< text->Value();
                }
            }
        case 5:
            {
                TiXmlText* text=parent->FirstChild("input_buf")->FirstChild()->ToText();
                if(text){
                    config.input_buf=atoi(text->Value());
                    LOG(DEBUG) << "input_buf : "<< text->Value();
                }
            }
        case 6:
            {
                TiXmlText* text=parent->FirstChild("output_file")->FirstChild()->ToText();
                if(text){
                    config.output_file=text->Value();
                    LOG(DEBUG) << "output_file : "<< text->Value();
                }
            }
        case 7:
            {
                TiXmlText* text=parent->FirstChild("consumer_threads")->FirstChild()->ToText();
                if(text){
                    config.consumer_threads=atoi(text->Value());
                    LOG(DEBUG) << "consumer_threads : "<< text->Value();
                }
            }
        case 8:
            {
                TiXmlNode* child=parent->FirstChild("cameras")->FirstChild();
                for(child; child; child=child->NextSibling()){
                    Camera cam;
                    cam.type=atoi(child->ToElement()->Attribute("type"));
                    cam.address=std::string(child->ToElement()->Attribute("address"));
                    cam.id=std::string(child->ToElement()->Attribute("id"));
                    //cam.port=atoi(child->ToElement()->Attribute("port"));
                    config.cameras.push_back(cam);
                    LOG(DEBUG) << "cam : "<< config.cameras.back().id;
                }
            }
        case 9:
            {
                TiXmlNode* op_parent = parent->FirstChild("operate_conf");
                OperateConf op_conf;
                switch (0)
                {
                    case 0:
                        {
                            TiXmlElement* child=op_parent->FirstChildElement("image_size");
                            POINT image_size;
                            image_size.x=atoi(child->Attribute("x"));
                            image_size.y=atoi(child->Attribute("y"));
                            op_conf.image_size=image_size;
                            LOG(DEBUG) << "image_size : "<<image_size.x<<"|"<<image_size.y ;
                        }
                    case 1:
                        {
                            TiXmlText* text=op_parent->FirstChild("algorithm")->FirstChild()->ToText();
                            if(text){
                                op_conf.algorithm=atoi(text->Value());
                                LOG(DEBUG) << "algorithm : "<< text->Value();
                            }
                        }
                    case 2:
                        {
                            TiXmlText* text=op_parent->FirstChild("img_show")->FirstChild()->ToText();
                            if(text){
                                op_conf.img_show=atoi(text->Value());
                                LOG(DEBUG) << "img_show : "<< text->Value();
                            }
                        }
                    case 3:
                        {
                            TiXmlText* text=op_parent->FirstChild("filter_threshol")->FirstChild()->ToText();
                            if(text){
                                op_conf.filter_threshol=atof(text->Value());
                                LOG(DEBUG) << "filter_threshol : "<< text->Value();
                            }
                        }
                    case 4:
                        {
                            TiXmlNode* hog_parent = op_parent->FirstChild("hogconf");
                            Hogconf hogc;
                            switch (0)
                            {
                            case 0:
                                {
                                    TiXmlText* text=hog_parent->FirstChild("hit_threshold")->FirstChild()->ToText();
                                    if(text){
                                        hogc.hit_threshold=atof(text->Value());
                                        LOG(DEBUG) << "hit_threshold : "<< text->Value();
                                    }
                                }
                            case 1:
                                {
                                    TiXmlText* text=hog_parent->FirstChild("scale")->FirstChild()->ToText();
                                    if(text){
                                        hogc.scale=atof(text->Value());
                                        LOG(DEBUG) << "scale : "<< text->Value();
                                    }
                                }
                            case 2:
                                {
                                    TiXmlText* text=hog_parent->FirstChild("final_threshold")->FirstChild()->ToText();
                                    if(text){
                                        hogc.final_threshold=atof(text->Value());
                                        LOG(DEBUG) << "final_threshold : "<< text->Value();
                                    }
                                }
                            case 3:
                                {
                                    TiXmlElement* child=hog_parent->FirstChildElement("win_stride");
                                    POINT win_stride;
                                    win_stride.x=atoi(child->Attribute("x"));
                                    win_stride.y=atoi(child->Attribute("y"));
                                    hogc.win_stride=win_stride;
                                    LOG(DEBUG) << "win_stride : "<<win_stride.x<<"|"<<win_stride.y ;
                                }
                            case 4:
                                {
                                    TiXmlElement* child=hog_parent->FirstChildElement("padding");
                                    POINT padding;
                                    padding.x=atoi(child->Attribute("x"));
                                    padding.y=atoi(child->Attribute("y"));
                                    hogc.padding=padding;
                                    LOG(DEBUG) << "padding : "<<padding.x<<"|"<<padding.y ;
                                }
                            default:
                                op_conf.hogconf=hogc;
                                break;
                            }
                        }
                    case 5:
                        {
                            TiXmlNode* cas_parent = op_parent->FirstChild("casecadeconf");
                            Casecade casc;
                            switch (0)
                            {
                            case 0:
                                {
                                    TiXmlText* text=cas_parent->FirstChild("scale_factor")->FirstChild()->ToText();
                                    if(text){
                                        casc.scale_factor=atof(text->Value());
                                        LOG(DEBUG) << "scale_factor : "<< text->Value();
                                    }
                                }
                            case 1:
                                {
                                    TiXmlText* text=cas_parent->FirstChild("min_neighbors")->FirstChild()->ToText();
                                    if(text){
                                        casc.min_neighbors=atoi(text->Value());
                                        LOG(DEBUG) << "min_neighbors : "<< text->Value();
                                    }
                                }
                            case 2:
                                {
                                    TiXmlText* text=cas_parent->FirstChild("flags")->FirstChild()->ToText();
                                    if(text){
                                        casc.flags=atoi(text->Value());
                                        LOG(DEBUG) << "flags : "<< text->Value();
                                    }
                                }
                            case 3:
                                {
                                    TiXmlText* text=cas_parent->FirstChild("casecade_file")->FirstChild()->ToText();
                                    if(text){
                                        casc.casecade_file=std::string(text->Value());
                                        LOG(DEBUG) << "casecade_file : "<< text->Value();
                                    }
                                }
                            case 4:
                                {
                                    TiXmlElement* child=cas_parent->FirstChildElement("minSize");
                                    POINT minSize;
                                    minSize.x=atoi(child->Attribute("x"));
                                    minSize.y=atoi(child->Attribute("y"));
                                    casc.minSize=minSize;
                                    LOG(DEBUG) << "minSize : "<<minSize.x<<"|"<<minSize.y ;
                                }
                            case 5:
                                {
                                    TiXmlElement* child=cas_parent->FirstChildElement("maxSize");
                                    POINT maxSize;
                                    maxSize.x=atoi(child->Attribute("x"));
                                    maxSize.y=atoi(child->Attribute("y"));
                                    casc.maxSize=maxSize;
                                    LOG(DEBUG) << "maxSize : "<<maxSize.x<<"|"<<maxSize.y ;
                                }
                            default:
                                op_conf.casecadeconf=casc;
                                break;
                            }
                        }
                    default:
                        config.operate_conf=op_conf;
                        break;
                }
            }
        default:
            {
                LOG(DEBUG) << "config file reading finished";
                break;
            }
        }
	}
	else
	{
		LOG(ERROR)<<("Failed to load file %s and continue with default configurations", config_file);
	}
}

CONFIG Configurations::get(){
    return config;
}
