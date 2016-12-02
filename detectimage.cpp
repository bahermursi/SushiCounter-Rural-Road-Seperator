#include "detectimage.h"
#include "QMessageBox"
#include <cmath>
using namespace  cv;
DetectImage::DetectImage(int i):index(i)
{
    img = cv::imread("/Users/bahermursi/Assignment3Vision/Sushi/Image" + QString::number(index + 1).toStdString() + ".jpg", 1 );
    img.copyTo(detectedImage);
    templ = cv::imread("/Users/bahermursi/Assignment3Vision/Sushi/templ" + QString::number(index + 1).toStdString() + ".jpg", 1 );
}

void DetectImage::run(){
    trackHighestPoints();
    imshow("Result image", detectedImage);
    showSushishushi();
}

void DetectImage::trackHighestPoints(){
    std::vector<MyPoints> localMaxima;
    std::vector<cv::Point> peaks;
    cv::matchTemplate( img, templ, result, CV_TM_CCOEFF_NORMED);
    cv::normalize(result, result, 0.0, 1.0, NORM_MINMAX, -1, Mat());

    for (int i = 0; i < result.rows; i += templ.rows) {
        for (int j = 0; j < result.cols; j += templ.cols) {
            float maximum(0.0);
            int row, col;
            for (int rOffset = 0; rOffset < templ.rows; ++rOffset) {
                if (i + rOffset >= result.rows) break;
                for (int cOffset = 0; cOffset < templ.cols; ++cOffset) {
                    if (j + cOffset >= result.cols)  break;
                    if (result.at<float>(i + rOffset, j + cOffset) > maximum) {
                        maximum = result.at<float>(i + rOffset, j + cOffset);
                        row = i + rOffset;
                        col = j + cOffset;
                    }
                }
            }
            if (maximum > thresholds[index])
                    localMaxima.push_back(MyPoints(maximum,col,row));
        }
    }
    sort(localMaxima.begin(),localMaxima.end(),compare);
    for (MyPoints mp : localMaxima) {
        bool closePoints = false;
        if(!closePoints){
            for (Point pt : peaks) {
                if (sqrt(pow(mp.point.x - pt.x, 2) + pow(mp.point.y - pt.y, 2)) < min(templ.rows, templ.cols) / 1.5)
                    closePoints = true;
            }
        }
        if (!closePoints)
            peaks.push_back(mp.point);
    }

    sushiCount = peaks.size();
    for (cv::Point peak : peaks)
        cv::rectangle(detectedImage, peak, Point(peak.x + templ.cols, peak.y + templ.rows), Scalar(0, 0, 0), 2);
}

int DetectImage::getSushiCount() const{
    return sushiCount;
}

void  DetectImage::showSushishushi(){
    QMessageBox messageBox;
    messageBox.information(0,"","Count of detected sushi pieces: " + QString::number(getSushiCount()));
    messageBox.setFixedSize(500,900);
}
