#ifndef CLOCK_H
#define CLOCK_H

#include <string>
#include <iostream>
#include "ofMain.h"
#include "Digit.h"

//enum Clock_Mode {
    //CMode_Normal  = 0x1,
    //CMode_Verbose = 0x2, // display info, numbers, arithmetic symbols
    //CMode_Columns = 0x4, // sort digits in three columns
    //CMode_Digits  = 0x8, // sort digits in six cols
//};

class Clock
{
    public:
        Clock ();
        ~Clock ();

        void setup ();
        void update ();
        void draw ();

        string toBinary (int);

    private:
        int h, m, s;
        vector<Digit> digits;

        bool bVerbose;
        bool bSingleColumn;

        ofVec2f position;
        ofColor textColor;
        ofTrueTypeFont font;
};

#endif /* ifndef CLOCK_H */
