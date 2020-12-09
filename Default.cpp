#include "Default.h"
//found similar problem on forum about curveVertex: https://forum.openframeworks.cc/t/drawing-a-curved-line/1141/3  helped with wave function 

void Default::setup(){
	// Give our source a decent name
    name = "Default";
   
	// Allocate our FBO source, decide how big it should be
    allocate(500, 500);
	phase = 0; 
	phase2 = 0;		
	height = 0;
	widthOfBar = fbo->getWidth() / 10; 
	spacing = widthOfBar; 
	speed = 2; 
	randomHeight = ofRandom(1, 20); 
	startSize = 10;
	startSize2 = 10;

	buzzySetUp(); 
	heightDiff = ofMap(sin(ofDegToRad(phase)), -1, 1, 1, fbo->getHeight());

}

//--------------------------------------------------------------
void Default::reset(){
    //reset is called optionally. if you leave it empty nothing is happening
	startTime = ofGetElapsedTimeMillis();
	//ofClear(0); // uncomment if you want canvas to be reset on the buffer when fbo source is called again
}

//--------------------------------------------------------------
void Default::setName(string _name){
    name = _name;
}

//--------------------------------------------------------------
// Don't do any drawing here 
void Default::update(){
	phase++; 
	phase2 += 4; 
	outlineUpdate();
}

