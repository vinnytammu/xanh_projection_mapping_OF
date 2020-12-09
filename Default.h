#pragma once

#include "ofMain.h"
#include "FboSource.h"

class Default : public ofx::piMapper::FboSource {
	public:
        void setup();
		void update();
		void draw();
        void reset();
		void outline(float locX, float locY, float locZ, float w, float h, ofColor c, float p, float r, float i);
		void outlineUpdate(); 
		void buzzy(float x, float y, float s, float p, ofColor b);
		void wave(float w, float f, float g, float t, float s);
		void buzzySetUp(); 
		void buzzyUpdate();
		void halfCirWave(); 
		void halfCirWaveSetUp();
		
		
        void setName(string _name);
		float phase; 
		float phase2; 
		int startTime;

		//outline
		float widthOfBar, spacing, height, speed, randomHeight;
		float startSize;
		float startSize2;
		ofColor xanh; 
		float diff; 
		float heightDiff; 
		
		//outline

		//buzzy
		int locX, locY;
		int numOfXTiles, numOfYTiles;
		int spacingX, spacingY;
		int startingX, startingY;
		int startX, startY; 
		//buzzy

		//
		//
		
};
