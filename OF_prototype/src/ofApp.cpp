#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	// setup the serial port
	_serial.setup("COM4", 115200);
	_serial.startContinuousRead();
	ofAddListener(_serial.NEW_MESSAGE, this, &ofApp::parseSerial);
	_requestRead = false;

	// initialize gyro values
	_pitch	= 0;
	_roll	= 0;
 
    // Initialize game values, everything to false
    _play = 0;
    _activateSlider = 0;
    _mode = 0;
    
    // Initialize ultrasonic sensor value
    _distance = 0;
    
    // GUI setup
    gui.setup();
    gui.add(_play.setup("Play", false));
    gui.add(_activateSlider.setup("Activate slider", false));
    gui.add(_mode.setup("Activate mode", false));
}

//--------------------------------------------------------------
void ofApp::update() {
	if (_requestRead) {
		_serial.sendRequest();
		_requestRead = false;
	}
    
    // If the game is not set on pause, add the current cursor position to an array
    if (_play) {
    
        // Get mapped position of the cursor
        float circleX = ofMap(_pitch, 0, 999, 0, ofGetViewportWidth());
        float circleY = ofMap(_roll, 0, 999, 0, ofGetViewportHeight());
        float circleRadius = _distance;
 
        // Store current point
        DrawPoint currentPoint(circleX, circleY, circleRadius);
        _currentPoint = currentPoint;
    
        // Add current point to points array
        pointsArray.push_back(DrawPoint(circleX, circleY, circleRadius));
    }
}

//--------------------------------------------------------------
void ofApp::draw() {

    // If the game is not set on pause, draw the points stored in the array
    if (_play) {
        for (int i = 0 ; i < pointsArray.size() ; i++) {
            // Smooth out difference between points
            float currentPointX = lerp(pointsArray[i - 1].x, pointsArray[i].x, 0.2);
            float currentPointY = lerp(pointsArray[i - 1].y, pointsArray[i].y, 0.2);
            
            ofDrawCircle(currentPointX, currentPointY, pointsArray[i].radius);
        }
    }

    // Debug
	ofDrawBitmapString("Pitch: " + ofToString(_pitch), 5, 20);
	ofDrawBitmapString("Roll: " + ofToString(_roll), 5, 40);
	// ofDrawBitmapString("Radius: " + ofToString(circleRadius), 5, 60);
 
    // GUI draw
    gui.draw();
    
}

void ofApp::parseSerial(string & message) {
	try {
        // Define what each value we get from serial is
        // Each value is separated by a comma

        if (message != "Started.") {
		    int pitch	         = ofToInt(ofSplitString(message, ",")[0]);
		    int roll	         = ofToInt(ofSplitString(message, ",")[1]);
            bool playPause       = ofToBool(ofSplitString(message, ",")[2]);
            bool activateSlider  = ofToBool(ofSplitString(message, ",")[3]);
            bool mode            = ofToBool(ofSplitString(message, ",")[4]);
            int distance         = ofToInt(ofSplitString(message, ",")[5]);

		    _pitch	            = pitch;
		    _roll	            = roll;
            _play               = playPause;
            _activateSlider     = activateSlider;
            _mode               = mode;
            _distance           = distance;
        }
	}
	catch (exception e) {
		logError(e.what());
	}
}

void ofApp::logError(string message) {
	cout << message << "\n";
}

//Linear Interpolation formula for "easing" between points (or smoothing data)
float ofApp::lerp(float previous, float current, float percent)
{
	return (previous + percent * (current - previous));
}
