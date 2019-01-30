#include "pch.h"
#include "MusicInformExtract.h"

MusicInformExtract::MusicInformExtract() {

}

void MusicInformExtract::ComponentDetect(Mat binImg) {
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	this->components = binImg.clone();

	// find contours
	findContours(binImg, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

	vector<vector<Point>> contours_poly(contours.size());
	vector<Rect> boundRect(contours.size());

	for (int i = 0; i < contours.size(); i++) {
		/* Contour Approximation
		   도형 외곽선을 더 적은 꼭지점수를 갖도록 바꿀때 ex) 찢겨진 사각형 복원
		approxPolyDP(Mat(contours[i]), contours_poly[i], 0, true);
		if (fabs(contourArea(Mat(contours_poly[i])) > 10)) {
			boundRect[i] = boundingRect(Mat(contours_poly[i]));
		}
		*/
		if (fabs(contourArea(Mat(contours[i])) > 5)) {
			boundRect[i] = boundingRect(Mat(contours[i]));
		}
	}
	Mat contourImg = Mat(binImg.rows, binImg.cols, CV_8U);
	Mat rectImg = Mat(binImg.rows, binImg.cols, CV_8U);
	//Scalar color(0, 0, 0);
	Scalar color(255, 255, 255);
	for (int i = 0; i < contours.size(); i++) {
		//drawContours(this->components, contours, i, color, 1, 8, vector<Vec4i>(), 0, Point());
		//rectangle(this->components, boundRect[i].tl(), boundRect[i].br(), color, 1);
		drawContours(contourImg, contours, i, color, 1, 8, vector<Vec4i>(), 0, Point());
		rectangle(rectImg, boundRect[i].tl(), boundRect[i].br(), color, 1);
	}	
	namedWindow("contours", CV_WINDOW_AUTOSIZE);
	imshow("contours", contourImg);

	namedWindow("bounding box", CV_WINDOW_AUTOSIZE);
	imshow("bounding box", rectImg);

}