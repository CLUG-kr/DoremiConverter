#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>

#define STAFFHEIGHT (3)
#define STAFFSPACE (5)

using namespace cv;
using namespace std;

class RemoveStaff {
private:
public:
	Mat detectImg;
	Mat originImg;
	Mat result;
	vector<int> temp_staff_y;
	vector<int> staff_y;
	RemoveStaff();
	void DetectLines(Mat img);
	void GetStaffLocation();
	void Remove(Mat img);
	int show(Mat img, string title);

};

// Image preprocessing to Remove Staff 
//PreProcessing pre("rotated_sheet_original.jpg");
//pre.binarization();
//pre.edgeDetect();
//pre.rotateImage(pre.calculateDegree(pre.straightExtract()));
//pre.inputImg = pre.straightendImg.clone();
//pre.binarization();
//pre.stafflineDetect();