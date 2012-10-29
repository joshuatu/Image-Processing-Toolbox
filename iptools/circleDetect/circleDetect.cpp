#include "circleDetect.h"

/*-----------------------------------------------------------------------**/
void circleDetect::hough(image &edgeImg, image &tgt, ROI roi){
	// parameter space for circle: x,y,R
	int rMin = 1;	//radius (in pix?)
	int rMax = 5;
	int rDelta = 1;
	int aMin = 0;	//possible x
	int aMax = edgeImg.getNumberOfColumns();
	int aDelta = 1;
	int bMin = 0;	//possible y
	int bMax = edgeImg.getNumberOfRows();
	int bDelta = 1;

	int acc[aMax-aMin][bMax-bMin][rMax-rMin];	// set up accumulator array
	memset(acc,0,sizeof(acc));	//initialize to 0



	for (int i=0; i<edgeImg.getNumberOfRows(); i++){	// for each edge point
		for (int j=0; j<edgeImg.getNumberOfColumns(); j++){
			int G = edgeImg.getPixel(i,j);// get gradient magnitude
			if (roi.InROI(i,j)){
				// calculate the possible circle equations (cone?)
				for(int a=aMin; a<aMax; a+=aDelta){ // for all x
					for(int b=bMin; b<bMax; b+=bDelta){ // for all x// for all y
						for(int r=rMin; r<rMax; r+=rDelta){
							acc[a][b][r] += G; // increment accumulator array
						}
					}
				}
			//}else{	
				//ignore the pixel
			}
		}
	}

	// display hough transform (2D projection?, at a set radius?)
	//what size? tgt.resize()
}
