#include "pch.h"
#include "RemoveStaff.h"

// constructor
RemoveStaff::RemoveStaff() {
	
}

int RemoveStaff::show(Mat img, string title) {
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

// detect lines from binary image
void RemoveStaff::DetectLines(Mat img) {
	
	int nr = img.rows;
	int nc = img.cols * img.channels();
	int staff_h = 0;
	int staff_order = 1;

	for (int i = 0; i < nr; i++) {

		uchar* data = img.ptr<uchar>(i);
		int wcount = 0;

		for (int j = 0; j < nc; j++) {

			if (data[j] == 255) {
				wcount++;
			}

		}

		if (wcount != 0) {
			staff_h++;
		}
		else {

			// staff -> i-1 i-2 i-3
			if (staff_h == STAFFHEIGHT) {
				this->temp_staff_y.push_back(i - 3);
				this->temp_staff_y.push_back(i - 2);
				this->temp_staff_y.push_back(i - 1);
				staff_h = 0;
			}
			// staff -> i-1 i-2 i-3 i-4
			else if (staff_h == STAFFHEIGHT + 1) {
				this->temp_staff_y.push_back(i - 4);
				this->temp_staff_y.push_back(i - 3);
				this->temp_staff_y.push_back(i - 2);
				this->temp_staff_y.push_back(i - 1);
				staff_h = 0;
			}
			else {
				staff_h = 0;
			}
		}

	}

}

// get staff line's y coordinations
void RemoveStaff::GetStaffLocation() {
	int space = 0;
	int n_space = 0;

	this->staff_y.push_back(this->temp_staff_y[0]);

	for (int i = 1; i < this->temp_staff_y.size(); i++) {

		space = this->temp_staff_y[i] - this->temp_staff_y[i - 1];

		// staff space
		if (space >= STAFFSPACE && space <= STAFFSPACE + 2) {
			n_space++;
		}
		// margin
		else if (space > STAFFSPACE + 2) {


			// If previous lines are staffs
			if (n_space >= 3 && n_space <= 4) {
				this->staff_y.push_back(this->temp_staff_y[i - 1]);
				this->staff_y.push_back(this->temp_staff_y[i]);
			}
			// if previous lines are not staffs
			else {
				this->staff_y.pop_back();
				this->staff_y.push_back(this->temp_staff_y[i]);
			}
			n_space = 0;
		}

		// end checking
		else if (i == this->temp_staff_y.size() - 1) {
			if (n_space == 4) {
				this->staff_y.push_back(this->temp_staff_y[i]);
			}
			n_space = 0;
		}

	}
}

// remove all staff line's area ( with Rectangle shape ) from straightendImg
void RemoveStaff::Remove(Mat img){

	Mat sub_img;
	int nr;
	int nc;
	int staffArea_h = this->staff_y[1] - this->staff_y[0];

	cout << "오선위치" << endl;

	for (int i = 0; i < this->staff_y.size(); i += 2) {

		sub_img = img(Rect(0, this->staff_y[i], img.cols, staffArea_h)); // share memory

		this->staff_y[i + 1] = this->staff_y[i] + staffArea_h;

		nr = sub_img.rows;
		nc = sub_img.cols * img.channels();

		for (int j = 0; j < nr; j++) {

			uchar* data = sub_img.ptr<uchar>(j);

			for (int k = 0; k < nc; k++) {

				data[k] = 255;

			}
		}

		cout << i/2 + 1 <<"번째 오선" << endl;
		cout << "시작:" << this ->staff_y[i] << endl;
		cout << "끝:" << this->staff_y[i+1] << endl;

	}

	result = img;

}