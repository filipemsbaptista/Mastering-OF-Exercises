#include "testApp.h"


#define MAX_USERS 10
bool g_visibleUsers[MAX_USERS] = {false};
nite::SkeletonState g_skeletonStates[MAX_USERS] = {nite::SKELETON_NONE};

#define USER_MESSAGE(msg) \
	{printf("[%08llu] User #%d:\t%s\n",ts, user.getId(),msg);}

#define GL_WIN_SIZE_X	1280
#define GL_WIN_SIZE_Y	1024
int g_nXRes = 0, g_nYRes = 0;


/* -------------------------------------------------------------------
		 _____       _             ______ _      _             
		/  __ \     | |            | ___ (_)    | |            
		| /  \/ ___ | | ___  _ __  | |_/ /_  ___| | _____ _ __ 
		| |    / _ \| |/ _ \| '__| |  __/| |/ __| |/ / _ \ '__|
		| \__/\ (_) | | (_) | |    | |   | | (__|   <  __/ |   
		 \____/\___/|_|\___/|_|    \_|   |_|\___|_|\_\___|_|   
                                                       
----------------------------------------------------------------------*/
class ColorPicker : public ofBaseApp {
public:
		void setup();
		void draw();
		void mouseDragged(int x, int y);

		ofColor getColor1(), getColor2(), getColor3();

		ofFbo cP_fbo;					//Buffer to draw color picker
		float rectHeight;			//Height of the color shower
		float margin;				//Margin between color shower and color picker

		ofImage img;				//Image object for color picker
		
		ofColor color1, color2, color3, textColor;	

		float colorPickerIndex;		//0 - Left picker, 1 - Right picker, 2 - Middle picker

};

void ColorPicker::setup(){
	ofSetFrameRate(60);
	ofBackground(255, 255, 255, 255);
	
	img.loadImage("color-picker.png");

	rectHeight = 25;
	margin = 5;

	cP_fbo.allocate(img.width, img.height + rectHeight + margin, GL_RGB32F_ARB);

	color1 = ofColor(15,10,15);
	color2 = ofColor(ofColor::red);
	color3 = ofColor(ofColor::blue);
	textColor = ofColor(ofColor::black);

	colorPickerIndex = 0;
}

void ColorPicker::draw(){
	cP_fbo.begin();
	ofEnableAlphaBlending();  
		
	//Draw color gradient image
	ofSetColor(255,255,255);
	img.draw(0, rectHeight + margin);
		
	//Draw left picker
	ofSetColor(color1);
	ofFill();
	ofRect(2, 2, img.getWidth()/3, rectHeight);
		
	//Draw right picker
	ofSetColor(color2);
	ofFill();
	ofRect(img.getWidth() - (img.getWidth()/3) - 2, 2, img.getWidth()/3, rectHeight);

	//Draw middle picker
	ofSetColor(color3);
	ofFill();
	ofRect(4 + img.getWidth()/3, 2, img.getWidth()/3, rectHeight);

	ofDisableAlphaBlending();
	cP_fbo.end();

	glEnable(GL_BLEND);  
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);  

	ofSetColor(255,255,255);

	cP_fbo.draw(ofGetWidth() - cP_fbo.getWidth() - 20, ofGetHeight() - cP_fbo.getHeight() - 20);

	//Draw color picker text
	if(color1.r < 90 && color1.g < 90 && color1.b < 90)
			textColor = ofColor(255, 255, 255);
		else 
			textColor = ofColor(0, 0, 0);
	
	//Check picker text alpha value
	if(colorPickerIndex == 0)
		ofSetColor(textColor);
	else
		ofSetColor(textColor.r, textColor.g, textColor.b, 85);
	ofDrawBitmapString( "Background", ofGetWidth() - 20 - cP_fbo.getWidth(), ofGetHeight() - 20 - cP_fbo.getHeight() - 5 );
		
	if(colorPickerIndex == 1)
		ofSetColor(textColor);
	else
		ofSetColor(textColor.r, textColor.g, textColor.b, 85);
	ofDrawBitmapString( "Death", ofGetWidth() - 20 - cP_fbo.getWidth()/3, ofGetHeight() - 20 - cP_fbo.getHeight() - 5 );

	if(colorPickerIndex == 2)
		ofSetColor(textColor);
	else
		ofSetColor(textColor.r, textColor.g, textColor.b, 85);
	ofDrawBitmapString( "Birth", ofGetWidth() - 20 - cP_fbo.getWidth() + img.getWidth()/3, ofGetHeight() - 20 - cP_fbo.getHeight() - 5 );

}

