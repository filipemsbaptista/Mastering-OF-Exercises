#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
	public:
		ofVideoPlayer video;			//Video player object
		deque<ofPixels> frames;			//Frames buffer
		int N;							//Frames buffer size

		//Pixels array for construcitng output
		ofPixels imagePixels;
		ofImage image;					//Output image

		//Main processing function which computes the pixel color (x, y) using frames buffer
		ofColor getSlitPixelColor(int x, int y);

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
