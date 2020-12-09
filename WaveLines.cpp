#include "WaveLines.h"
//sought/researched help on forum about curveVertex: https://forum.openframeworks.cc/t/drawing-a-curved-line/1141/3 simple curveVertex example in forum helped in creation of the dynamic wave I was trying to achieve

void WaveLines::wave(float w, float s, float p) {

	ofNoFill();

	int spacing = p;

	ofBeginShape();
	ofSetLineWidth(2);
	for (int x = 0; x < fbo->getWidth(); x += spacing) {
		ofColor a1 = ofColor::midnightBlue;
		ofColor a2 = ofColor::blueSteel;
		ofColor xanh = a2.getLerped(a1, .55);
		ofSetColor(xanh);
		ofCurveVertex(x, fbo->getHeight() / 2 + fbo->getHeight() * 0.3 * sin(x*0.01 + ofGetFrameNum() * 0.02));			//ofGetHeight() * float number determines height of wave
	}
	ofEndShape();

	ofBeginShape();
	//ofSetLineWidth(3);
	for (int x = 0; x < fbo->getWidth(); x += spacing) {																	//multiply x by .01 to convert to decimal 
		ofColor b1 = ofColor::royalBlue;
		ofColor b2 = ofColor::orange;
		ofColor xanh2 = b2.getLerped(b1, .35);
		ofSetColor(xanh2);
		ofCurveVertex(x, fbo->getHeight() / 2 + (fbo->getHeight() * 0.3 * sin(x*0.01 + ofGetFrameNum() * 0.02)));			//multiply iterator to a designated decimal step and add to a time modulator to then multiply to a float to make a certain sized step/also changes speed of wave animation
		ofCurveVertex(x, fbo->getHeight() / 2 + (fbo->getHeight()  * w * sin(x*0.01 + ofGetFrameNum() * s)));

	}
	ofEndShape(false);
}


//--------------------------------------------------------------
void WaveLines::setup() {
	// Give our source a decent name
	name = "WaveLines";

	// Allocate our FBO source, decide how big it should be
	allocate(500, 500);

	ofSetFrameRate(60);
	//ofBackground(255);
	phase = 0;						//reading in time

	posX = 0;
	locX = 300;
	addX = 50;
	locY = 50;
	spacingX = 50;
	locSpeed = .02;
	speed = 1; 
	int initialSize = 50;
	SpeedDiff = ofMap(sin(ofDegToRad(phase)), -1, 1, .02, .06);
	HeightDiff = ofMap(sin(ofDegToRad(phase)), -1, 1, .2, .6);
}

void WaveLines::setName(string _name) {
	name = _name;
}

void WaveLines::reset() {
	startTime = ofGetElapsedTimeMillis();
}
//--------------------------------------------------------------
void WaveLines::update() {
	phase++;
	
}

//--------------------------------------------------------------
void WaveLines::draw() {
	ofPushStyle();
	ofClear(0); // remove if you never want to update the background

	if (ofGetElapsedTimeMillis() - startTime > 0) {
		wave(.2, .04, 10);
		if (ofGetElapsedTimeMillis() - startTime > 18000) {
			wave(.2, -.04, 10);
		}
	}

	if (ofGetElapsedTimeMillis() - startTime > 6000) {
		wave(.4, .04, 5);
	}
	if (ofGetElapsedTimeMillis() - startTime > 12000) {
		wave(.6, locSpeed, 20); 
	}
	if (ofGetElapsedTimeMillis() - startTime > 18000) {
		wave(.6, SpeedDiff, 20);
	}
	if (ofGetElapsedTimeMillis() - startTime > 24000) {
		wave(.6, -SpeedDiff, 5);
	}

	ofPopStyle();
}


