#pragma once

#include "ofMain.h"

class Particle{
	public:
		Particle();							//Class constructor
		void setup();						//Start particle
		void update(float dt,
			float destX,
			float destY,
			float destZ);					//Recalculate physics
		void draw(ofColor pColor1, ofColor pColor2);			//Draw particle

		ofPoint pos;						//Position
		ofPoint vel;						//Velocity
		float time;							//Time of living
		float lifeTime;						//Allowed lifetime
		float size;							//Maximum particle size
		bool live;							//Is particle alive

		float force;						//Intensity of mouse attraction
		bool tracking;						//Is particle tracking mouse

		ofColor color;
		float newR, newG, newB;

		int targetJoint;			//0 - Head, 1 - Center, 2 - Left Hand, 3 - Right Hand, 4 - Left Knee, 5 - Right Knee 
		int getTargetJoint();
};