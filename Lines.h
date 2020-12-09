#pragma once

#include "ofMain.h"
#include "FboSource.h"

class FineLine {
public: 
	ofPoint a; 
	ofPoint b; 
};

class Lines : public ofx::piMapper::FboSource {
	public:
		void reset(); 
        void setup();
		void update();
		void draw();
        void setName(string);
		void Buzzy(float x, float y, float s, float p, ofColor b); 
		void OpenBox(float x, float y, float w, float h, ofColor b);

		int startTime;
		int locX, locY; 
		int numOfXTiles, numOfYTiles;
		int spacingX, spacingY;
		int startingX, startingY;
		int startX, startY; 
		int phase; 
		int startSize; 


};
