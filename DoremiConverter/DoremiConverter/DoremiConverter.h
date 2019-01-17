#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

class DoremiConverter {
private:
	Mat inputImg;
	void binarization(Mat img);
public:
	DoremiConverter(string imgName);
	int show();
};