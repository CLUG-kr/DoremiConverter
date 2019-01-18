#include "pch.h"
#include "DoremiConverter.h"


DoremiConverter::DoremiConverter(string imgName) {
	this->inputImg = imread(imgName, CV_LOAD_IMAGE_COLOR);
	this->binarization(this->inputImg);
}

void DoremiConverter::binarization(Mat img) {
	threshold(img, img, 150, 255, CV_THRESH_BINARY);
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
	dc.show();
	return 0;
}
