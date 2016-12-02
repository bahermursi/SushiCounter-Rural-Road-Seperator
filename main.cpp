#include "mainwindow.h"
#include <QApplication>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;
using namespace std;
int iLowH = 50;
int iHighH = 150;

int iLowS = 0;
int iHighS = 128;

int iLowV = 0;
int iHighV = 128;
//Mat imgOriginal,imgHSV,imgThresholded;
string path1 = "/Users/bahermursi/Desktop/testthis.jpg";
string path2 = "/Users/bahermursi/Desktop/travel.jpg";
void count(){
    int largest_area=0;
    int largest_contour_index=0;
    Mat src = imread(path1); //Load source image
    Mat thr(src.rows,src.cols,CV_8UC1);
    Mat dst(src.rows,src.cols,CV_8UC1,Scalar::all(0));
    cvtColor(src,thr,CV_BGR2GRAY); //Convert to gray
    threshold(thr, thr,25, 255,THRESH_BINARY); //Threshold the gray

    vector<vector<Point>> contours; // Vector for storing contour
    vector<Vec4i> hierarchy;

    findContours( thr, contours, hierarchy,CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE ); // Find the contours in the image

    for( int i = 0; i< contours.size(); i++ ) // iterate through each contour.
    {
        double a=contourArea( contours[i],false);  //  Find the area of contour
        if(a>largest_area){
            largest_area=a;
            largest_contour_index=i;                //Store the index of largest contour
            // bounding_rect=boundingRect(contours[i]); // Find the bounding rectangle for biggest contour
        }

    }

    Scalar color( 255,255,255);
    drawContours( dst, contours,largest_contour_index, color, CV_FILLED, 8, hierarchy ); // Draw the largest contour using previously stored index.
    // rectangle(src, bounding_rect,  Scalar(0,255,0),1, 8,0);
    imshow( "src", src );
    imshow( "largest Contour", dst );
}
Mat equalizeIntensity(const Mat& inputImage)
{
    if(inputImage.channels() >= 3)
    {
        Mat ycrcb;

        cvtColor(inputImage,ycrcb,CV_BGR2YCrCb);

        vector<Mat> channels;
        split(ycrcb,channels);

        equalizeHist(channels[0], channels[0]);

        Mat result;
        merge(channels,ycrcb);

        cvtColor(ycrcb,result,CV_YCrCb2BGR);

        return result;
    }
    return Mat();
}
void MatchingMethod( int, void* )
{
    Mat imgOriginal = cv::imread(path2);
    Mat imgHSV;
    // blur(imgOriginal, imgOriginal, Size(3,3));
    //Canny(imgOriginal,imgOriginal,128,255);
    //imgOriginal = equalizeIntensity(imgOriginal);

    cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV

    Mat imgThresholded;

    inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image

    //morphological opening (remove small objects from the foreground)
    erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
    dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(4, 4)) );

    //morphological closing (fill small holes in the foreground)
    dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)) );
    erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(1, 1)) );

    imshow("Thresholded Image", imgThresholded); //show the thresholded image
    imshow("Original", imgOriginal); //show the original image
}
void tacker(){
    namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"
    //Create trackbars in "Control" window
    createTrackbar("LowH", "Control", &iLowH, 179,MatchingMethod); //Hue (0 - 179)
    createTrackbar("HighH", "Control", &iHighH, 179,MatchingMethod);

    createTrackbar("LowS", "Control", &iLowS, 255,MatchingMethod); //Saturation (0 - 255)
    createTrackbar("HighS", "Control", &iHighS, 255,MatchingMethod);

    createTrackbar("LowV", "Control", &iLowV, 255,MatchingMethod); //Value (0 - 255)
    createTrackbar("HighV", "Control", &iHighV, 255,MatchingMethod);
    MatchingMethod( 0, 0 );
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    //  tacker();
    //    count();
    return a.exec();
}


//using namespace cv;
//using namespace std;
//int main(int argc, char *argv[])
//{
//
//    return a.exec();
//}
