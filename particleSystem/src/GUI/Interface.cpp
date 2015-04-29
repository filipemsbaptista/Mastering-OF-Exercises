#include "Interface.h"

void Interface::setup(){

	gui1->loadSettings("gui1Settings.xml");
	gui2->loadSettings("gui2Settings.xml");
	gui3->loadSettings("gui3Settings.xml");
}

void Interface::update(){

}

void Interface::draw(){

}

void Interface::setGUI1(float *force, float *size, float *lifeTime, float *history, float *rotate, float *eRad, float *bornRate, float *velRad, int *Zintensity){
	gui1 = new ofxUISuperCanvas("PARAMETERS:");		//Creates a canvas at (0,0) using the default width	
	gui1->setDrawWidgetPadding(true);
	gui1->setPosition(5, 5);
	
	//Add widgets
	gui1->addSpacer();
    gui1->addLabel("Press 'ENTER' to Hide GUIs", OFX_UI_FONT_SMALL);
	gui1->addLabel("Press 'r' to reset GUI position", OFX_UI_FONT_SMALL);

	gui1->addLabel("");
	gui1->addLabel("PARTICLES");
	
	sP.force = force;
	sP.size = size;
	sP.lifeTime = lifeTime;
	sP.history = history;
	sP.rotate = rotate;
	sP.eRad = eRad;
	sP.bornRate = bornRate;
	sP.velRad = velRad;
	sP.Zintesity = Zintensity;
	
	gui1->addSlider("Attraction Force", 0.0, 0.5, *sP.force)->setTriggerType(OFX_UI_TRIGGER_ALL);
	gui1->addSlider("Size", 0.0, 30.0, *sP.size)->setTriggerType(OFX_UI_TRIGGER_ALL);
	gui1->addSlider("Life Time", 0.0, 120.0, *sP.lifeTime)->setTriggerType(OFX_UI_TRIGGER_ALL);
	gui1->addSlider("History", 0.0, 1.0, *sP.history)->setTriggerType(OFX_UI_TRIGGER_ALL);
	gui1->addSlider("Rotation", -500, 500, *sP.rotate)->setTriggerType(OFX_UI_TRIGGER_ALL);
	gui1->addSlider("Z Intesity", 0, 5, *sP.Zintesity)->setTriggerType(OFX_UI_TRIGGER_ALL);

	gui1->addLabel("");
	gui1->addLabel("");

    gui1->addLabel("EMITTER");
	gui1->addSlider("Radius", 0.0, 500.0, *sP.eRad)->setTriggerType(OFX_UI_TRIGGER_ALL);
	gui1->addSlider("Particles Rate", 0.0, 500.0, *sP.bornRate)->setTriggerType(OFX_UI_TRIGGER_ALL);
	gui1->addSlider("Initial Velocity", 0.0, 400.0, *sP.velRad)->setTriggerType(OFX_UI_TRIGGER_ALL);
	gui1->addLabel("");

	gui1->autoSizeToFitWidgets(); 
	ofAddListener(gui1->newGUIEvent, this, &Interface::guiEvent); 
}

void Interface::setGUI2(){
	gui2 = new ofxUISuperCanvas("SHORTCUT KEYS:");		//Creates a canvas at (0,0) using the default width	
	gui2->setDrawWidgetPadding(true);
	gui2->setPosition(5, ofGetHeight() - 170 - 5);

	gui2->addSpacer();
	gui2->addLabel("CTRL - Tracking On/Off", OFX_UI_FONT_SMALL);
	gui2->addLabel("",1);
	string textString = "SPACE - Randomly reset particles position\n";
	gui2->addTextArea("textarea", textString, OFX_UI_FONT_SMALL);
		gui2->addLabel("",1);
	gui2->addLabel("H - Show skeletonr", OFX_UI_FONT_SMALL);
	gui2->addLabel("",1);
	gui2->addLabel("F1 - Printscreen", OFX_UI_FONT_SMALL);

	gui2->autoSizeToFitWidgets(); 
	ofAddListener(gui2->newGUIEvent, this, &Interface::guiEvent); 
}

void Interface::setGUI3(){
	gui3 = new ofxUISuperCanvas("");		//Creates a canvas at (0,0) using the default width	
	gui3->setDrawWidgetPadding(true);
	gui3->setPosition(ofGetWidth() - gui3->getGlobalCanvasWidth() - 5, 5);

	gui3->addSpacer();
    gui3->addFPS();

	gui3->autoSizeToFitWidgets(); 
	ofAddListener(gui3->newGUIEvent, this, &Interface::guiEvent); 
}

void Interface::exit(){
	gui1->saveSettings("gui1Settings.xml");     
	gui2->saveSettings("gui2Settings.xml");     
	gui3->saveSettings("gui3Settings.xml");     
    delete gui1;
	delete gui2;
	delete gui3;
}

void Interface::guiEvent(ofxUIEventArgs &e){
	string name = e.getName();
	cout << "got event from: " << name << endl;
	
	ofxUISlider *slider = e.getSlider();    
	if(slider->getName() == "Attraction Force"){
		*sP.force = slider->getScaledValue();
	}
	else
		if(slider->getName() == "Size"){
			*sP.size= slider->getScaledValue();
		}
		else
			if(slider->getName() == "Life Time"){
				*sP.lifeTime= slider->getScaledValue();
			}
			else
				if(slider->getName() == "History"){
					*sP.history = slider->getScaledValue();
				}
				else
					if(slider->getName() == "Rotation"){
						*sP.rotate = slider->getScaledValue();
					}
					else
						if(slider->getName() == "Radius"){
							*sP.eRad = slider->getScaledValue();
						}
						else
							if(slider->getName() == "Particles Rate"){
								*sP.bornRate = slider->getScaledValue();
							}
							else
								if(slider->getName() == "Initial Velocity"){
									*sP.velRad = slider->getScaledValue();
								}
}

void Interface::keyPressed(int key){
	switch (key){
	case OF_KEY_RETURN:
		gui1->toggleVisible();
		gui2->toggleVisible();
		gui3->toggleVisible();
		break;

	case 'r':
		gui1->setPosition(5, 5);
		gui2->setPosition(5, ofGetHeight() - 170 - 5);
		gui3->setPosition(ofGetWidth() - gui3->getGlobalCanvasWidth() - 5, 5);
		break;

    case '1':
        gui1->toggleVisible();
        break;
            
	case '2':
		gui2->toggleVisible();
        break;

	case '3':
		gui3->toggleVisible();
        break;

	default:
		break;
	}
}