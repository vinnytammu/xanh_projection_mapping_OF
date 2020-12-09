#include "PulseLines.h"

//--------------------------------------------------------------
void PulseLines::setup() {
	// Give our source a decent name
	name = "PulseLines";

	// Allocate our FBO source, decide how big it should be
	allocate(500, 500);

	ofBackground(0);
	numOfXTiles = 8;
	//numOfYTiles = 20;

	spacingX = fbo->getWidth() / numOfXTiles; 
	//spacingY = ofGetHeight() / numOfYTiles;

	startingX = spacingX / 2;
	//startingY = spacingY / 2;
	locX = 0;
	locY = 0;

	startX = 0;
	startY = 0;
	startSize = 10;
	height = 0;
	height2 = 0;

	phase = 0;  //used to modulate movement
	speed = 1;
	speed2 = 1;

	boxW = 40; 
	boxH = 40; 
}

//--------------------------------------------------------------
void PulseLines::update() {
	phase += 4;
	buzzyUpdate();
}

void PulseLines::reset() {
	//initialise time at the start of source
	startTime = ofGetElapsedTimeMillis();
	//cout << startTime;
	
	ofClear(0); // uncomment if you want canvas to be reset on the buffer when fbo source is called again
}

void PulseLines::buzzyUpdate() {
	if (ofGetElapsedTimeMillis() - startTime < 8000) {		//first vetical pulse growth scene stops once clock hits 8.6 seconds
		height += speed;
		if (height < 0 || height > fbo->getHeight()) {		//keep growth within fbo edges 
			speed *= -1;										//moveHeight via speed var; 
		}
	} else if (ofGetElapsedTimeMillis() - startTime < 9000) {			//stop movement of the vertical pulse rects after 8 seconds
		height = fbo->getHeight();

	}
	
	if (ofGetElapsedTimeMillis() - startTime > 8100 ) {				//start growth of first horizontal pulse lines after 8 seconds //&& ofGetElapsedTimeMillis() - startTime < 20000
		if (height2 < fbo->getHeight()) {
			height2 += speed2;
			cout << "height growing";
		}
	}


	if (ofGetElapsedTimeMillis() - startTime > 20000) {
		if (boxW < fbo->getHeight()) {
			boxW += speed2;
			boxH += speed2;
		}
	}
}

