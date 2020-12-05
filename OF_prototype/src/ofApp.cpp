#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	// setup the serial port
	_serial.setup("COM3", 115200);
	_serial.startContinuousRead();
	ofAddListener(_serial.NEW_MESSAGE, this, &ofApp::parseSerial);
	_requestRead = false;

	// initialize gyro values
	_pitch	= 0;
	_roll	= 0;
}

//--------------------------------------------------------------
void ofApp::update() {
	if (_requestRead) {
		_serial.sendRequest();
		_requestRead = false;
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	//float circleRadius = ofLerp(ofGetViewportWidth() / 300.0f, ofGetViewportWidth() / 50.0f, 0);
	float circleRadius = (float) ofGetMouseY() / (float) ofGetViewportHeight() * (ofGetViewportWidth() / 20);
	float circleX = ofMap(_pitch, 0, 999, 0, ofGetViewportWidth());
	float circleY = ofMap(_roll, 0, 999, 0, ofGetViewportHeight());

	ofSetColor(255);
	ofDrawCircle(circleX, circleY, circleRadius);

	ofDrawBitmapString("Pitch: " + ofToString(_pitch), 5, 20);
	ofDrawBitmapString("Roll: " + ofToString(_roll), 5, 40);
	ofDrawBitmapString("Radius: " + ofToString(circleRadius), 5, 60);
}

void ofApp::parseSerial(string & message) {
	try {
		int pitch	= ofToInt(ofSplitString(message, ",")[0]);
		int roll	= ofToInt(ofSplitString(message, ",")[1]);

		_pitch	= pitch;
		_roll	= roll;
	}
	catch (exception e) {
		logError(e.what());
	}
}

void ofApp::logError(string message) {
	cout << message << "\n";
}

