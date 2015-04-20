#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	nTri = 1200;		//The number of the triangles
	nVert = nTri * 3;	//The number of the vertices

	float Rad = 100;	//The shpere's radius
	float rad = 10;		//Maximal triangle "radius" (the maximal corrdinates' deviation from the triangle's center)

	//Fill the vertices array
	vertices.resize(nVert);
	for(int i=0; i<nTri; i++){
		//Generate the center of the triangle as a random point within the sphere radius

		//Take the random point from cube[-1,1]x[-1,1]x[-1,1]
		ofPoint center (ofRandom(-1,1), ofRandom(-1,1), ofRandom(-1,1));
		center.normalize();		//Normalize vector's length to 1
		center *= Rad;			//Now the center vector has length Rad

		//Generate the triangle's vertices as the center plus random point from [-rad, rad]x[-rad, rad]x[-rad, rad]
		for(int j=0; j<3; j++){
			vertices[i*3 + j] = center + ofPoint(ofRandom(-rad, rad), ofRandom(-rad, rad), ofRandom(-rad, rad));
		}
	}

	//Fill the array of triangle's colors
	colors.resize(nTri);
	for(int i = 0; i<nTri; i++){
		//Take a random color from black to red
		colors[i] = ofColor(ofRandom(0,255), 0, 0);
	}
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofEnableDepthTest();				//Enable z-buffering

	//Set a gradient background from white to gray for adding an illusion of visual depth pf the scene
	ofBackgroundGradient(ofColor(255), ofColor(128));

	ofPushMatrix();						//Store the coordinate system matrix

	//Move the coordiante system to the center of the screen
	ofTranslate(ofGetWidth()/2, ofGetHeight()/2, 0);

	//Calculate the rotation angle
	float time = ofGetElapsedTimef();	//Get time in seconds
	float angle = time * 10;			//Compute angle. We rotate at speed 10 degrees per second
	ofRotate(angle, 0, 1, 0);			//Rotate the coordiante system along the y-axe

	//Draw the triangles
	for(int i = 0; i<nTri; i++){
		ofSetColor(colors[i]);			//Set color
		ofTriangle(vertices[i * 3], 
			vertices[i * 3 + 1], 
			vertices[i * 3 + 2]);		//Draw triangle
	}

	ofPopMatrix();						//Restore the coordiante system
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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