void ColorPicker::mouseDragged(int mouseX, int mouseY){
	//Check click on color gradient
	if(mouseX < ofGetWidth() - 20 && mouseX > ofGetWidth() - 20 - img.width && mouseY < ofGetHeight() - 20 && mouseY > ofGetHeight() - 20 - img.height){
		cP_fbo.begin();
		GLubyte RGB[3];
		float x = cP_fbo.getWidth() - (ofGetWidth() - mouseX - 20);
		float y = cP_fbo.getHeight() - (ofGetHeight() - mouseY - 20);

		glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &RGB[0]);
		if(colorPickerIndex == 0)
			color1 = ofColor(RGB[0], RGB[1], RGB[2], 255);
		else
			if(colorPickerIndex == 1)
				color2 = ofColor(RGB[0], RGB[1], RGB[2], 255);	
			else
				color3 = ofColor(RGB[0], RGB[1], RGB[2], 255);
		cP_fbo.end();
	}

	//Check click on first picker
	if(mouseX < (ofGetWidth() - 20 - img.getWidth() + 2) + img.getWidth()/3 &&
		mouseX > ofGetWidth() - 20 - img.getWidth() + 2 &&
		mouseY < ofGetHeight() - 20 - cP_fbo.getHeight() + 2 + rectHeight &&
		mouseY > ofGetHeight() - 20 - cP_fbo.getHeight() + 2){
			colorPickerIndex = 0;
			cout << "Clicked on left picker!" << endl;
	}

	//Check click on second picker
	if(mouseX < ofGetWidth() - 20 - 2 &&
		mouseX > ofGetWidth() - 20 - 2 - img.getWidth()/3 &&
		mouseY < ofGetHeight() - 20 - cP_fbo.getHeight() + 2 + rectHeight &&
		mouseY > ofGetHeight() - 20 - cP_fbo.getHeight() + 2){
			colorPickerIndex = 1;
			cout << "Clicked on rigth picker!" << endl;
	}

	//Check click on second picker
	if(mouseX < ofGetWidth() - 20 - img.getWidth() + img.getWidth()/3 + 2 + img.getWidth()/3 &&
		mouseX > ofGetWidth() - 20 - img.getWidth() + img.getWidth()/3 + 2 &&
		mouseY < ofGetHeight() - 20 - cP_fbo.getHeight() + 2 + rectHeight &&
		mouseY > ofGetHeight() - 20 - cP_fbo.getHeight() + 2){
			colorPickerIndex = 2;
			cout << "Clicked on middle picker!" << endl;
	}
}

ofColor ColorPicker::getColor1(){
	return color1;
}

ofColor ColorPicker::getColor2(){
	return color2;
}

ofColor ColorPicker::getColor3(){
	return color3;
}



/* ----------------------------------------------------------
		 _____         _      ___              
		|_   _|       | |    / _ \             
		  | | ___  ___| |_  / /_\ \_ __  _ __  
		  | |/ _ \/ __| __| |  _  | '_ \| '_ \ 
		  | |  __/\__ \ |_  | | | | |_) | |_) |
		  \_/\___||___/\__| \_| |_/ .__/| .__/ 
								  | |   | |    
								  |_|   |_|    
--------------------------------------------------------------*/
Params param;				//Definition of a global variable for parameters
ColorPicker colorPicker;	//Definition of a global variable for color picker

//Since 'vector' adds and removes elements to its ends slowly, 
// we'll use a similar class, 'deque', which represents a dynamic array that changes its size during runtime 
deque<Particle> particles;	//Particles

ofFbo fbo;					//Offscreen buffer for trails

float history;				//Control parameter for trails between [0, 1] --> 0.0 - trails disappear immediately; 1.0 - trails are infinite.
float time0;				//Time value for computing dt

