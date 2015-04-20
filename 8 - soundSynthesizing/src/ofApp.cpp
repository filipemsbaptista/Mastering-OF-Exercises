#include "ofApp.h"

int bufSize = 512;					//Sound card buffer size
int sampleRate = 44100;				//Sound sample rate
float volume = 0.1;					//Output volume

void ofApp::audioOut(float *output, int bufferSize, int nChannels){
	//Fill output buffer, and also move freq to userFreq and pwm to userPwm slowly
	for(int i = 0; i < bufferSize; i++){
		//freq smoothly reaches userFreq
		freq += (userFreq - freq) * 0.001;
		//pwm slowly reaches userPwm
		pwm += (userPwm - pwm) * 0.001;

		//Change phase and push it into [0, 1] range
		phase += freq / sampleRate;
		phase = fmod(phase, 1.0);

		//Calculate the output audio sample value
		//Instead of 1 and 0 we use 1 and -1 output values for the sound wave to be symmetrical along y-axe
		float v = (phase < pwm) ? 1.0 : -1.0;

		//Set the computed value to the left and right channels of output buffer, also using global volume value defined above
		output[i*2] = output[i*2 + 1] = v * volume;

		//Set the value to buffer buf, used for rendering on the screen
		//Note: bufferSize can ocasionally differ from bufSize
		if(i < bufSize)
			buf[i] = v;
	}
}

//--------------------------------------------------------------
void ofApp::setup(){
	userFreq = 100.0;				//Some initial frequency
	userPwm = 0.5;					//Some initial PWM value

	freq = userFreq;
	pwm = userPwm;
	phase = 0;
	buf.resize(bufSize);
	
	//Start the sound output
	soundStream.setup(this, 2, 0, 44100, 512, 4);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(255, 255, 255);
	//Draw the buffer values
	ofSetColor(0, 0, 0);
	for(int i = 0; i < bufSize - 1; i++){
		ofLine(i, 100 - buf[i]*50, (i+1), 100 - buf[i+1]*50);
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
	userFreq = ofMap(x, 0, ofGetWidth(), 1, 2000);
	userPwm = ofMap(y, 0, ofGetHeight(), 0, 1);
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