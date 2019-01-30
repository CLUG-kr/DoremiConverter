#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

class MusicInformExtract {
private:
public:
	Mat components;
	vector<Rect> objectRects;
	MusicInformExtract();
	void componentDetect(Mat img);
	//void histogram(Mat img);
	struct byX {
		bool operator () (const Rect & a, const Rect & b) {
			return a.x < b.x;
		}
	};
};
//
//bool operator < (const Rect &a, const Rect &b) {
//	return (a.x < b.x);
//}