void testApp::setup(){
	 ofSetFrameRate(60);

    int w = ofGetWindowWidth(); 
    int h = ofGetWindowHeight();
	fbo.allocate(w, h, GL_RGB32F_ARB);

	//Fill buffer with background color
	fbo.begin();
	ofBackgroundGradient(ofColor::gray,ofColor(colorPicker.getColor1()), OF_GRADIENT_CIRCULAR);
	fbo.end();

	//Set up parameters
	param.setup();
	history = 0.7;

	//Set up color picker
	colorPicker.setup();

	time0 = ofGetElapsedTimef();
	destX = ofGetWidth()/2;
	destY = -ofGetHeight()/2;
	destY = 1;

	//Set up interface
	interf.setGUI1(&param.force, &param.size, &param.lifeTime, &history, &param.rotate, &param.eRad, &param.bornRate, &param.velRad, &param.Zintensity);
	interf.setGUI2();
	interf.setGUI3();
	interf.setup();

	// ----------------------------------------

	//NiTE
	niteRc = nite::NiTE::initialize();
	if (niteRc != nite::STATUS_OK)	{
		printf("NiTE initialization failed\n");
	}

	niteRc = userTracker.create();
	if (niteRc != nite::STATUS_OK)	{
		printf("Couldn't create user tracker\n");
	}
	printf("\nStart moving around to get detected...\n");

	drawSkeleton = false;
}
 
