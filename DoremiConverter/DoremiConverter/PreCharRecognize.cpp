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
	this->topImg = subImg;
	imwrite("PreCRImg/TopImg.jpg", this->topImg);
	
}

// Crop opearation for each line area
void PreCharRecognize::CropLine(int order) {
	
	int staff_height = this->staff_y[order + 1] - this->staff_y[order];
	int start = 0;
	int end = 0;
	Mat subImg;
	
	// make line's top image
	start = staff_y[order] - staff_height*4/3;
	end = staff_y[order];
	subImg = inputImg(Rect(0, start, inputImg.cols, staff_height));
	
	this->lineTopImg = subImg;

	// make line's bottom image
	start = staff_y[order + 1] + staff_height * 0.5;
	end = start + staff_height*1.4;
	subImg = inputImg(Rect(0, start, inputImg.cols, end - start));
	
	this->lineBottomImg = subImg;

}

// Crop along the line area
void PreCharRecognize::CropAllLine() {
	
	string order;
	string title;

	// make Line Top Image
	for (int i = 0; i < this->staff_y.size(); i += 2) {
		this->CropLine(i);
		order = to_string(i / 2);
		title = "PreCRImg/LineTop";
		title += order;
		title += ".jpg";
		imwrite(title, this->lineTopImg);
		title = "PreCRImg/LineBottom";
		title += order;
		title += ".jpg";
		imwrite(title, this->lineBottomImg);

	}
}

vector<cv::Rect> PreCharRecognize::detectLetters(cv::Mat img)
{
	std::vector<cv::Rect> boundRect;
	cv::Mat img_gray, img_sobel, img_threshold, element;
	cvtColor(img, img_gray, CV_BGR2GRAY);
	cv::Sobel(img_gray, img_sobel, CV_8U, 1, 0, 3, 1, 0, cv::BORDER_DEFAULT);
	cv::threshold(img_sobel, img_threshold, 0, 255, CV_THRESH_OTSU + CV_THRESH_BINARY);
	element = getStructuringElement(cv::MORPH_RECT, cv::Size(17, 3));
	cv::morphologyEx(img_threshold, img_threshold, CV_MOP_CLOSE, element); //Does the trick
	std::vector< std::vector< cv::Point> > contours;
	cv::findContours(img_threshold, contours, 0, 1);
	std::vector<std::vector<cv::Point> > contours_poly(contours.size());
	for (int i = 0; i < contours.size(); i++)
		if (contours[i].size()>100)
		{
			cv::approxPolyDP(cv::Mat(contours[i]), contours_poly[i], 3, true);
			cv::Rect appRect(boundingRect(cv::Mat(contours_poly[i])));
			if (appRect.width>appRect.height)
				boundRect.push_back(appRect);
		}
	return boundRect;
}