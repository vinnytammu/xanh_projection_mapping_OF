#pragma once

#include "ofMain.h"
#include "FboSource.h"


class WaveLines : public ofx::piMapper::FboSource {
public:
	void shape(ofVec2f v);
	void wave(float w, float s, float p);
	void setup();
	void update();
	void draw();
	void setName(string _name);
	void reset(); 
	int startTime; 
	float SpeedDiff;
	float HeightDiff; 
	float phase;
	//vector<ofVec2f> vect; 
	//vector<ofVec2f> speed; 
	float locX, locY, locSpeed, addX, posX, speed;
	float spacingX;
	

};
