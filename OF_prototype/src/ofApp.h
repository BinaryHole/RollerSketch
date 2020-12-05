#pragma once

#include "ofMain.h"
#include "ofxSimpleSerial.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		
		// gyroscope values
		int		_pitch;
		int		_roll;

		// serial stuff
		ofxSimpleSerial _serial;
		bool			_requestRead;

		void parseSerial(string & message);
		void logError(string message);
};
