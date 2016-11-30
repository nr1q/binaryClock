#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofNoFill();
    //ofSetFrameRate(60);
    ofSetFrameRate(24);

    //ofDisableAntiAliasing();

    ofLog(OF_LOG_NOTICE, "Initializing binary clock…");
    ofSetWindowTitle("binaryClock");

    binClock.setup();
}

//--------------------------------------------------------------
void ofApp::update()
{
    binClock.update();
}

//--------------------------------------------------------------
void ofApp::draw()
{
    binClock.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    switch (key) {
        case 102: // f
            binClock.toggleFormat();
            break;
        case 99: // c
            binClock.toggleConversion();
            break;
        case 118: // v
            binClock.toggleVerbosity();
            break;
    }
    //std::cout << key << std::endl;
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
