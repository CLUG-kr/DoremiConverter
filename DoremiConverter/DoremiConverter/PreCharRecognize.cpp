#include "pch.h"
#include "PreCharRecognize.h"

// constructor
PreCharRecognize::PreCharRecognize(Mat img, vector<int> staff_y) {
	this->inputImg = img;
	this->staff_y = staff_y;
}


int PreCharRecognize::show(Mat img, string title) {
	// cout << "OpenCV Version : " << CV_VERSION << endl;
	namedWindow(title, CV_WINDOW_AUTOSIZE);

	if (img.empty())
	{
		cout << "There's no sheet file!" << endl;
		return -1;
	}

	imshow(title, img);
	//imwrite("RemoveStaff.jpg", img);
}

// make top Image of Sheet
// There are Title, Composer, ... etc
void PreCharRecognize::CropTop() {
	
	int staff_height = this->staff_y[1] - this->staff_y[0];
	int topLower_y = this->staff_y[0] - staff_height;
	Mat subImg;
	subImg = inputImg(Rect(0, 0, inputImg.cols, topLower_y));
	topImg = subImg;
	
}