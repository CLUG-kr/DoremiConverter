#include "pch.h"
#include "PreProcessing.h"
#include "MusicInformExtract.h"
#include <math.h>

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
	pre.show(pre.staffLine, "staffline");
	
	// count line's white cols
	int nr = pre.staffLine.rows;          
	int nc = pre.staffLine.cols * pre.staffLine.channels();
	int staff = 0;
	int staff_x[100];
	int staff_c = 0;
	
	for(int i = 0; i < nr ; i++ ){
		
		uchar* data = pre.staffLine.ptr<uchar>(i);
		int wcount = 0;
		
		for(int j = 0; j < nc ; j++){
			
			if(data[j] == 255){
				wcount++;
			}
			
		}
		
		if(wcount != 0){		
			staff++;			
		}
		else{
			
			// staff -> i-1 i-2 i-3
			if(staff == 3){		
				staff_x[staff_c] = i-3;
				staff_x[staff_c + 1] = i-2;
				staff_x[staff_c + 2] = i-1;
				staff_c = staff_c+3;	
				staff = 0;					
			}
						// staff -> i-1 i-2 i-3
			else if(staff == 4){		
				staff_x[staff_c] = i-4;
				staff_x[staff_c + 1] = i-3;
				staff_x[staff_c + 2] = i-2;
				staff_x[staff_c + 3] = i-1;
				staff_c = staff_c+4;	
				staff = 0;					
			}
			else{
				staff = 0;
			}
		}
		
	}
	
	for(int i = 0 ; i<staff_c; i++){
		cout << staff_x[i] << endl;
	}
	
	
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
