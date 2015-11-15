#include "ofApp.h"

//--------------------------------------------------------------
void
ofApp::setup()
{
    ofNoFill();
    //ofSetFrameRate(24);

    ofDisableAntiAliasing();
}

//--------------------------------------------------------------
void
ofApp::update()
{

}

//--------------------------------------------------------------
void
ofApp::draw()
{
    ofBackground(0);
    ofSetColor(255);

    // Binary clock skeleton
    //ofRect(100, 100, 50, 80);
    //ofRect(100, 200, 50, 80);
    ofRect(100, 300, 50, 50);
    ofRect(100, 400, 50, 50);

    ofRect(200, 100, 50, 50);
    ofRect(200, 200, 50, 50);
    ofRect(200, 300, 50, 50);
    ofRect(200, 400, 50, 50);

    //ofRect(300, 100, 505 80);
    ofRect(300, 200, 50, 50);
    ofRect(300, 300, 50, 50);
    ofRect(300, 400, 50, 50);

    ofRect(400, 100, 50, 50);
    ofRect(400, 200, 50, 50);
    ofRect(400, 300, 50, 50);
    ofRect(400, 400, 50, 50);
}

//--------------------------------------------------------------
void
ofApp::keyPressed(int key)
{

}

//--------------------------------------------------------------
void
ofApp::keyReleased(int key)
{

}

//--------------------------------------------------------------
void
ofApp::mouseMoved(int x, int y )
{

}

//--------------------------------------------------------------
void
ofApp::mouseDragged(int x, int y, int button)
{

}

//--------------------------------------------------------------
void
ofApp::mousePressed(int x, int y, int button)
{

}

//--------------------------------------------------------------
void
ofApp::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void
ofApp::windowResized(int w, int h)
{

}

//--------------------------------------------------------------
void
ofApp::gotMessage(ofMessage msg)
{

}

//--------------------------------------------------------------
void
ofApp::dragEvent(ofDragInfo dragInfo)
{

}
