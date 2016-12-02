#ifndef SEGMENTIMAGE_H
#define SEGMENTIMAGE_H
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;

class SegmentImage
{
public:
    SegmentImage(int);
    void run();

private:
    enum TYPE{RURAL,ROAD};
    void extractToBinary(TYPE,Mat&);
    struct hsvRange{
        int lowH; int highH;
        int lowS; int highS;
        int lowV; int highV;

        hsvRange(int lh,int hh, int ls, int hs, int lv,int hv): lowH(lh), highH(hh), lowS(ls),highS(hs),lowV(lv), highV(hv){}
    };
    hsvRange ruralRanges[4]{
        hsvRange(18,170,0,255,0,142),
                hsvRange(22,104,0,255,0,255),
                hsvRange(18,122,0,255,14,241),
                 hsvRange(23,179,0,255,0,160),



    };
    hsvRange roadRanges[4]{
        hsvRange(0,23,36,141,0,255),
                hsvRange(0,179,0,93,65,255),
                hsvRange(0,179,0,102,31,232),
                hsvRange(0,32,22,202,74,255),

    };
    std::vector<hsvRange*> ranges{ruralRanges,roadRanges};
    int index;
    Mat imgOriginal;

};


#endif // SEGMENTIMAGE_H
