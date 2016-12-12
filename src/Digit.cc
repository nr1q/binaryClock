#include "Digit.h"

//--------------------------------------------------------------
Digit::Digit () : isOn(false)
{
    position.set(0,0);
    size = 0;
    color = ofColor(255,255);
}

//--------------------------------------------------------------
Digit::Digit (unsigned int _size) : isOn(false)
{
    position.set( ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight()) );
    size = _size;
}

//--------------------------------------------------------------
Digit::~Digit ()
{
}

//--------------------------------------------------------------
void Digit::update ()
{
    if (isOn) {
        if (color.getBrightness() < color.limit()) {
            color.setBrightness( color.getBrightness() + 20 );
        }
    } else {
        if (color.getBrightness() > 0) {
            color.setBrightness( color.getBrightness() - 20 );
        }
    }

    position.set( position.interpolate(newPosition, 0.75) );
}

//--------------------------------------------------------------
void Digit::draw ()
{
    if (isOn)
        ofFill();
    else
        ofNoFill();

    ofSetColor(color);
    ofDrawRectangle(position, size, size);
}

//--------------------------------------------------------------
void Digit::setStatus (bool _status)
{
    isOn = _status;
}

//--------------------------------------------------------------
void Digit::setStatus (char _charBin)
{
    isOn = (_charBin == '1' ? true : false);
}

//--------------------------------------------------------------
void Digit::setColor (ofColor _color)
{
    color = _color;
}

//--------------------------------------------------------------
void Digit::setPosition (ofVec2f _pos)
{
    newPosition.set( _pos );
}

//--------------------------------------------------------------
void Digit::setSize (unsigned int _size)
{
    size = _size;
}
