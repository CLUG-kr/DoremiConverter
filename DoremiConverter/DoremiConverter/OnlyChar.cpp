#include "pch.h"
#include "PreProcessing.h"
#include "MusicInformExtract.h"
#include <math.h>

#define STAFFHEIGHT (3)
#define STAFFSPACE (5)

// For Dev.
int main()
{
	PreProcessing pre("rotated_sheet_original.jpg");
	pre.binarization();
	pre.edgeDetect();
	pre.rotateImage(pre.calculateDegree(pre.straightExtract()));
	pre.inputImg = pre.straightendImg.clone();
	pre.binarization();
	pre.stafflineDetect();
	//pre.show(pre.staffLine, "staffline");
	

	//imwrite("staffLine.jpg", pre.staffLine);
	
	// Detect Line
	int nr = pre.staffLine.rows;          
	int nc = pre.staffLine.cols * pre.staffLine.channels();
	int staff_h = 0;
	vector<int> temp_staff_y;
	int staff_order = 1;
	
	for(int i = 0; i < nr ; i++ ){
		
		uchar* data = pre.staffLine.ptr<uchar>(i);
		int wcount = 0;
		
		for(int j = 0; j < nc ; j++){
			
			if(data[j] == 255){
				wcount++;
			}
			
		}
		
		if(wcount != 0){		
			staff_h++;			
		}
		else{
			
			// staff -> i-1 i-2 i-3
			if(staff_h == STAFFHEIGHT){
				temp_staff_y.push_back(i-3);
				temp_staff_y.push_back(i-2);
				temp_staff_y.push_back(i-1);
				staff_h = 0;
			}
			// staff -> i-1 i-2 i-3 i-4
			else if(staff_h == STAFFHEIGHT+1){
				temp_staff_y.push_back(i-4);
				temp_staff_y.push_back(i-3);
				temp_staff_y.push_back(i-2);
				temp_staff_y.push_back(i-1);
				staff_h = 0;					
			}
			else{
				staff_h = 0;
			}
		}
		
	}



	// Distinguish staff or others
	int space = 0;
	int n_space = 0;
	vector<int> staff_y;

	staff_y.push_back(temp_staff_y[0]);

	for (int i = 1; i < temp_staff_y.size(); i++) {
		
		space = temp_staff_y[i] - temp_staff_y[i-1];
		
		// staff space
		if (space >=STAFFSPACE && space <= STAFFSPACE+2 ) {
			n_space++;
		}
		// margin
		else if(space > STAFFSPACE+2) {
			

			// If previous lines are staffs
			if (n_space >=3 && n_space<=4) {
				staff_y.push_back(temp_staff_y[i - 1]);
				staff_y.push_back(temp_staff_y[i]);
			}
			// if previous lines are not staffs
			else {
				staff_y.pop_back();
				staff_y.push_back(temp_staff_y[i]);
			}
			n_space = 0;
		}

		// end checking
		else if (i == temp_staff_y.size() - 1) {
			if (n_space == 4) {
				staff_y.push_back(temp_staff_y[i]);
			}
			n_space = 0;
		}

	}
	cout << "result" << endl;
	for (int i = 0; i<staff_y.size(); i++) {
		cout << staff_y[i] << endl;
	}


	// remove ROI 
	Mat img = pre.straightendImg.clone();
	Mat sub_img;

	/*
	sub_img = img(Rect(0, staff_y[0], img.cols, staff_y[1] - staff_y[0])); // share memory

	nr = sub_img.rows;
	nc = sub_img.cols * img.channels();

	for (int j = 0; j < nr; j++) {

		uchar* data = sub_img.ptr<uchar>(j);

		for (int k = 0; k < nc; k++) {

			data[k] = 255;

		}
	}
	*/
	
	for (int i = 0; i < staff_y.size(); i+=2) {

		sub_img = img(Rect(0, staff_y[i], img.cols, staff_y[i+1] - staff_y[i])); // share memory

		nr = sub_img.rows;
		nc = sub_img.cols * img.channels();

		for (int j = 0; j < nr; j++) {

			uchar* data = sub_img.ptr<uchar>(j);

			for (int k = 0; k < nc; k++) {

				data[k] = 255;

			}
		}


	}


	namedWindow("test", CV_WINDOW_AUTOSIZE);

	if (img.empty())
	{
		cout << "There's no sheet file!" << endl;
		return -1;
	}

	imshow("test", img);

	imwrite("OnlyChar.jpg", img);


	//vector<Vec4i> linesP;
	//linesP = pre.straightExtract();
	
	//for (size_t i = 0; i < linesP.size(); i++) {
		//cout<<linesP[i][0]<<" and "<<linesP[i][1]<<endl;
		//Vec4i l = linesP[i];
		//line(this->straightImg, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255, 255, 255), 1);
	//}
	
	//pre.rotateImage(pre.calculateDegree(pre.straightExtract()));
	//pre.inputImg = pre.straightendImg.clone();
	//pre.binarization();
	//pre.stafflineDetect();
	//pre.show(pre.staffLine, "staffline");
	
	waitKey(0);
	destroyAllWindows();
	return 0;
}
