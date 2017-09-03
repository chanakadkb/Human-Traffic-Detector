#include "opencv2/highgui/highgui.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <structures.h>
#include <string>

class Operator{
    public:
        int operate(cv::Mat frame);
        Operator(OperateConf config);
    private:
        OperateConf config;
        cv::CascadeClassifier face_cascade;
        cv::CascadeClassifier eyes_cascade;
        cv::CascadeClassifier full_body;
        int people_casecade_detect(cv::Mat cal);
        int people_hog_detect(cv::Mat frame);
        std::vector<cv::Rect> filter(std::vector<cv::Rect> rects);
        static bool myfunction (cv::Rect i,cv::Rect j);
};