void testApp::update(){
    //Compute dt
	float time = ofGetElapsedTimef();
	float dt = ofClamp(time - time0, 0, 0.1);
	time0 = time;

	//Delete inactive particles
	int i = 0;
	while(i < particles.size()){
		if (!particles[i].live){
			particles.erase(particles.begin()+i);
		}
		else
			i++;
	}

	//Born new particles
	param.bornCount += dt * param.bornRate;		//Update bornCount value
	if(param.bornCount >= 1){
		int bornN = int (param.bornCount);		//How many particles born
		param.bornCount -= bornN;				//Correct bornCount value
		for (int i = 0; i < bornN; i++)
		{
			Particle newP;
			newP.setup();
			particles.push_back(newP);
		}
	}

	
	//NiTE
	niteRc = userTracker.readFrame(&userTrackerFrame);
	if(niteRc != nite::STATUS_OK)
		printf("Get next frame failed\n");

	const nite::Array<nite::UserData>& users = userTrackerFrame.getUsers();
	for (int i = 0; i < users.getSize(); i++)
	{
		const nite::UserData& user = users[i];
		updateUserState(user,userTrackerFrame.getTimestamp());
		
		if (user.isNew())
			userTracker.startSkeletonTracking(user.getId());
		else
			if (user.getSkeleton().getState() == nite::SKELETON_TRACKED)
			{
				const nite::SkeletonJoint& head = user.getSkeleton().getJoint(nite::JOINT_HEAD);
				const nite::SkeletonJoint& neck = user.getSkeleton().getJoint(nite::JOINT_NECK);
				const nite::SkeletonJoint& handL = user.getSkeleton().getJoint(nite::JOINT_LEFT_HAND);
				const nite::SkeletonJoint& elbowL = user.getSkeleton().getJoint(nite::JOINT_LEFT_ELBOW);
				const nite::SkeletonJoint& handR = user.getSkeleton().getJoint(nite::JOINT_RIGHT_HAND);
				const nite::SkeletonJoint& elbowR = user.getSkeleton().getJoint(nite::JOINT_RIGHT_ELBOW);
				const nite::SkeletonJoint& shoulderL = user.getSkeleton().getJoint(nite::JOINT_LEFT_SHOULDER);
				const nite::SkeletonJoint& shoulderR = user.getSkeleton().getJoint(nite::JOINT_RIGHT_SHOULDER);
				const nite::SkeletonJoint& torso = user.getSkeleton().getJoint(nite::JOINT_TORSO);
				const nite::SkeletonJoint& hipL = user.getSkeleton().getJoint(nite::JOINT_LEFT_HIP);
				const nite::SkeletonJoint& hipR = user.getSkeleton().getJoint(nite::JOINT_RIGHT_HIP);
				const nite::SkeletonJoint& kneeL = user.getSkeleton().getJoint(nite::JOINT_LEFT_KNEE);
				const nite::SkeletonJoint& kneeR = user.getSkeleton().getJoint(nite::JOINT_RIGHT_KNEE);
				const nite::SkeletonJoint& footL = user.getSkeleton().getJoint(nite::JOINT_LEFT_FOOT);
				const nite::SkeletonJoint& footR = user.getSkeleton().getJoint(nite::JOINT_RIGHT_FOOT);
				
				const nite::Point3f center = user.getCenterOfMass();

		/*0*/	headPos = ofPoint(head.getPosition().x + ofGetWidth()/2, -(head.getPosition().y - ofGetHeight()/2), -head.getPosition().z/param.Zintensity);
		/*1*/	neckPos = ofPoint(neck.getPosition().x + ofGetWidth()/2, -(neck.getPosition().y - ofGetHeight()/2), -neck.getPosition().z/param.Zintensity);
		/*2*/	handLPos = ofPoint(handL.getPosition().x + ofGetWidth()/2, -(handL.getPosition().y - ofGetHeight()/2), -handL.getPosition().z/param.Zintensity);
		/*3*/	elbowLPos = ofPoint(elbowL.getPosition().x + ofGetWidth()/2, -(elbowL.getPosition().y - ofGetHeight()/2), -elbowL.getPosition().z/param.Zintensity);
		/*4*/	handRPos = ofPoint(handR.getPosition().x + ofGetWidth()/2, -(handR.getPosition().y - ofGetHeight()/2), -handR.getPosition().z/param.Zintensity);
		/*5*/	elbowRPos = ofPoint(elbowR.getPosition().x + ofGetWidth()/2, -(elbowR.getPosition().y - ofGetHeight()/2), -elbowR.getPosition().z/param.Zintensity);
		/*6*/	shoulderLPos = ofPoint(shoulderL.getPosition().x + ofGetWidth()/2, -(shoulderL.getPosition().y - ofGetHeight()/2), -shoulderL.getPosition().z/param.Zintensity);
		/*7*/	shoulderRPos = ofPoint(shoulderR.getPosition().x + ofGetWidth()/2, -(shoulderR.getPosition().y - ofGetHeight()/2), -shoulderR.getPosition().z/param.Zintensity);
		/*8*/	torsoPos = ofPoint(torso.getPosition().x + ofGetWidth()/2, -(torso.getPosition().y - ofGetHeight()/2), -torso.getPosition().z/param.Zintensity);
		/*9*/	hipLPos = ofPoint(hipL.getPosition().x + ofGetWidth()/2, -(hipL.getPosition().y - ofGetHeight()/2), -hipL.getPosition().z/param.Zintensity);
		/*10*/	hipRPos = ofPoint(hipR.getPosition().x + ofGetWidth()/2, -(hipR.getPosition().y - ofGetHeight()/2), -hipR.getPosition().z/param.Zintensity);
		/*11*/	kneeLPos = ofPoint(kneeL.getPosition().x + ofGetWidth()/2, -(kneeL.getPosition().y - ofGetHeight()/2), -kneeL.getPosition().z/param.Zintensity);
		/*12*/	kneeRPos = ofPoint(kneeR.getPosition().x + ofGetWidth()/2, -(kneeR.getPosition().y - ofGetHeight()/2), -kneeR.getPosition().z/param.Zintensity);
		/*13*/	footLPos = ofPoint(footL.getPosition().x + ofGetWidth()/2, -(footL.getPosition().y - ofGetHeight()/2), -footL.getPosition().z/param.Zintensity);
		/*14*/	footRPos = ofPoint(footR.getPosition().x + ofGetWidth()/2, -(footR.getPosition().y - ofGetHeight()/2), -footR.getPosition().z/param.Zintensity);

				centerPos = ofPoint(center.x + ofGetWidth()/2, -(center.y - ofGetHeight()/2), center.z);

				
				//Update the particles
				for (int i = 0; i < particles.size(); i++){
					switch (particles[i].getTargetJoint()){
					case 0:
						destX = headPos.x;
						destY = -headPos.y ;
						destZ = headPos.z;
						break;
					case 1: 
						destX = neckPos.x;
						destY = -neckPos.y ;
						destZ = neckPos.z;
						break;
					case 2:
						destX = handLPos.x;
						destY = -handLPos.y;
						destZ = handLPos.z;
						break;
					case 3: 
						destX = elbowLPos.x;
						destY = -elbowLPos.y;
						destZ = elbowLPos.z;
						break;
					case 4:
						destX = handRPos.x;
						destY = -handRPos.y;
						destZ = handRPos.z;
						break;
					case 5: 
						destX = elbowRPos.x;
						destY = -elbowRPos.y;
						destZ = elbowRPos.z;
						break;
					case 6:
						destX = shoulderLPos.x;
						destY = -shoulderLPos.y;
						destZ = shoulderLPos.z;
						break;
					case 7: 
						destX = shoulderRPos.x;
						destY = -shoulderRPos.y;
						destZ = shoulderRPos.z;
						break;
					case 8:
						destX = torsoPos.x;
						destY = -torsoPos.y;
						destZ = torsoPos.z;
						break;
					case 9:
						destX = hipLPos.x;
						destY = -hipLPos.y;
						destZ = hipLPos.z;
						break;
					case 10:
						destX = hipRPos.x;
						destY = -hipRPos.y;
						destZ = hipRPos.z;
						break;
					case 11: 
						destX = kneeLPos.x;
						destY = -kneeLPos.y;
						destZ = kneeLPos.z;
						break;
					case 12:
						destX = kneeRPos.x;
						destY = -kneeRPos.y;
						destZ = kneeRPos.z;
						break;
					case 13: 
						destX = footLPos.x;
						destY = -footLPos.y;
						destZ = footLPos.z;
						break;
					case 14:
						destX = footRPos.x;
						destY = -footRPos.y;
						destZ = footRPos.z;
						break;
					}
					particles[i].update(dt, destX, destY, destZ);
				}
			}
			else
			{
				destX = 0;
				destY = 0;
				destZ = 0;
				particles[i].update(dt, destX, destY, destZ);
			}
	}
	//------------------------------------------------

	//Update color picker
	colorPicker.update();
}
 
