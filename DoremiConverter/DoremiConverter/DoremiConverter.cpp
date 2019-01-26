#include "pch.h"
#include "DoremiConverter.h"


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
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16U;

	// reduce the noise (kernel size=3)
	Mat blurredImg;
	GaussianBlur(this->inputImg, blurredImg, Size(3, 3), 0, 0, BORDER_DEFAULT);
	
	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y;

	// calculate derivatives in x and y directions
	Sobel(blurredImg, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT);
	Sobel(blurredImg, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT);
	//Scharr(blurredImg, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT);
	//Scharr(blurredImg, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT);

	// convert results back to CV_8U
	convertScaleAbs(grad_x, abs_grad_x);
	convertScaleAbs(grad_y, abs_grad_y);

	// add sobel_x & sobel_y
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, this->edgeImg);
}

// For Dev.
int main()
{
	DoremiConverter dc("rotated_sheet_original.jpg");
	dc.binarization(dc.inputImg);
	dc.show(dc.inputImg, "binary image");
	dc.edgeDetect();
	dc.show(dc.edgeImg, "sobel edge");
	waitKey(0);
	destroyAllWindows();
	return 0;
}
