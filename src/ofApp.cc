#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofNoFill();
    ofSetFrameRate(24);

    //ofDisableAntiAliasing();

    ofLog(OF_LOG_NOTICE, "Initializing binary clock…");

    binClock.setup();
}

//--------------------------------------------------------------
void ofApp::update()
{
    //short centerX, centerY;

    //centerX = ofGetWidth()/2 - matrix.width*100/2;
    //centerY = ofGetHeight()/2 - matrix.height*100/2;

    //for (unsigned i = 0; i < digits.size(); ++i) {
        //digits[i].setOffset( ofVec2f(centerX, centerY) );

        //if (i%2 == 0)
            //digits[i].turnOn();
        //else
            //digits[i].turnOff();
    //}

    binClock.update();
}

//--------------------------------------------------------------
void ofApp::draw()
{
    ofBackground(0);
    ofSetColor(255);

    //for (unsigned i = 0; i < digits.size(); ++i)
        //digits[i].draw();

    binClock.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y )
{

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{

}
