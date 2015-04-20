#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
	public:
		vector<ofPoint> vertices;
		vector<ofColor> colors;

		int nTri;					//The number of triangles
		int nVert;					//The number of vertices equals nTri * 3

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
