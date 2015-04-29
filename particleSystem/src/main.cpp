#include "ofMain.h"
#include "testApp.h"

int main( ){
	ofSetupOpenGL(1366,768, OF_WINDOW);			// <-------- setup the GL context
	ofSetWindowTitle("Particle System");

	ofRunApp( new testApp());
}