void testApp::draw(){
	ofBackgroundGradient(ofColor::gray,ofColor(colorPicker.getColor1()), OF_GRADIENT_CIRCULAR);
	

	//1. Drawing to buffer
	fbo.begin();
	
	//Draw semi-transparent white rectangle to slightly clearing a buffer (depends on history value)
	ofEnableAlphaBlending();		//Enbale transparency
	float alpha = (1 - history) * 255;
	//ofSetColor(255, 255, 255, alpha);
	ofSetColor(colorPicker.getColor1().r, colorPicker.getColor1().g, colorPicker.getColor1().b, alpha);
	ofFill();
	ofRect(0, 0, ofGetScreenWidth(), ofGetScreenHeight());
	ofDisableAlphaBlending();		//Disabale transparency

	//Draw the particle
	ofFill();
	for (int i = 0; i < particles.size(); i++){
		particles[i].draw(colorPicker.getColor3(), colorPicker.getColor2());
	}
	fbo.end();

	
	//2. Draw the buffer on the screen
	ofSetColor(255, 255, 255);
	fbo.draw(0, 0);
	
	
	//3. Draw interface on the screen
	interf.draw();
	if ( drawInterface ) {	
		colorPicker.draw();
	}

	if(drawSkeleton){
		ofSetColor(ofColor::green);
		ofRect(headPos.x, headPos.y, 10, 10);
		ofRect(neckPos.x, neckPos.y, 10, 10);
		ofRect(handLPos.x, handLPos.y, 10, 10);
		ofRect(elbowLPos.x, elbowLPos.y, 10, 10);
		ofRect(handRPos.x, handRPos.y, 10, 10);
		ofRect(elbowRPos.x, elbowRPos.y, 10, 10);
		ofRect(shoulderLPos.x, shoulderLPos.y, 10, 10);
		ofRect(shoulderRPos.x, shoulderRPos.y, 10, 10);
		ofRect(torsoPos.x, torsoPos.y, 10, 10);
		ofRect(hipLPos.x, hipLPos.y, 10, 10);
		ofRect(hipRPos.x, hipRPos.y, 10, 10);
		ofRect(kneeLPos.x, kneeLPos.y, 10, 10);
		ofRect(kneeRPos.x, kneeRPos.y, 10, 10);
		ofRect(footLPos.x, footLPos.y, 10, 10);
		ofRect(footRPos.x, footRPos.y, 10, 10);

		ofSetColor(ofColor::green);
		ofLine(ofPoint(headPos.x, headPos.y), ofPoint(neckPos.x, neckPos.y));
		ofLine(ofPoint(neckPos.x, neckPos.y), ofPoint(shoulderLPos.x, shoulderLPos.y));
		ofLine(ofPoint(neckPos.x, neckPos.y), ofPoint(shoulderRPos.x, shoulderRPos.y));
		ofLine(ofPoint(shoulderLPos.x, shoulderLPos.y), ofPoint(elbowLPos.x, elbowLPos.y));
		ofLine(ofPoint(elbowLPos.x, elbowLPos.y), ofPoint(handLPos.x, handLPos.y));
		ofLine(ofPoint(shoulderRPos.x, shoulderRPos.y), ofPoint(elbowRPos.x, elbowRPos.y));
		ofLine(ofPoint(elbowRPos.x, elbowRPos.y), ofPoint(handRPos.x, handRPos.y));
		ofLine(ofPoint(shoulderLPos.x, shoulderLPos.y), ofPoint(torsoPos.x, torsoPos.y));
		ofLine(ofPoint(shoulderRPos.x, shoulderRPos.y), ofPoint(torsoPos.x, torsoPos.y));
		ofLine(ofPoint(torsoPos.x, torsoPos.y), ofPoint(hipLPos.x, hipLPos.y));
		ofLine(ofPoint(torsoPos.x, torsoPos.y), ofPoint(hipRPos.x, hipRPos.y));
		ofLine(ofPoint(hipLPos.x, hipLPos.y), ofPoint(kneeLPos.x, kneeLPos.y));
		ofLine(ofPoint(hipRPos.x, hipRPos.y), ofPoint(kneeRPos.x, kneeRPos.y));
		ofLine(ofPoint(kneeLPos.x, kneeLPos.y), ofPoint(footLPos.x, footLPos.y));
		ofLine(ofPoint(kneeRPos.x, kneeRPos.y), ofPoint(footRPos.x, footRPos.y));
	}
}

