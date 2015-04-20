#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
	public:
		ofPoint pos0;		//Center of suspension
		ofPoint pos;		//Ball's position
		ofPoint velocity;	//Ball's velocity

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
