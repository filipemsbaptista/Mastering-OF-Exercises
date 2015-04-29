#include "Params.h"

void Params::setup(){
	eCenter = ofPoint(ofGetWidth()/2, ofGetHeight()/2);
	eRad = 40;
	bornRate = 178;
	bornCount = 0;
	
	velRad = 200;
	lifeTime = 5.0;
	rotate = 2;
	size = 1;
	Zintensity = 2;
	
	force = 0.03;
	tracking = true;
}