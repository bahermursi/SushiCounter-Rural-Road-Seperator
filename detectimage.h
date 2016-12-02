#ifndef DETECTIMAGE_H
#define DETECTIMAGE_H
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <string>
#include <iostream>
#include <algorithm>


class DetectImage
{
public:
    DetectImage(int);
    void trackHighestPoints();
    void run();
    void showSushishushi();
    int  getSushiCount() const;

private:
    struct MyPoints{
        float maximum;
        cv::Point point;
        MyPoints(float m, int x, int y) : maximum(m),point(x,y){}
    };

    static bool compare(const MyPoints& l,const  MyPoints& r)
    {
        return l.maximum < r.maximum;
    }

    cv::Mat img,result,templ,detectedImage;
    float thresholds [5] = {0.5, 0.62, 0.585, 0.65, 0.55};
    int sushiCount;
    int index;

};

#endif // DETECTIMAGE_H
