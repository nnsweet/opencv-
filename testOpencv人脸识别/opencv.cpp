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
cv::Mat g_src = imread("C:/Users/Administrator/Pictures/Saved Pictures/����.png");

void facePictureDetecion();
void faceVideoDetection();

int main(void)
{
    //facePictureDetecion();//ͼ������ʶ��
    faceVideoDetection();//��Ƶ����ʶ��
    return 0;
}

void facePictureDetecion()
{
    namedWindow("�������", WINDOW_NORMAL);
    cv::Mat src = g_src;
    cv::Mat dst=src.clone();
    imshow("1", dst);
    vector<Rect> faces;
    CascadeClassifier cascade;//���������
    cascade.load(xmlPath);
   // if (!cascade.load(xmlPath)) {
   //     cout << "xml�ļ�����ʧ��" << endl;
   // }
    cascade.detectMultiScale(src, faces, 1.1, 3, 0, Size(30, 30));
    cout << "��⵽��������:" << faces.size() << endl;
    for (size_t t = 0; t < faces.size(); t++) {
        rectangle(dst, faces[t], Scalar(0, 255, 0), 2, 8);//���̿�
    }
    imshow("�������", dst);
    waitKey(0);
}

void faceVideoDetection()
{
    namedWindow("�������", WINDOW_NORMAL);
    vector<Rect> faces;
    VideoCapture capture(0);
    CascadeClassifier cascade;//���������
    cascade.load(xmlPath);
    if (cascade.empty()) {
        cout << "xml�ļ�����ʧ��" << endl;
    }

    while (true) {
        Mat frame;
        Mat dst;
        capture >> frame;
        flip(frame, dst, 1);//������y��ת
        cascade.detectMultiScale(dst, faces, 1.1, 3, 0, Size(30, 30));
        for (size_t t = 0; t < faces.size(); t++) {
            rectangle(dst, faces[t], Scalar(0, 255, 0), 2, 8);//���̿�
        }
        imshow("�������", dst);
        waitKey(10);//��ʱ10ms
    }
}
