#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

typedef struct character {

	// int order;
	char * code;
	char * lyrics;

}
character;

class PreCharRecognize {

private:

public:

	Mat inputImg;
	Mat topImg;
	Mat lineTopImg;
	Mat lineBottomImg;
	vector<int> staff_y;
	vector<character> charResult;
	PreCharRecognize(Mat img, vector<int> staff_y);
	void CropTop();
	void CropLine(int order);
	void CropAllLine();
	vector<cv::Rect> detectLetters(cv::Mat img);
	int show(Mat img, string title);

};