#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
	public:
		//Function for generating sound
		void audioOut(float *output, int bufferSize, int nChannels);

		ofSoundStream soundStream;		//Object for sound output setup
		
		//User-changing parameters
		float userFreq;					//Frequency
		float userPwm;					//PWM value
		//Parameters used during synthesis
		float freq;						//Current frequency
		float pwm;						//Current PWM value
		float phase;					//Phase of the wave

		//Buffer for rendering last generated audio buffer
		vector<float> buf;

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
