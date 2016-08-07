#include "Digit.h"

//--------------------------------------------------------------
Digit::Digit () : isOn(false)
{
    position.set(0, 0);
}

//--------------------------------------------------------------
Digit::Digit (ofVec2f _position) : isOn(false)
{
    position = _position;
}

//--------------------------------------------------------------
Digit::~Digit ()
{
}

//--------------------------------------------------------------
void Digit::draw ()
{
    if (isOn)
        ofFill();
    else
        ofNoFill();

    ofDrawRectangle(position, 50, 50);
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
void Digit::setPosition (ofVec2f _pos)
{
    position.set( _pos );
}