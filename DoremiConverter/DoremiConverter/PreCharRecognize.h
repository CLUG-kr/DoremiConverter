#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

class PreCharRecognize {

private:

public:

	Mat inputImg;
	Mat topImg;
	Mat lineImg;
	vector<int> staff_y;
	PreCharRecognize(Mat img, vector<int> staff_y);
	void CropTop();
	void CropLine();
	int show(Mat img, string title);

};