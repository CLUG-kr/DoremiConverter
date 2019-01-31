#include "pch.h"
#include "PreProcessing.h"
#include "MusicInformExtract.h"
#include "RemoveStaff.h"
#include "PreCharRecognize.h"
#include <math.h>

// For Dev.
int main()
{
	PreProcessing pre("rotated_sheet_original.jpg");
	pre.binarization();
	//pre.show(pre.binaryImg, "Binary image");
	pre.edgeDetect();
	//pre.show(pre.edgeImg, "Sobel edge image");
	pre.rotateImage(pre.calculateDegree(pre.straightExtract()));
	//pre.show(pre.straightendImg, "Straightened image");
	pre.inputImg = pre.straightendImg.clone();
	pre.binarization();
	//pre.show(pre.binaryImg, "Straightened Binary image");
	//pre.edgeDetect();
	//pre.show(pre.edgeImg, "Straightened Sobel edge image");
	//pre.straightExtract();
	//pre.show(pre.straightImg, "straight");
	pre.stafflineDetect();
	pre.show(pre.staffLine, "staffline");
	//imwrite("staffLine.jpg", pre.staffLine);

	/* Char Recognition First Step */
	// Detect Line
	RemoveStaff rs;
	rs.DetectLines(pre.staffLine);
	// Distinguish staff or others
	rs.GetStaffLocation();
	// remove ROI 
	rs.Remove(pre.straightendImg.clone());
	//rs.show(rs.result, "result");
	
	/* Char Recognition Second Step */
	// Crop Char area
	// Title, Composer
	PreCharRecognize cr(rs.result, rs.staff_y);
	cr.CropTop();
	// crop line <- top + bottom
	cr.CropAllLine();


	// 글자 세분화
	//Read
	Mat img1 = cv::imread("PreCRImg/TopImg.jpg");
	Mat subimg1;
	string title;
	//Detect
	vector<Rect> letterBBoxes1 = cr.detectLetters(img1);
	// 글자 구역 인식한거 저장하는 코드
	for (int i = 0; i < letterBBoxes1.size(); i++) {
		rectangle(img1, letterBBoxes1[i], Scalar(0, 255, 0), 2, 8, 0);
	}
	imwrite("PreCRImg/TopImg-entire.jpg", img1);

	// 글자 구역 나눈거 저장하는 코드
	/*
	for (int i = 0; i < letterBBoxes1.size(); i++) {
		rectangle(img1, letterBBoxes1[i], Scalar(255, 255, 255), 0, 0, 0);
		subimg1 = img1(letterBBoxes1[i]);
		title = "PreCRImg/LineTop3-split";
		title += to_string(i);
		title += ".jpg";
		imwrite(title, subimg1);
	}
	*/




	// excute tesseract -> save line order, top(code), bottom(lyrics)

	waitKey(0);
	destroyAllWindows();
	return 0;
}