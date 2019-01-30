#include "pch.h"
#include "PreProcessing.h"
#include <math.h>

PreProcessing::PreProcessing(string imgName) {
	this->inputImg = imread(imgName, IMREAD_GRAYSCALE);
}

int PreProcessing::show(Mat img, string title) {
	// cout << "OpenCV Version : " << CV_VERSION << endl;
	namedWindow(title, CV_WINDOW_AUTOSIZE);

	if (img.empty())
	{
		cout << "There's no sheet file!" << endl;
		return -1;
	}

	imshow(title, img);
}

// Image binarization
void PreProcessing::binarization() {

	//threshold(this->inputImg, this->binaryImg, 0, 255, THRESH_OTSU);
	//adaptiveThreshold(inputImg, this->binaryImg, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 5, 10);
	//**adaptiveThreshold(inputImg, this->binaryImg, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 15, 10);
	adaptiveThreshold(~inputImg, this->binaryImg, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 15, -2);
}

// Edge detecting with Sobel Algorithm
void PreProcessing::edgeDetect() {

	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;
	
	/*
	// reduce the noise (kernel size=3)
	Mat blurredImg;
	GaussianBlur(this->binaryImg, blurredImg, Size(5, 5), 0, 0, BORDER_DEFAULT);
	*/
	
	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y;

	// calculate derivatives in x and y directions
	Sobel(binaryImg, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT);
	Sobel(binaryImg, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT);
	//Scharr(blurredImg, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT);
	//Scharr(blurredImg, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT);

	// convert results back to CV_8U
	convertScaleAbs(grad_x, abs_grad_x);
	convertScaleAbs(grad_y, abs_grad_y);

	// add sobel_x & sobel_y
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, this->edgeImg);
}

// Straight line extract with Hough transformation
vector<Vec4i> PreProcessing::straightExtract() {

	Mat blank(this->inputImg.rows, this->inputImg.cols, CV_8UC1, Scalar(0));
	this->straightImg = blank.clone();

	/* too much
	// standard hough line transform
	vector<Vec2f> lines; // will hold the results of the detection
	HoughLines(this->edgeImg, lines, 1, CV_PI / 180, 150, 0, 0);
	// Draw lines
	for (size_t i = 0; i < lines.size(); i++) {
		float rho = lines[i][0], theta = lines[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a * rho, y0 = b * rho;
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));
		line(this->straightImg, pt1, pt2, Scalar(255, 255, 255), 2, LINE_AA);
		printf("®G®G\n");
	}
	*/

	// probabilistic line transform
	vector<Vec4i> linesP;
	HoughLinesP(this->edgeImg, linesP, 1, CV_PI / 180, 50, 200, 10);
	for (size_t i = 0; i < linesP.size(); i++) {
		Vec4i l = linesP[i];
		line(this->straightImg, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255, 255, 255), 1);
	}
	return linesP;
}

// Calculate the slope average of straight lines (staff line)
double PreProcessing::calculateDegree(vector<Vec4i> lines) {
	double sum = 0;
	for (size_t i = 0; i < lines.size(); i++) {
		Vec4i l = lines[i];
		int dx = l[0] - l[2];
		int dy = l[1] - l[3];
		double rad = atan2((double)dx, (double)dy);
		double degree = abs(rad * 180) / CV_PI;
		sum += degree;
	}
	double average = round(sum / lines.size() * 100) / 100;
	double degree = 90 - average;
	printf("%f", degree);
	return degree;
}

// rotate the image
void PreProcessing::rotateImage(double degree) {
	Point center = Point(this->inputImg.cols / 2, this->inputImg.rows / 2);
	double scale = 1;
	degree = degree * -1;
	printf("%f", degree);
	Mat rot_mat = getRotationMatrix2D(center, degree, scale);
	warpAffine(this->inputImg, this->straightendImg, rot_mat, this->inputImg.size());
}

void PreProcessing::stafflineDetect() {
	this->staffLine = this->binaryImg.clone();
	int horizontalsize = this->staffLine.cols / 50;
	Mat horizontalStructure = getStructuringElement(MORPH_RECT, Size(horizontalsize, 1));
	erode(this->staffLine, this->staffLine, horizontalStructure, Point(-1, -1));
	dilate(this->staffLine, this->staffLine, horizontalStructure, Point(-1, -1));
}

void PreProcessing::objectsDetect() {
	this->objects = this->binaryImg.clone();
	int verticalsize = this->objects.rows / 280;
	Mat verticalStructure = getStructuringElement(MORPH_RECT, Size(1, verticalsize));
	erode(this->objects, this->objects, verticalStructure, Point(-1, -1));
	dilate(this->objects, this->objects, verticalStructure, Point(-1, -1));

	/* Extract edges and smooth image according to the logic
	Mat edges;
	adaptiveThreshold(this->objects, edges, 255, CV_ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 3, -2);
	Mat kernel = Mat::ones(2, 2, CV_8UC1);
	dilate(edges, edges, kernel);
	blur(this->objects, this->objects, Size(2, 2));
	this->objects.copyTo(this->objects, edges);
	*/
}