#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

class DoremiConverter {
private:
public:
	Mat inputImg;
	Mat binaryImg;
	Mat edgeImg;
	Mat straightImg;
	Mat straightendImg;
	DoremiConverter(string imgName);
	void binarization(Mat img);
	int show(Mat img, string title);
	void edgeDetect();
	void straightDetect();
	double calculateDegree(vector<Vec4i> lines);
	void rotateImage(double degree);
};