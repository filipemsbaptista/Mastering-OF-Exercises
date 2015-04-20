#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(60);

	//Allocate drawing buffer
	fbo.allocate(ofGetWidth(), ofGetHeight());

	//Fill buffer with white color
	fbo.begin();
	ofBackground(255, 255, 255,0);

	fbo.end();

	//Initialize variables
	a = 0;
	b = 0;
	pos = ofPoint(ofGetWidth()/2, ofGetWidth()/2);	//Screen center
	colorStep = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
	fbo.begin();		//Begin draw to buffer
	for(int i = 0; i<200; i++){
		draw1();
	}
	fbo.end();			//End draw to buffer
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(255, 255, 255);	//In this case, this is not necessary since the FBO fills the whole screen

	//Draw buffer
	ofSetColor(255, 255, 255);
	fbo.draw(0, 0);
}

void ofApp::draw1(){
	//Change a
	a += b *DEG_TO_RAD;				//a holds values in radians, b holds values in degrees
									//so when changing a we multiply b to DEG_TO_RAD constant
	//Change b
	b += 4;

	//Shift pos in direction by angle a
	lastPos = pos;					//Store last pos value
	ofPoint d = ofPoint(cos(a), sin(a));
	float len = 18;
	pos += d * len;

	//Change color each 100 steps
	if(colorStep % 100 == 0){
		//Generate random color
		color = ofColor(ofRandom(0,255), ofRandom(0,255), ofRandom(0,255));
	}
	colorStep++;

	//Draw line segment
	ofSetColor(color);
	ofLine(lastPos, pos);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	//Grab the screen image to file, aka, print-screen and save
	if(key == ' '){
		ofImage image;						//Declare image object

		//Grab contents of the screen
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());

		image.saveImage("spirals.png");		//Save image to file
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}