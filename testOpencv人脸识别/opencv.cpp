#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;
using namespace cv;

string xmlPath = "E:/opencv/build/etc/haarcascades/haarcascade_frontalface_default.xml";
cv::Mat g_src = imread("C:/Users/Administrator/Pictures/Saved Pictures/人脸.png");

void facePictureDetecion();
void faceVideoDetection();

int main(void)
{
    //facePictureDetecion();//图像人脸识别
    faceVideoDetection();//视频人脸识别
    return 0;
}

void facePictureDetecion()
{
    namedWindow("人脸检测", WINDOW_NORMAL);
    cv::Mat src = g_src;
    cv::Mat dst=src.clone();
    imshow("1", dst);
    vector<Rect> faces;
    CascadeClassifier cascade;//定义分类器
    cascade.load(xmlPath);
   // if (!cascade.load(xmlPath)) {
   //     cout << "xml文件加载失败" << endl;
   // }
    cascade.detectMultiScale(src, faces, 1.1, 3, 0, Size(30, 30));
    cout << "检测到人脸数量:" << faces.size() << endl;
    for (size_t t = 0; t < faces.size(); t++) {
        rectangle(dst, faces[t], Scalar(0, 255, 0), 2, 8);//画绿框
    }
    imshow("人脸检测", dst);
    waitKey(0);
}

void faceVideoDetection()
{
    namedWindow("人脸检测", WINDOW_NORMAL);
    vector<Rect> faces;
    VideoCapture capture(0);
    CascadeClassifier cascade;//定义分类器
    cascade.load(xmlPath);
    if (cascade.empty()) {
        cout << "xml文件加载失败" << endl;
    }

    while (true) {
        Mat frame;
        Mat dst;
        capture >> frame;
        flip(frame, dst, 1);//镜像沿y翻转
        cascade.detectMultiScale(dst, faces, 1.1, 3, 0, Size(30, 30));
        for (size_t t = 0; t < faces.size(); t++) {
            rectangle(dst, faces[t], Scalar(0, 255, 0), 2, 8);//画绿框
        }
        imshow("人脸检测", dst);
        waitKey(10);//延时10ms
    }
}
