#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

class MusicInformExtract {
private:
public:
	Mat components;
	MusicInformExtract();
	void ComponentDetect(Mat img);

};