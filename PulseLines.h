#pragma once

#include "ofMain.h"
#include "FboSource.h"


class PulseLines : public ofx::piMapper::FboSource {
public:
	void setup();
	void update();
	void draw();
	void reset();

	void Buzzy(float x, float y, float s, float h, ofColor b, float d);
	void buzzyUpdate();
	void Box(float w, float h); 

	float boxW, boxH; 
	float height, height2;
	float speed;
	float speed2; 
	int startTime;
	int locX, locY;
	int numOfXTiles, numOfYTiles;
	int spacingX, spacingY;
	int startingX, startingY;
	int startX, startY;
	int phase;
	int startSize;
};
