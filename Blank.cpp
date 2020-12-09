#include "Blank.h"

void Blank::setup(){
	// Give our source a decent name
    name = "Blank";

	// Allocate our FBO source, decide how big it should be
    allocate(500, 500);

  

    //if you want to draw something inside setup you need to make calls to this->beginFbo() / this->endFbo as below
    this->beginFbo();
    ofClear(0,0,0);
    this->endFbo();
}

void Blank::setName(string _name){
    name = _name;
}

// Don't do any drawing here
void Blank::update(){
    
}

void Blank::reset(){
    //initialise time at the start of source
    startTime = ofGetElapsedTimeMillis();
    //ofClear(0); // uncomment if you want canvas to be reset on the buffer when fbo source is called again
}

// No need to take care of fbo.begin() and fbo.end() here.
// All within draw() is being rendered into fbo;
void Blank::draw(){
   
}

//================================================================

