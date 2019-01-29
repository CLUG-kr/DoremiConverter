#include "pch.h"
#include "DoremiConverter.h"


DoremiConverter::DoremiConverter(string imgName) {
	this->inputImg = imread(imgName, CV_LOAD_IMAGE_COLOR);
	this->binarization();
}

void DoremiConverter::binarization() {
	threshold(this->inputImg, this->inputImg, 150, 255, CV_THRESH_BINARY);
}

vector<vector<int>> DoremiConverter::encodeRLE() {
	int height = this->inputImg.rows;
	int width = this->inputImg.cols;
	vector<vector<int>> RLE;

	for (int w = 0; w < width; w++) {
		vector<int> col;
		int zeroCount = 0;
		for (int h = 0; h < height; h++) {
			uchar value = this->inputImg.data[h * width * 3 + w * 3];
			if (value == 0) {
				zeroCount++;
			}
			else {
				col.push_back(zeroCount);
				zeroCount = 0;
			}
		}
		RLE.push_back(col);
	}
	return RLE;
}

Mat DoremiConverter::decodeRLE(vector<vector<int>> RLE) {
	Mat decodeImg = Mat(this->inputImg.rows,this->inputImg.cols, CV_8UC1, Scalar(0));
	int height = decodeImg.rows;
	int width = decodeImg.cols;

	uchar *data = decodeImg.data;
	vector<vector<int>>::iterator rows;
	vector<int>::iterator colPixel;

	for (rows = RLE.begin(); rows != RLE.end(); rows++) {
		for (colPixel = rows->begin(); colPixel != rows->end(); colPixel++) {

		}
	}
	
	return decodeImg;
}

int DoremiConverter::show() {
	cout << "OpenCV Version : " << CV_VERSION << endl;
	namedWindow("Show input img", CV_WINDOW_AUTOSIZE);

	if (this->inputImg.empty())
	{
		cout << "There's no sheet file!" << endl;
		return -1;
	}

	imshow("Show input img", this->inputImg);

	waitKey(0);
	destroyAllWindows();
}

int DoremiConverter::show(Mat img) {
	cout << "OpenCV Version : " << CV_VERSION << endl;
	namedWindow("Show some img", CV_WINDOW_AUTOSIZE);

	if (img.empty())
	{
		cout << "There's no sheet file!" << endl;
		return -1;
	}

	imshow("Show some img", img);

	waitKey(0);
	destroyAllWindows();
}

// For Dev.
int main()
{
	DoremiConverter dc("sobel.jpg");
	//dc.show();
	dc.show(dc.decodeRLE(dc.encodeRLE()));
	return 0;
}
