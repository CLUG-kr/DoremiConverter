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
	vector<Rect> letterBBoxes1;
	PreCharRecognize(Mat img, vector<int> staff_y);
	void CropTop();
	void CropLine(int order);
	void CropAllLine();
	void detectLetters(Mat img);
	void saveAllLetters(Mat img, string title);
	void saveEachLetters(Mat img, string title);
	int show(Mat img, string title);

};