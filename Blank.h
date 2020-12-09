#pragma once

#include "ofMain.h"
#include "FboSource.h"

class Blank : public ofx::piMapper::FboSource {
	public:
        void setup();
		void update();
		void draw();
        void setName(string);
		void reset(); 
		int startTime;
   
};
