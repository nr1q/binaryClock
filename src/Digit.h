#pragma once

#include "ofMain.h"

class Digit
{
    public:
        Digit ();
        Digit (unsigned int);
        ~Digit ();

        void update ();
        void draw ();
        void setStatus (bool);
        void setStatus (char);
        void setColor (ofColor);
        void setPosition (ofVec2f);
        void setSize (unsigned int);

    private:
        bool isOn;
        ofColor color;
        ofVec2f position;
        ofVec2f newPosition;
        unsigned int size;
};
