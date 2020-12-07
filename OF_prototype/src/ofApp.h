#pragma once

#include "ofMain.h"
#include "../DrawPoint.h"
#include "ofxSimpleSerial.h"
#include "ofxGui.h"

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
  
  
        // Game stuff

        // 2D vector to store the on-screen points location
        vector<DrawPoint> pointsArray;
        DrawPoint _currentPoint;
        
        // Gui
        ofxPanel gui;
        ofxToggle _play;
        ofxToggle _activateSlider;
        ofxToggle _mode;
        
        // Slider ultrasonic distance
        int _distance;
        
};
