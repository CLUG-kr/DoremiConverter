#include "pch.h"
#include "DoremiConverter.h"

DoremiConverter::DoremiConverter(string imgName) {
	this->inputImg = imread(imgName, CV_LOAD_IMAGE_COLOR);
	this->binarization(this->inputImg);
}

Mat makeHistogram(int FLAG) {

}

void DoremiConverter::binarization(Mat img) {
	threshold(img, img, 150, 255, CV_THRESH_BINARY);
}

int DoremiConverter::getNote() {

}

int DoremiConverter::show() {
	cout << "OpenCV Version : " << CV_VERSION << endl;
	namedWindow("Sheet Test View", CV_WINDOW_AUTOSIZE);

	if (this->inputImg.empty())
	{
		cout << "There's no sheet file!" << endl;
		return -1;
	}

	imshow("Sheet Test View", this->inputImg);
	waitKey(0);
	destroyAllWindows();
}


// For Dev.
int main()
{
	DoremiConverter dc("windows.jpg");
	PreProcessing pre("rotated_sheet_original.jpg");
	pre.binarization();
	pre.show(pre.binaryImg, "Binary image");
	pre.edgeDetect();
	pre.show(pre.edgeImg, "Sobel edge image");
	pre.rotateImage(pre.calculateDegree(pre.straightExtract()));
	pre.show(pre.straightendImg, "Straightened image");
	pre.inputImg = pre.straightendImg.clone();
	pre.binarization();
	pre.show(pre.binaryImg, "Straightened Binary image");
	pre.edgeDetect();
	pre.show(pre.edgeImg, "Straightened Sobel edge image");

	waitKey(0);
	destroyAllWindows();
	return 0;
}