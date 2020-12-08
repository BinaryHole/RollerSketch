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
        vector<DrawPoint> _pointsArray;
        DrawPoint _cursor;
        DrawPoint _previousPoint;
        
        // Buttons
        // Button 1: play/pause
        bool _button1Value  = false;
        bool _isPaused      = false;
        
        // Button 2: Clear Canvas
        bool _button2Value  = false;

        // Button 3: Activate slider
        bool _button3Value      = false;
        bool _isSliderActive    = false;
        
        // Slider values (ultrasonic sensor)
        int _sliderValue     = 0;
        int _brushRadius     = 10;
        
};
