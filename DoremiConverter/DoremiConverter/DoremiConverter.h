#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

class DoremiConverter {
private:
	Mat inputImg;
	Mat makeHistogram(int FLAG);
	void binarization(Mat img);
public:
	DoremiConverter(string imgName);
	int show();
	int getNote();
};