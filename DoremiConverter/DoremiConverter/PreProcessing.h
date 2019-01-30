#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

class PreProcessing {
private:
public:
	Mat inputImg;
	Mat binaryImg;
	Mat edgeImg;
	Mat straightImg;
	Mat straightendImg;
	Mat staffLine;
	Mat objects;
	PreProcessing(string imgName);
	int show(Mat img, string title);
	void binarization();
	void edgeDetect();
	vector<Vec4i> straightExtract();
	double calculateDegree(vector<Vec4i> lines);
	void rotateImage(double degree);
	void stafflineDetect();
	void objectsDetect();
};
