#include "Clock.h"

Clock::Clock ()
{
    s = 0;
    m = 0;
    h = 0;
    currTime = 0;
    bVerbose = false;
    b24Hours = false;
    bConvByDigits = true;

    // Matrices are read from top to bottom and left to right
    //
    //  0  1  1<--number
    //  1  1  1
    //  1  1  1  |  01 01 01<--digits
    //  1  1  1  |  01 11 11
    //  1  1  1  |  11 11 11
    //  1  1  1  |  11 11 11
    //  h  m  s  |  hh mm ss
    mtxNumber.format = "011111111111111111";
    mtxNumber.width = 3;
    mtxNumber.height = 6;
    mtxNumber.numActive = count(mtxNumber.format.begin(), mtxNumber.format.end(), '1');
    mtxDigits.format = "001111110111111101111111";
    mtxDigits.width = 6;
    mtxDigits.height = 4;
    mtxDigits.numActive = count(mtxDigits.format.begin(), mtxDigits.format.end(), '1');
}

Clock::~Clock()
{
    for (size_t i = 0; i < digits_ptr.size(); i++) {
        delete digits_ptr[i];
    }
}

//--------------------------------------------------------------
void Clock::setup ()
{
    position.set(80, 100);
    textColor.setHex(0xffffff);
    font.load("font/andalemono.ttf", 20);

    updateMatrix();
}

//--------------------------------------------------------------
void Clock::update ()
{
    lastTime = currTime;
    currTime = ofGetElapsedTimeMillis() / 1000;

    updateMatrix();

    s = ofGetSeconds();
    m = ofGetMinutes();
    h = ofGetHours();

    // fix the time for 12-hour format
    if (! b24Hours) {
        h = (0 == h || 12 == h) ? 12 : h % 12;
    }

    newStatus = "";
    unsigned int padding = bConvByDigits ? mtxDigits.height : mtxNumber.height;

    if (bConvByDigits) {
        newStatus += toBinaryStr( h/10, padding-2);
        newStatus += toBinaryStr( h%10, padding );
        newStatus += toBinaryStr( m/10, padding-1 );
        newStatus += toBinaryStr( m%10, padding );
        newStatus += toBinaryStr( s/10, padding-1 );
        newStatus += toBinaryStr( s%10, padding );
    } else {
        newStatus += toBinaryStr( h, padding-1 );
        newStatus += toBinaryStr( m, padding );
        newStatus += toBinaryStr( s, padding );
    }

    //if (currTime != lastTime) {
        //std::cout << newStatus << std::endl;
    //}

    if (newStatus.length() == digits_ptr.size()) {
        for (int i = 0; i < digits_ptr.size(); ++i) {
            digits_ptr.at(i)->setStatus( newStatus.at(i) );
        }
    }

    // Map of the increments form 0 to 60
    //                                 x............................
    //                 x...............................x............
    //         x...............x...............x...............x....
    //     x.......x.......x.......x.......x.......x.......x.......x
    //   x...x...x...x...x...x...x...x...x...x...x...x...x...x...x..
    // .x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.
    //
    //                                 11111111111111111111111111111
    //                 1111111111111111................1111111111111
    //         11111111........11111111........11111111........11111
    //     1111....1111....1111....1111....1111....1111....1111....1
    //   11..11..11..11..11..11..11..11..11..11..11..11..11..11..11.
    // .1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.

}

//--------------------------------------------------------------

/**
 * Update of the matrix array, depending on the hours format
 */
void Clock::updateMatrix ()
{
    bool updateDigits = false;
    size_t digitsCount  = bConvByDigits ? mtxDigits.numActive : mtxNumber.numActive;

    if (0 == digits_ptr.size()) {
        for (size_t i = 0; i < digitsCount; ++i) {
            digits_ptr.push_back( new Digit() );
        }
        updateDigits = true;
    }


    if (digits_ptr.size() != digitsCount) {
        while (digits_ptr.size() < digitsCount) {
            digits_ptr.push_back( new Digit() );
        }
        while (digits_ptr.size() > digitsCount) {
            digits_ptr.pop_back();
        }
        updateDigits = true;
    }

    if (updateDigits) {
        size_t idxDigit = 0;
        size_t matrixWidth  = bConvByDigits ? mtxDigits.width : mtxNumber.width;
        size_t matrixHeight = bConvByDigits ? mtxDigits.height : mtxNumber.height;
        string matrix = bConvByDigits ? mtxDigits.format : mtxNumber.format;

        for (size_t i = 0; i < matrixWidth; ++i) {
            for (size_t j = 0; j < matrixHeight; ++j) {
                if ('0' == matrix.at(i*matrixHeight+j)) {
                    continue;
                }

                digits_ptr.at( idxDigit )->setPosition( ofVec2f(i*100, j*100) );

                ++idxDigit;
            }
        }
    }
}

//--------------------------------------------------------------
void Clock::draw ()
{
    char theTime[50];
    unsigned int padding;

    ofBackground(0);
    ofSetColor(255);

    for (size_t i = 0; i < digits_ptr.size(); ++i) {
        digits_ptr[i]->draw();
    }

    if (bVerbose) {
        ofSetColor( textColor );

        sprintf(theTime, "sexagesimal: %02d:%02d:%02d", h, m, s);
        font.drawString( theTime, position.x, position.y );

        padding = bConvByDigits ? mtxDigits.height : mtxNumber.height;

        if (bConvByDigits) {
            sprintf(theTime, "binary: %s %s:%s %s:%s %s",
                    toBinaryStr( h/10, padding ).c_str(),
                    toBinaryStr( h%10, padding ).c_str(),
                    toBinaryStr( m/10, padding ).c_str(),
                    toBinaryStr( m%10, padding ).c_str(),
                    toBinaryStr( s/10, padding ).c_str(),
                    toBinaryStr( s%10, padding ).c_str());
            font.drawString( theTime, position.x, position.y+60 );
        } else {
            sprintf(theTime, "binary: %s:%s:%s",
                    toBinaryStr( h, padding ).c_str(),
                    toBinaryStr( m, padding ).c_str(),
                    toBinaryStr( s, padding ).c_str());
            font.drawString( theTime, position.x, position.y+60 );
        }
    }
}

//--------------------------------------------------------------
void Clock::toggleVerbosity ()
{
    bVerbose = ! bVerbose;
}

//--------------------------------------------------------------
void Clock::toggleConversion ()
{
    bConvByDigits = ! bConvByDigits;
}

//--------------------------------------------------------------
void Clock::toggleFormat ()
{
    b24Hours = ! b24Hours;
}

//--------------------------------------------------------------
string Clock::toBinaryStr (unsigned int dec, const unsigned int padding)
{
    string bin;

    if (dec == 0) {
        bin = "0";
    } else {
        while (dec != 0) {
            bin = (dec%2 == 0 ? "0" :"1") + bin;
            dec /= 2;
        }
    }

    while (bin.size() < padding) {
        bin = "0" + bin;
    }

    return bin;
}
