#pragma once

#include "ofMain.h"
#include "ofxUI.h"
#include "SliderParams.h"

class Interface : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		
		ofxUICanvas *gui1, *gui2, *gui3;
		void setGUI1(float *force, float *size, float *lifeTime, float *history, float *rotate, float *eRad, float *bornRate, float *velRad, int *Zintensity),
			setGUI2(), setGUI3();
		void exit(); 
		void guiEvent(ofxUIEventArgs &e);

		SliderParams sP;
};
