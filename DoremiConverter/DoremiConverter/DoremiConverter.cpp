#include "pch.h"
#include "PreProcessing.h"
#include "MusicInformExtract.h"
#include <math.h>

// For Dev.
int main()
{
	//PreProcessing pre("rotated_sheet_original.jpg");
	//pre.binarization();
	//pre.show(pre.binaryImg, "Binary image");
	//pre.edgeDetect();
	//pre.show(pre.edgeImg, "Sobel edge image");
	//pre.rotateImage(pre.calculateDegree(pre.straightExtract()));
	//pre.show(pre.straightendImg, "Straightened image");
	//pre.inputImg = pre.straightendImg.clone();
	//pre.binarization();
	//pre.show(pre.binaryImg, "Straightened Binary image");
	//pre.edgeDetect();
	//pre.show(pre.edgeImg, "Straightened Sobel edge image");
	int DELAY_BLUR = 100;
	int MAX_KERNEL_LENGTH = 31;

	PreProcessing pre("notes.jpg");
	pre.binarization();
	//medianBlur(pre.binaryImg, pre.binaryImg, 1);	
	pre.show(pre.binaryImg, "Binary notes");
	MusicInformExtract info = MusicInformExtract();
	info.ComponentDetect(pre.binaryImg);
	pre.show(info.components, "cca image");

	waitKey(0);
	destroyAllWindows();
	return 0;
}