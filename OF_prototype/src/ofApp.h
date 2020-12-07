#pragma once

#include "ofMain.h"
#include "../DrawPoint.h"
#include "ofxSimpleSerial.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp {

	public:
		void setup();
		void update();
		void draw();
  
        void clearCanvas();
        
        //Called just before the application shuts down
        void exit();
  
        float lerp(float previous, float current, float percent);
		
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
        DrawPoint previousPoint;
        
        // Gui
        ofxPanel gui;
        ofxToggle _play;
        ofxButton _clear;
        ofxToggle _activateSlider;
        
        // Slider ultrasonic distance
        int _distance;
        
        // Buttons
        // Button 1: play/pause
        bool button1Value = false;
        
        // Button 2: Clear canvas
        // Probably don't need these
        bool button2Value = false;
        bool clearCanvasBool  = false;
        
        // Button 3: Activate slider
        bool button3Value = false;
        bool activateSlider = false;
        
        // slider
        int sliderValue     = 0;
        int brushRadius     = 0;
        
};
