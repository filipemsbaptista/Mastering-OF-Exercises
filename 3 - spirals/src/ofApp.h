#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
	public:
		float a, b;				//Angle and its increments
		ofPoint pos, lastPos;		//Current and last drawing position
		ofColor color;				//Drawing color
		int colorStep;				//Counter for color changing
		ofFbo fbo;					//Drawing buffer
		void draw1();				//Draw one line segment

		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
};