//--------------------------------------------------------------
// No need to take care of fbo.begin() and fbo.end() here.
// All within draw() is being rendered into fbo;
void Default::draw() {
	ofPushStyle();
	ofClear(0); //clear the buffer
	//do it with static values
	//since the buffer is 500x500, then...
	//drawMovingRect(250, 250, 500, 500);
	//or pass it dynamic values (ie. ask the fbo how big it is)

	if (ofGetElapsedTimeMillis() - startTime > 0 && ofGetElapsedTimeMillis() - startTime < 2000) {       //start first scene after 1 seconds 14350
		ofColor b1 = ofColor::midnightBlue;
		ofColor b2 = ofColor::silver;
		xanh = b2.getLerped(b1, .35);
		outline(0, 500, 0, widthOfBar, height, xanh + height, 0, 0, 1);

	}

	if (ofGetElapsedTimeMillis() - startTime < 12400) {												//outline loses fill 
		ofNoFill();
		outline(0, 500, 0, widthOfBar, height, xanh, 0, 0, 1);
	}
		
	if (ofGetElapsedTimeMillis() - startTime > 6000) {									//wave scenes starts afer 6 seconds

		wave(fbo->getWidth(), fbo->getHeight() / 2, fbo->getHeight(), .3f, -.04f);

		if (ofGetElapsedTimeMillis() - startTime > 8000) {
			ofPushMatrix(); 
			//ofTranslate(fbo->getWidth() / 2, fbo->getHeight() / 2);											//pushes frame towards buttom and a bit out of fbo edges 
			wave(fbo->getWidth(), fbo->getHeight() / 2, fbo->getHeight(), .1f, .04f);						//wave goes in other direction at different speed 
			ofPopMatrix(); 
		}
	}

		if (ofGetElapsedTimeMillis() - startTime > 10000) {									//dual wave starts here. not using wave class because different steps to create dual wave
			int spacing = 10;
			ofBeginShape();
			for (int x = 0; x < fbo->getWidth() ; x += spacing) {
				ofSetCurveResolution(25);
				ofColor a1 = ofColor::midnightBlue;
				ofColor a2 = ofColor::blueSteel; 
				ofColor xanh = a2.getLerped(a1, .85);
				ofSetColor(xanh);
				ofCurveVertex(x, fbo->getHeight() / 2 + fbo->getHeight()/2 * 0.2f * sin(x*0.01f + ofGetFrameNum() * 0.04f));			//ofGetHeight() * float number determines height of wave

				if (ofGetElapsedTimeMillis() - startTime > 12000) {
					ofCurveVertex(x, fbo->getHeight() / 2 + fbo->getHeight() / 2 * 0.2f * sin(x*0.01f + ofGetFrameNum() * 0.06f));
				}
			}
			ofEndShape();
		}
	
	if (ofGetElapsedTimeMillis() - startTime > 12100 ) {			//start this after 12 seconds  //&& ofGetElapsedTimeMillis() - startTime < 16000   //sinVerticalBars

		ofColor b1 = ofColor::midnightBlue;
		ofColor b2 = ofColor::silver;
		float pulseBlu = ofMap(sin(ofDegToRad(phase)), -1, 1, .20, .80);
		xanh = b2.getLerped(b1, pulseBlu);
		outline(0, 500, 0, widthOfBar, height, xanh, heightDiff, 0, 1);
	}

	
	if (ofGetElapsedTimeMillis() - startTime > 16350) {       //start scene after 16.35 seconds
		ofColor b1 = ofColor::midnightBlue;
		ofColor b2 = ofColor::silver;
		xanh = b2.getLerped(b1, .35);
		int spacingZ = fbo->getWidth() / 20;
		for (int i = 0; i > -60; i -= 10 ) {
			ofPushMatrix(); 
			ofTranslate(0, 0, i * spacingZ);										//z-depth for z coordinate
			outline(0, 500, i, widthOfBar, height, xanh - i , height, 0, 1);
			ofPopMatrix(); 
		}

		if (ofGetElapsedTimeMillis() - startTime > 30550) {				//start scene after 30.35 seconds: horizontal z depth
			for (int i = 0; i > -60; i -= 10) {
				ofPushMatrix();
				ofColor b1 = ofColor::midnightBlue;
				ofColor b2 = ofColor::silver;
				xanh = b2.getLerped(b1, .35);
				ofTranslate(fbo->getWidth(), 0, i * spacingZ);
				outline(0, 500, i, widthOfBar, height, xanh - i, height, 90, 1);
				ofPopMatrix();

				ofPushMatrix();
				ofTranslate(0, 500, i * spacingZ);
				outline(0, 500, i, widthOfBar, height, xanh - i, height, -90, 1);
				ofPopMatrix();
			}
		}
	}  
	
	
	/*if (ofGetElapsedTimeMillis() - startTime > 40500) {			//SCENE SIDEBARS: start at 10.5 second mark. 
		xanh = ofColor::blueSteel;
		ofTranslate(fbo->getWidth() - 10, 0);
		//for (float i = 0; i < fbo->getWidth(); i++) {
			outline(0, 500, 0, widthOfBar, height, xanh, randomHeight, 30, 1);
		//}
	} */
	
	
	if (ofGetElapsedTimeMillis() - startTime > 45000) {		//SCENE PULSE: start playing this scene after 40 seconds 
		for (int i = 0; i < numOfXTiles; i++) {
			//startX = startingX + spacingX * i;
			//startY = 0;
			ofPushMatrix();
			//ofRotateDeg(90); 
			//ofTranslate(startX, startY);
			ofTranslate(fbo->getWidth() / 2, 0); 
			ofColor b1 = ofColor::midnightBlue;
			ofColor b2 = ofColor::cornflowerBlue;
			ofColor bleu = b2.getLerped(b1, ofMap(i, 0, 8, 0, 1));
			buzzy(startX, startY, startSize, phase2, bleu);

			if (ofGetElapsedTimeMillis() - startTime > 50000) {
				ofPushMatrix(); 
				ofTranslate(fbo->getWidth() / 3, 0);
				buzzy(startX, startY, startSize, phase2, bleu);			
				ofPopMatrix(); 
			}

			if (ofGetElapsedTimeMillis() - startTime > 55000) {
				ofPushMatrix(); 
				ofTranslate(-166, 0);
				buzzy(startX, startY, startSize, phase2, bleu);
				ofPopMatrix();
				
			}
			ofPopMatrix();
		}
	} 
	/*
	if (ofGetElapsedTimeMillis() - startTime > 60000) {
		for (int i = 0; i < numOfXTiles; i++) {
			ofPushMatrix();
			ofPushStyle();
			ofColor b1 = ofColor::midnightBlue;
			ofColor b2 = ofColor::cornflowerBlue;
			ofColor bleu = b2.getLerped(b1, ofMap(i, 0, 8, 0, 1));
			buzzy(startX, startY, startSize, phase2, bleu);
			ofTranslate(fbo->getWidth() / 2, 0);
			ofSetColor(255);
			buzzy(startX, startY, startSize2 + speed, phase2, bleu);
			ofPopStyle();
			ofPopMatrix();
		}
	}*/

	ofPopStyle();
}

