#include "pch.h"
#include "DoremiConverter.h"


DoremiConverter::DoremiConverter(string imgName) {
	this->inputImg = imread(imgName, IMREAD_GRAYSCALE);
	this->binarization(this->inputImg);
}

void DoremiConverter::binarization(Mat img) {
	threshold(img, img, 0, 255, THRESH_OTSU);
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
	DoremiConverter dc("rotated_sheet_original.jpg");
	dc.show();
	return 0;
}
