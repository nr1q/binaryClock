#pragma once

#include <string>
#include <iostream>
#include <algorithm>
#include "ofMain.h"
#include "Digit.h"

struct Matrix {
    string format;
    int width;
    int height;
    int numOnes;
};

class Clock
{
    public:
        Clock ();
        ~Clock ();

        void setup ();
        void update ();
        void updateMatrix ();
        void updateDigits ();
        void draw ();

        void toggleVerbosity ();
        void toggleConversion ();
        void toggleFormat ();
        string toBinaryStr (unsigned int, const unsigned int = 0);

    private:
        unsigned int currTime, lastTime;
        unsigned int h, m, s;

        // Matrices are read from top to bottom and left to right
        //
        //  0  1  1<--number
        //  1  1  1
        //  1  1  1  |  01 01 01<--digits
        //  1  1  1  |  01 11 11
        //  1  1  1  |  11 11 11
        //  1  1  1  |  11 11 11
        //  h  m  s  |  hh mm ss

        Matrix mtxNumber {"011111111111111111",3,6,17};
        Matrix mtxDigits {"001111110111111101111111",6,4,20};
        Matrix mtxCurrent;

        string binaryTime, oldBinaryTime, increments;
        unsigned int digitSize, digitPadding;
        vector<Digit> digits;
        vector<Digit*> digits_ptr;
        //vector<string> digits_bin;

        bool bVerbose;
        bool bConvByDigits;
        bool b24Hours;

        ofVec2f position;
        ofColor textColor;
        ofTrueTypeFont font;
};