//--------------------------------------------------------------
void Default::outlineUpdate() {
	height += speed;
	if (height < 0 || height > fbo->getHeight() / 2) {		//keep growth within fbo edges 
		speed *= -1;										//moveHeight via speed var; 
	}
	if (ofGetElapsedTimeMillis() - startTime > 60000) {
		startSize += speed; 
		startX -= speed;
		startY -= speed; 
	}
}

//--------------------------------------------------------------
void Default::outline(float locX, float locY, float locZ, float w, float h, ofColor c, float p, float r, float i) {
	
	for (int x = 0; x < fbo->getWidth(); x++) {					//draw rects across the fbo

		ofPushMatrix();
		ofPushStyle(); 
		ofSetLineWidth(3);
		//ofSetRectMode(m); 
		ofRotateDeg(r); 
		ofSetColor(c/(x *.2));	
		ofTranslate(x * spacing, 0);							//every tenth/fboWidth, translate the bar to create the wall of bars
		//ofDrawRectangle(0, 500, w, -h + (randomHeight * x));	//bottom bars coming up (progressive bars version)
		//ofDrawRectangle(0, 0, w, h + (randomHeight * x));		//original line for progressively higher bars
		
		ofDrawRectangle(0, 0, w, h + (p * i));
		ofDrawRectangle(locX, locY, locZ ,w, -h + (p * i));
		ofPopStyle(); 
		ofPopMatrix(); 
	}
	
}

//--------------------------------------------------------------
void Default::buzzy (float x, float y, float s, float p, ofColor b) {
	ofPushMatrix();
	ofPushStyle();
	ofSetLineWidth(3);
	ofSetColor(255);

	ofDrawRectangle(x, y, startSize, fbo->getHeight());

	ofSetColor(b);
	float xDiff = ofMap(sin(ofDegToRad(p)), -1, 1, -10, 10);
	ofDrawRectangle(x - xDiff, y, s, fbo->getHeight());
	ofDrawRectangle(x + xDiff, y, s, fbo->getHeight());

	ofPopStyle();
	ofPopMatrix();
}

//--------------------------------------------------------------
void Default::buzzySetUp() {
	numOfXTiles = 1;			//originally 8
	//numOfYTiles = 20;

	spacingX = ofGetWidth() / numOfXTiles;
	//spacingY = ofGetHeight() / numOfYTiles;

	startingX = spacingX / 2;
	//startingY = spacingY / 2;

	startX = 0;
	startY = 0;
}

//--------------------------------------------------------------
void Default::wave(float w, float f, float g, float t, float s) {
	ofPushMatrix();
	ofNoFill();

	ofBeginShape();
	ofSetLineWidth(3);
	int spacing = 10;
	for (int x = 0; x < w; x += spacing) {
		ofSetCurveResolution(255);
		ofColor a1 = ofColor::midnightBlue;
		ofColor a2 = ofColor::blueSteel;
		ofColor xanh = a2.getLerped(a1, .55);
		ofSetColor(xanh);
		ofCurveVertex(x, f + g * t * sin(x*0.01f + ofGetFrameNum() * s));			//ofGetHeight() * float number determines height of wave
	}
	ofEndShape();
	ofPopMatrix();
}

//--------------------------------------------------------------
