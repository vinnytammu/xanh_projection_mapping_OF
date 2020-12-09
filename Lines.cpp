#include "Lines.h"

void Lines::setup(){
	// Give our source a decent name
    name = "Lines";

	// Allocate our FBO source, decide how big it should be
    allocate(500, 500);

	ofBackground(0); 
	numOfXTiles = 8;
	//numOfYTiles = 20;

	spacingX = ofGetWidth() / numOfXTiles;
	//spacingY = ofGetHeight() / numOfYTiles;

	startingX = spacingX / 2;
	//startingY = spacingY / 2;
	locX = 0; 
	locY = 0; 

	startX = 0;
	startY = 0; 
	startSize = 10; 
	
	phase = 0;  //used to modulate movement

    //if you want to draw something inside setup you need to make calls to this->beginFbo() / this->endFbo as below
    //this->beginFbo();
    //ofClear(255,0,0);
    //this->endFbo();
}

void Lines::setName(string _name){
    name = _name;
}

// Don't do any drawing here
void Lines::update(){
	phase+= 4;
}

void Lines::reset() {
	//initialise time at the start of source
	startTime = ofGetElapsedTimeMillis();
	cout << startTime; 
}



// No need to take care of fbo.begin() and fbo.end() here.
// All within draw() is being rendered into fbo;
void Lines::draw(){
	ofPushStyle(); 
    ofClear(0); // remove if you never want to update the background

	if (ofGetElapsedTimeMillis() - startTime < 10000) {		//play this scene at start and ends after 10 seconds

		ofColor b1 = ofColor::blueSteel;
		ofColor b2 = ofColor::deepSkyBlue; 
		ofColor blu = b2.getLerped(b1, .5); 
		float movementX = ofMap(sin(ofDegToRad(phase)), -1, 1, fbo->getWidth() / 2, fbo->getWidth());
		
		OpenBox(0, 0, movementX, fbo->getHeight(), blu); 
	}


	if ( ofGetElapsedTimeMillis() - startTime > 10000) {		//start playing this scene after 10 seconds
		
	for (int i = 0; i < numOfXTiles; i++) {
		startX = startingX + spacingX * i;
		startY = 0;

		ofPushMatrix();
		ofTranslate(startX, startY);
		ofColor b1 = ofColor::midnightBlue;
		ofColor b2 = ofColor::cornflowerBlue;
		ofColor bleu = b2.getLerped(b1, ofMap(i, 0, 8, 0, 1));
		Buzzy(locX, locY, startSize ,phase, bleu);
		ofPopMatrix();
		
			
		}
	} 
	ofPopStyle(); 
}
	
void Lines::Buzzy(float x, float y, float s,float p, ofColor b) {

		ofPushMatrix();
		ofPushStyle();
		
		ofSetColor(255);
		
		ofDrawRectangle(x, y, startSize, ofGetHeight());
		
		ofSetColor(b);
		float xDiff = ofMap(sin(ofDegToRad(p)), -1, 1, -10, 10);
		ofDrawRectangle(x - xDiff, y, s, ofGetHeight());
		ofDrawRectangle(x + xDiff, y, s , ofGetHeight()); 

		ofPopStyle(); 
		ofPopMatrix();
	
}

void Lines::OpenBox(float x, float y, float w, float h, ofColor b ) {
	ofPushMatrix();
	ofSetColor(b); 
	ofDrawRectangle(x, y, w, h); 
	ofPopMatrix(); 
}


//================================================================

