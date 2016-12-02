#include "segmentimage.h"
#include <string>
#include <iostream>
#include <QString>

SegmentImage::SegmentImage(int i):index(i)
{
    imgOriginal = cv::imread("/Users/bahermursi/Assignment3Vision/Outdoors/Image" + QString::number(index + 1).toStdString() + ".jpg", 1 );
    imshow("original",imgOriginal);
}
void SegmentImage::run(){

    Mat imgHSV;
    cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV
    Mat imgThresholded(imgOriginal.rows,imgOriginal.cols,COLOR_BGR2HSV);
    for(int i = 0; i < 2; ++i){
        inRange(imgHSV, Scalar(ranges[i][index].lowH,ranges[i][index].lowS,ranges[i][index].lowV),
                Scalar(ranges[i][index].highH, ranges[i][index].highS, ranges[i][index].highV), imgThresholded);
        //morphological opening (remove small objects from the foreground)
        erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
        dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(4, 4)) );

        //morphological closing (fill small holes in the foreground)
        dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)) );
        erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(1, 1)) );
        Mat temp = imgThresholded.clone();
        extractToBinary(TYPE(i),temp);
    }
}

void SegmentImage::extractToBinary(TYPE type, Mat& src){
    int largest_area=0;
    int largest_contour_index=0;
    Mat thr = src.clone();
    Mat dst(src.rows,src.cols,CV_8UC1,Scalar::all(0));
    threshold(src, src,0, 255,THRESH_BINARY); //Threshold the gray

    std::vector<std::vector<Point>> contours; // Vector for storing contour
    std::vector<Vec4i> hierarchy;

    findContours( thr, contours, hierarchy,CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );

    for( int i = 0; i< contours.size(); i++ )
    {
        double a=contourArea( contours[i],false);
        if(a>largest_area){
            largest_area=a;
            largest_contour_index=i;
        }

    }

    Scalar color( 255,255,255);
    drawContours( dst, contours,largest_contour_index, color, CV_FILLED, 8, hierarchy );
    if(type == ROAD)
        imshow( "ROAD", dst );
    else
        imshow( "RURAL", dst );
}
