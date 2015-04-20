#include "ofApp.h"

int W = 100;		//Grid size
int H = 100;

void setNormals(ofMesh &mesh){
	//The number of the vertices
	int nVertex = mesh.getNumVertices();

	//The number of triangles
	int nTri = mesh.getNumIndices()/3;

	vector<ofPoint> norm(nVertex);	//Array for the normals

	//Scan all the triangles. For each triangle add its normal to norm's vectors of triangle's vertices
	for(int t = 0; t < nTri; t++){
		//Get indices of the triangle t
		int i1 = mesh.getIndex(3 * t);
		int i2 = mesh.getIndex(3 * t + 1);
		int i3 = mesh.getIndex(3 * t + 2);

		//Get vertices of the triangle
		const ofPoint &v1 = mesh.getVertex(i1);
		const ofPoint &v2 = mesh.getVertex(i2);
		const ofPoint &v3 = mesh.getVertex(i3);

		//Compute the triangle's normal
		ofPoint dir = ((v2 - v1).crossed(v3 - v1)).normalized();

		//Accumulate it to norm array for i1, i2, i3
		norm[i1] += dir;
		norm[i2] += dir;
		norm[i3] += dir;
	}

	//Normalize the normal's length
	for(int i = 0; i < nVertex; i++){
		norm[i].normalize();
	}

	//Set the normals
	mesh.clearNormals();
	mesh.addNormals(norm);
}

//--------------------------------------------------------------
void ofApp::setup(){
	//Set up vertices and colors
	for(int y = 0; y < H; y++){
		for(int x = 0; x < W; x++){
			mesh.addVertex(ofPoint((x - W/2) * 6, (y - H/2) * 6, 0));
			mesh.addColor(ofColor(0, 0, 0));
		}
	}
	//Set up triangles' indices
	for(int y = 0; y < H - 1; y++){
		for(int x = 0; x < W - 1; x++){
			int i1 = x + (W * y);
			int i2 = x+1 + (W * y);
			int i3 = x + W * (y + 1);
			int i4 = x+1 + W * (y+1);

			mesh.addTriangle(i1, i2, i3);
			mesh.addTriangle(i2, i4, i3);
		}
	}
	setNormals(mesh);
	light.enable();
}

//--------------------------------------------------------------
void ofApp::update(){
	float time = ofGetElapsedTimef();

	//Change vertices
	for(int y = 0; y < H; y++){
		for(int x = 0; x < W; x++){
			int i = x + W * y;			//Vertex index
			ofPoint p = mesh.getVertex(i);
			//Get Perlin noise value
			float value = ofNoise(x* 0.05, y * 0.05, time * 0.5);
			//Change z-coordinate of vertex
			p.z = value * 100;
			mesh.setVertex(i, p);
			//Change color of vertex
			mesh.setColor(i, ofColor(value * 255, value * 255, 255));
		}
	}
	setNormals(mesh);					//Update normals
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofEnableDepthTest();			//Enable z-buffering

	//Set a background
	ofBackgroundGradient(ofColor(255), ofColor(128));

	ofPushMatrix();					//Store the coordiante system

	//Move coordinate system to the center of the screen
	ofTranslate(ofGetWidth()/2, ofGetHeight()/2, 0);

	//Calculate the rotation angle
	float time = ofGetElapsedTimef();	//Get time in seconds
	float angle = time * 20;			//Compute angle. Rotation at speed 20 degrees per second

	ofRotate(30, 1, 0, 0);
	ofRotate(angle, 0, 0, 1);

	//Draw mesh
	//Here ofSetColor() does not affect the result of drawing, because the mesh has its own vertices' colors
	mesh.draw();

	ofPopMatrix();					//Restore the coordinate system
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