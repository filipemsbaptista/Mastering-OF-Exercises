#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0,0,0);
	//image.loadImage("apollo.jpg");
	//image.saveImage("apollo.png");
	image.loadImage("moon.png");
	image2.clone(image);
	image.resize(image.width * 0.5, image.height * 0.5);

	//Modifying image

	//Getting pointer to pixel array of image
	unsigned char *data = image.getPixels();

	//Calculate a number of pixel components
	int components = image.bpp / 8;

	//Modify pixel array
	for(int y = 0; y < image.height; y++){
		for(int x = 0; x < image.width; x++){
			//Read pixel (x,y) color components
			int index = components * (x + image.width * y);
			int red = data[index];
			int green = data[index +1];
			int blue = data[index + 2];

			//Calculate periodical modulation
			float u = abs(sin(x * 0.1) * sin(y * 0.1));

			//Set red component modulated by u
			data[index] = red * u;

			//Set green component modulated by u
			data[index + 1] = (255 - red);

			//Set blue component modulated by u
			data[index + 2] = (255 - blue);

			//If there is alpha component or not we don't touch it anyway
		}
	}
	//Calling image.update() to apply changes
	image.update();
}

//--------------------------------------------------------------
void ofApp::update(){
	float time = ofGetElapsedTimef();

	//Build image2 using image
	for(int y = 0; y < image.height; y++){
		for(int x = 0; x < image.width; x++){
			//Use y and time for computing shifted x1
			float amp = sin(y * 0.03);
			int x1 = x + sin(time * 2.0) * amp * 50.0;

			//Clamp x1 to range [0, image.width - 1]
			x1 = ofClamp(x1, 0, image.width - 1);

			//Set image2(x, y) equal to image(x1, y)
			ofColor color = image.getColor(x1, y);
			image2.setColor(x, y, color);
		}
	}
	image2.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	/*
	ofPushMatrix();				//Store the transformation matrix
	ofRotate(10.0);				//Applying rotation on 10 degrees
	image.draw(0, 0);			//Draw image
	ofPopMatrix();				//Restore the transformation
	*/

	for(int i = 0; i<20; i++){
		ofPushMatrix();

		//Shift center of coordinate system (0,0) to the desired point, which will be rotation center
		ofTranslate(ofGetWidth()/2, ofGetHeight()/2);

		//Rotate coordinate system on i * 15 degrees
		ofRotate(i * 15);
		//ofRotate(10.0 * ofGetElapsedTimef());

		/*//Draw image in a way that its center on the screen coincide with (0,0)
		image.setAnchorPercent(0.5, 0.5);
		image.draw(0,0);
		*/

		//Go right on 50 + i * 10 pixels in rotated coordiante system
		ofTranslate(50 + i * 10, 0);
		
		
		//Scale coordinate system for decreasing drawing image size
		float sc1 = 1.0 - i * 0.8 / 20.0;		//sc1 decreases with i, so the images become gradually smaller
		ofScale(sc1, sc1);

		ofSetColor(255,255,255, 255 - (i*15));
		image.draw(-100, -100, 200, 200);
		//image.draw(0,0);

		ofPopMatrix();
	}
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