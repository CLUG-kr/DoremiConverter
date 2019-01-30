#include "pch.h"
#include "MusicInformExtract.h"

MusicInformExtract::MusicInformExtract() {

}



void MusicInformExtract::componentDetect(Mat binImg) {
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	this->components = binImg.clone();

	// find contours
	findContours(binImg, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

	vector<vector<Point>> contours_poly(contours.size());
	vector<Rect> boundRect(contours.size());

	for (int i = 0; i < contours.size(); i++) {
		/*Contour Approximation
		   도형 외곽선을 더 적은 꼭지점수를 갖도록 바꿀때 ex) 찢겨진 사각형 복원
		approxPolyDP(Mat(contours[i]), contours_poly[i], 0, true);
		if (fabs(contourArea(Mat(contours_poly[i])) > 10)) {
			boundRect[i] = boundingRect(Mat(contours_poly[i]));
		}
		*/
		// cout << contourArea(Mat(contours[i])) << endl;
		if (fabs(contourArea(Mat(contours[i])) > 100)) {
			boundRect[i] = boundingRect(Mat(contours[i]));
			//Mat object = binImg(boundRect[i]);
			//Histogram(object);
			//namedWindow("object" + to_string(i), CV_WINDOW_AUTOSIZE);
			//imshow("object" + to_string(i), object);
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

	this->objectRects = boundRect;
}

/*
// Draw histogram of binary image  *strange result*
void MusicInformExtract::histogram(Mat img) {
	
	int histSize = 256;
	
	float range[] = { 0, 256 };
	const float* histRange = { range };

	Mat hist;
	calcHist(&img, 1, 0, Mat(), hist, 1, &histSize, &histRange);
	
	int hist_w = 512, hist_h = 400;
	int bin_w = cvRound((double)hist_w / histSize);

	Mat histImage(hist_h, hist_w, CV_8UC1, Scalar(0, 0, 0));
	normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	
	for (int i = 1; i < histSize; i++)
	{
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(hist.at<float>(i - 1))),
			Point(bin_w*(i), hist_h - cvRound(hist.at<float>(i))),
			Scalar(255, 255, 255), 1);;
	}
	namedWindow("object", CV_WINDOW_AUTOSIZE);
	imshow("object", img);

	namedWindow("histogram", CV_WINDOW_AUTOSIZE);
	imshow("histogram", histImage);
}*/