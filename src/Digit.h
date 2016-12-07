#pragma once

#include "ofMain.h"

class Digit
{
    public:
        Digit ();
        Digit (ofVec2f);
        ~Digit ();

        void draw ();
        void setStatus (bool);
        void setStatus (char);
        void setPosition (ofVec2f);
        void setSize (unsigned int);

    private:
        bool isOn;
        ofVec2f position;
        unsigned int size;
};