void testApp::keyPressed(int key){
	interf.keyPressed(key);

	if(key == ' '){
		for (int i = 0; i < particles.size(); i++){
			particles[i].pos.x = ofRandom(ofGetWindowWidth());
			particles[i].pos.y = ofRandom(ofGetWindowHeight());
		}
	}

	if ( key == OF_KEY_RETURN ){	//Hide/show GUI
		drawInterface = !drawInterface;
	}

	if ( key == OF_KEY_F1 ){		//Grab the screen image to file
		ofImage image;	
		image.grabScreen( 0, 0, ofGetWidth(), ofGetHeight() );	

		//Select random file name
		int n = ofRandom( 0, 1000 );
		string fileName = "screen" + ofToString( n ) + ".png";

		image.saveImage( "Screenshots/" + fileName );	
	}

	if(key == OF_KEY_CONTROL){
		for (int i = 0; i < particles.size(); i++)
		{
			if(!particles[i].tracking)
			particles[i].tracking = true;
		else
			particles[i].tracking = false;
		}
	}

	if(key == OF_KEY_ESC){
		nite::NiTE::shutdown();
		exit();
	}

	if(key == 'h')
		drawSkeleton = !drawSkeleton;
}

void testApp::keyReleased(int key){

}

void testApp::mouseMoved(int x, int y){

}

void testApp::mouseDragged(int x, int y, int button){
	if ( drawInterface ) {
		colorPicker.mouseDragged(mouseX, mouseY);
	}
}

void testApp::mousePressed(int x, int y, int button){
}

void testApp::mouseReleased(int x, int y, int button){
}

void testApp::windowResized(int w, int h){
	fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGB32F_ARB);
	param.eCenter = ofPoint(ofGetWidth()/2, ofGetHeight()/2);
}

void testApp::gotMessage(ofMessage msg){

}

void testApp::dragEvent(ofDragInfo dragInfo){ 

}

void testApp::updateUserState(const nite::UserData& user, unsigned long long ts)
{
	if (user.isNew())
		USER_MESSAGE("New")
	else if (user.isVisible() && !g_visibleUsers[user.getId()])
		USER_MESSAGE("Visible")
	else if (!user.isVisible() && g_visibleUsers[user.getId()])
		USER_MESSAGE("Out of Scene")
	else if (user.isLost())
		USER_MESSAGE("Lost")

	g_visibleUsers[user.getId()] = user.isVisible();


	if(g_skeletonStates[user.getId()] != user.getSkeleton().getState())
	{
		switch(g_skeletonStates[user.getId()] = user.getSkeleton().getState())
		{
		case nite::SKELETON_NONE:
			USER_MESSAGE("Stopped tracking.")
			break;
		case nite::SKELETON_CALIBRATING:
			USER_MESSAGE("Calibrating...")
			break;
		case nite::SKELETON_TRACKED:
			USER_MESSAGE("Tracking!")
			break;
		case nite::SKELETON_CALIBRATION_ERROR_NOT_IN_POSE:
		case nite::SKELETON_CALIBRATION_ERROR_HANDS:
		case nite::SKELETON_CALIBRATION_ERROR_LEGS:
		case nite::SKELETON_CALIBRATION_ERROR_HEAD:
		case nite::SKELETON_CALIBRATION_ERROR_TORSO:
			USER_MESSAGE("Calibration Failed... :-|")
			break;
		}
	}
}

