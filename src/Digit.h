#ifndef _DIGIT_H
#define _DIGIT_H

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

    private:
        ofVec2f position;
        bool isOn;
};

#endif /* ifndef _DIGIT_H */
