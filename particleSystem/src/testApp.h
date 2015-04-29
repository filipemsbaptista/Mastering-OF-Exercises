#pragma once

#include "ofMain.h"
#include "Interface.h"
#include "Params.h"
#include "Particle.h"
#include "NiTE.h"

//Declaration of a global variable for paramters class, through which all the parameters are acessed
extern Params param;

class testApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
 
		//GUI
		Interface interf;
		bool drawInterface;

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		float destX, destY, destZ;

		ofPoint headPos, neckPos, handLPos, elbowLPos, handRPos,
			elbowRPos, shoulderLPos, shoulderRPos, torsoPos, hipLPos, hipRPos,
			kneeLPos, kneeRPos, footLPos, footRPos, centerPos;
		bool drawSkeleton;

		//Kinect
		nite::Status niteRc;
		nite::UserTracker userTracker;
		nite::UserTrackerFrameRef userTrackerFrame;

		void updateUserState(const nite::UserData& user, unsigned long long ts);
		void drawLimb(nite::UserTracker* pUserTracker, const nite::SkeletonJoint& joint1, const nite::SkeletonJoint& joint2);


};
