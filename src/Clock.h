#ifndef _CLOCK_H
#define _CLOCK_H

#include <string>
//#include <array>
#include <iostream>
#include <algorithm>
#include "ofMain.h"
#include "Digit.h"

struct matrix {
    string format;
    int width;
    int height;
    int numActive;
};

class Clock
{
    public:
        Clock ();
        ~Clock ();

        void setup ();
        void update ();
        //void updateTime (); ???
        void updateMatrix ();
        void draw ();

        void toggleVerbosity ();
        void toggleConversion ();
        void toggleFormat ();
        string toBinaryStr (unsigned int, const unsigned int = 0);

    private:
        unsigned int currTime;
        unsigned int lastTime;
        int h, m, s;

        //string matrix;
        matrix mtxDigits;
        matrix mtxNumber;
        //unsigned int matrixWidth;
        //unsigned int matrixHeight;
        //unsigned int maxDigits;
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

#endif /* ifndef CLOCK_H */
