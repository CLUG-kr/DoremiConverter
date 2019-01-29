#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

class DoremiConverter {
private:
	Mat inputImg;
	void binarization();

public:
	DoremiConverter(string imgName);
	int show();
	int show(Mat img);
	vector<vector<int>> encodeRLE();
	Mat decodeRLE(vector<vector<int>> RLE);
};