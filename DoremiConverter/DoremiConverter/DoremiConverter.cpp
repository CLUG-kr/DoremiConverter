#include "pch.h"
#include "DoremiConverter.h"
#include <math.h>

DoremiConverter::DoremiConverter(string imgName) {
	this->inputImg = imread(imgName, IMREAD_GRAYSCALE);
	//this->binarization(this->inputImg);
	//this->edgeDetect();
}

void DoremiConverter::binarization(Mat img) {
	threshold(img, img, 0, 255, THRESH_OTSU);
}

int DoremiConverter::show(Mat img, string title) {
	// cout << "OpenCV Version : " << CV_VERSION << endl;
	namedWindow(title, CV_WINDOW_AUTOSIZE);

	if (img.empty())
	{
		cout << "There's no sheet file!" << endl;
		return -1;
	}

	imshow(title, img);
}


void DoremiConverter::edgeDetect() {

	// Canny
	//Canny(this->inputImg, this->edgeImg, 50, 200, 3);

	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;

	// reduce the noise (kernel size=3)
	Mat blurredImg;
	// GaussianBlur(this->inputImg, blurredImg, Size(5, 5), 0, 0, BORDER_DEFAULT);
	
	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y;

	// calculate derivatives in x and y directions
	Sobel(inputImg, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT);
	Sobel(inputImg, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT);
	//Scharr(blurredImg, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT);
	//Scharr(blurredImg, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT);

	// convert results back to CV_8U
	convertScaleAbs(grad_x, abs_grad_x);
	convertScaleAbs(grad_y, abs_grad_y);

	// add sobel_x & sobel_y
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, this->edgeImg);

	// dilate
	//dilate(this->edgeImg, this->edgeImg, Mat());
}

void DoremiConverter::straightDetect() {

	Mat blank(this->inputImg.rows, this->inputImg.cols, CV_8UC1, Scalar(0));
	this->straightImg = blank.clone();

	/* 
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
		printf("췍췍\n");
	}
	*/

	// probabilistic line transform
	vector<Vec4i> linesP;
	HoughLinesP(this->edgeImg, linesP, 1, CV_PI / 180, 50, 300, 10);
	for (size_t i = 0; i < linesP.size(); i++) {
		Vec4i l = linesP[i];
		line(this->straightImg, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255, 255, 255), 1, LINE_AA);
	}
	calculateDegree(linesP);
}

// Calculate the slope average of straight lines (staff line)
void DoremiConverter::calculateDegree(vector<Vec4i> lines) {
	double sum = 0;
	for (size_t i = 0; i < lines.size(); i++) {
		Vec4i l = lines[i];
		int dx = l[0] - l[2];
		int dy = l[1] - l[3];
		double rad = atan2((double)dx, (double)dy);
		double degree = abs(rad * 180) / CV_PI;
		sum += degree;
	}
	float average = (float) roundf(sum / lines.size() * 100) / 100;
	printf("%f", average);
}

// For Dev.
int main()
{
	DoremiConverter dc("rotated_sheet_original.jpg");
	dc.binarization(dc.inputImg);
	//dc.show(dc.inputImg, "binary image");
	dc.edgeDetect();
	//dc.show(dc.edgeImg, "sobel edge");
	dc.straightDetect();
	dc.show(dc.straightImg, "hough line");
	waitKey(0);
	destroyAllWindows();
	return 0;
}