//--------------------------------------------------------------
void PulseLines::draw() {
	ofPushStyle();
	ofClear(0); // remove if you never want to update the background
	float xDiff = ofMap(sin(ofDegToRad(phase)), -1, 1, -10, 10);

	if (ofGetElapsedTimeMillis() - startTime > 0) {		//start playing this scene after 10 seconds first pulse vertical lines come down
		
		for (int i = 0; i < numOfXTiles; i++) {
			startX = startingX + spacingX * i;
			startY = 0;

			ofPushMatrix();
			ofTranslate(startX, startY);
			ofColor b1 = ofColor::midnightBlue;
			ofColor b2 = ofColor::cornflowerBlue;
			ofColor bleu = b2.getLerped(b1, ofMap(i, 0, 8, 0, 1));
			Buzzy(locX, locY, startSize, height, bleu, xDiff);
			ofPopMatrix();

		}
	}


	if (ofGetElapsedTimeMillis() - startTime > 8000) {				//first horizontal pulse lines come out from the right 
		
		for (int i = 0; i < numOfXTiles; i++) {
			startX = startingX + spacingX * i;
			startY = 0;

			ofPushMatrix();
			ofTranslate(fbo->getWidth(), 0);
			ofRotateDeg(90);
			ofTranslate(startX, startY);
			ofColor b1 = ofColor::midnightBlue;
			ofColor b2 = ofColor::cornflowerBlue;
			ofColor bleu = b2.getLerped(b1, ofMap(i, 0, 8, 0, 1));
			Buzzy(locX, locY, startSize, height2, bleu, xDiff);
			ofPopMatrix();

		}
	}

	if (ofGetElapsedTimeMillis() - startTime > 16000) {				//horizontal lines pulse bigger
		xDiff = ofMap(sin(ofDegToRad(phase)), -1, 1, -20, 20);
		for (int i = 0; i < numOfXTiles; i++) {
			startX = startingX + spacingX * i;
			startY = 0;

			ofPushMatrix();
			ofTranslate(fbo->getWidth(), 0);
			ofRotateDeg(90);
			ofTranslate(startX, startY);
			ofColor b1 = ofColor::midnightBlue;
			ofColor b2 = ofColor::cornflowerBlue;
			ofColor bleu = b2.getLerped(b1, ofMap(i, 0, 8, 0, 1));
			Buzzy(locX, locY, startSize, height2, bleu, xDiff);
			ofPopMatrix();

		}
	}

	if (ofGetElapsedTimeMillis() - startTime > 18000) {
		xDiff = ofMap(sin(ofDegToRad(phase)), -1, 1, -20, 20);
		for (int i = 0; i < numOfXTiles; i++) {
			startX = startingX + spacingX * i;
			startY = 0;

			ofPushMatrix();
			ofTranslate(fbo->getWidth(), 0);
			ofRotateDeg(90);
			ofTranslate(startX, startY);
			ofColor b1 = ofColor::midnightBlue;
			ofColor b2 = ofColor::cornflowerBlue;
			ofColor bleu = b2.getLerped(b1, ofMap(i, 0, 8, 0, 1));
			Buzzy(locX, locY, startSize + xDiff, height2, bleu, xDiff);
			ofPopMatrix();
		}
	}

	if (ofGetElapsedTimeMillis() - startTime > 20000) {																			//exit and introduction to waves scene
		Box(boxW, boxH); 
		if (ofGetElapsedTimeMillis() - startTime > 26000) {
			int spacing = 10;
			ofBeginShape();
			for (int x = 0; x < fbo->getWidth(); x += spacing) {																	//multiply x by .01 to convert to decimal 
				ofColor b1 = ofColor::royalBlue;
				ofColor b2 = ofColor::orange;
				ofColor xanh2 = b2.getLerped(b1, .35);
				ofSetColor(xanh2);
				ofCurveVertex(x, fbo->getHeight() / 2 + (fbo->getHeight() * 0.3f * sin(x*0.01f + ofGetFrameNum() * 0.02f)));			//multiply iterator to a designated decimal step and add to a time modulator to then multiply to a float to make a certain sized step/also changes speed of wave animation
				ofCurveVertex(x, fbo->getHeight() / 2 + (fbo->getHeight()  * .2f * sin(x*0.01f + ofGetFrameNum() * .04f)));

			}
			ofEndShape(false);
		}
	}

	ofPopStyle();
}

void PulseLines::Buzzy(float x, float y, float s, float h, ofColor b, float d) {

	ofPushMatrix();
	ofPushStyle();

	ofSetColor(255);

	ofDrawRectangle(x, y, startSize, ofGetHeight());

	ofSetColor(b);
	//float xDiff = ofMap(sin(ofDegToRad(p)), -1, 1, -10, 10);
	ofDrawRectangle(x - d, y, s, h);
	ofDrawRectangle(x + d, y, s, h);

	ofPopStyle();
	ofPopMatrix();
}

void PulseLines::Box(float w, float h) {
	ofSetRectMode(OF_RECTMODE_CENTER);
	ofFill();
	ofSetColor(0); // fill color  
	ofDrawRectangle(fbo->getWidth() / 2, fbo->getHeight() / 2, w, h);
	ofNoFill();
	ofSetLineWidth(4);
	ofColor b1 = ofColor::midnightBlue;
	ofColor b2 = ofColor::cornflowerBlue;
	ofColor bleu = b2.getLerped(b1, .35);
	ofSetColor(bleu);
	ofDrawRectangle(fbo->getWidth() / 2, fbo->getHeight() / 2, w, h);
}