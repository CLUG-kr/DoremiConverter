#include "pch.h"
#include "PreProcessing.h"
#include "MusicInformExtract.h"
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
	//pre.show(pre.staffLine, "staffline");
	pre.objectsDetect();
	//pre.show(pre.objects, "objects");
	
	MusicInformExtract info = MusicInformExtract();
	info.componentDetect(pre.objects);
	pre.show(~info.components, "cca image");
	
	waitKey(0);
	destroyAllWindows();
	return 0;
}