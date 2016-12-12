#include "Clock.h"

Clock::Clock ()
{
    s = 0;
    m = 0;
    h = 0;
    currTime = 0;
    digitSize = 50;
    digitPadding = 15;
    bVerbose = false;
    b24Hours = false;
    bConvByDigits = true;
}

Clock::~Clock()
{
    for (size_t i = 0; i < digits_ptr.size(); ++i) {
        delete digits_ptr[i];
    }
}

//--------------------------------------------------------------
void Clock::setup ()
{
    textColor.setHex(0xffffff);
    font.load("font/andalemono.ttf", 20);
}

//--------------------------------------------------------------
void Clock::update ()
{
    s = ofGetSeconds();
    m = ofGetMinutes();
    h = ofGetHours();

    if (!b24Hours) {
        h = (0==h || 12==h) ? 12 : h%12;
    }

    lastTime = currTime;
    currTime = ofGetElapsedTimeMillis() / 1000;
    oldBinaryTime = binaryTime;
    binaryTime = "";
    mtxCurrent = bConvByDigits ? mtxDigits : mtxNumber;
    unsigned int padding = mtxCurrent.height;

    if (bConvByDigits) {
        binaryTime += toBinaryStr( h/10, padding-2);
        binaryTime += toBinaryStr( h%10, padding );
        binaryTime += toBinaryStr( m/10, padding-1 );
        binaryTime += toBinaryStr( m%10, padding );
        binaryTime += toBinaryStr( s/10, padding-1 );
        binaryTime += toBinaryStr( s%10, padding );
    } else {
        binaryTime += toBinaryStr( h, padding-1 );
        binaryTime += toBinaryStr( m, padding );
        binaryTime += toBinaryStr( s, padding );
    }

    // keep the clock centered
    position.set(
            (ofGetWidth() - (mtxCurrent.width*(digitSize+digitPadding)) + digitPadding)*0.45,
            (ofGetHeight() - (mtxCurrent.height*(digitSize+digitPadding)) + digitPadding)*0.35);

    updateMatrix();
}

//--------------------------------------------------------------

/**
 * Update of the matrix array, depending on the time format
 */
void Clock::updateMatrix ()
{
    size_t digitsCount = mtxCurrent.numOnes;

    if (digits_ptr.size() != digitsCount) {
        while (digits_ptr.size() < digitsCount) {
            digits_ptr.push_back( new Digit(digitSize) );
        }
        while (digits_ptr.size() > digitsCount) {
            digits_ptr.pop_back();
        }
    }

    updateDigits();
}

/**
 * Update the digits position based on time format
 */
void Clock::updateDigits ()
{
    ofVec2f newPosition(0, 0);
    unsigned int index = 0;
    unsigned int size = digitSize + digitPadding;

    // Map of the increments from 0 to 60
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
    // 0112122312232334122323342334344512232334233434452334344534454

    if (currTime != lastTime &&
        binaryTime.length() == digits_ptr.size()
       ) {
        for (size_t i = 0; i < digits_ptr.size(); ++i) {
            digits_ptr.at(i)->setStatus( binaryTime.at(i) );
        }
    }

    for (int i = 0; i < mtxCurrent.width; ++i) {
        for (int j = 0; j < mtxCurrent.height; ++j) {
            if ('0' == mtxCurrent.format.at(i*mtxCurrent.height+j)) {
                continue;
            }

            newPosition.set(position.x+i*size, position.y+j*size);

            digits_ptr.at( index )->update();
            digits_ptr.at( index )->setPosition( newPosition );

            ++index;
        }
    }
}

//--------------------------------------------------------------
void Clock::draw ()
{
    char theTime[50];

    ofBackground(0);
    //ofSetColor(255);

    //ofPushMatrix();
    //ofPopMatrix();
    for (size_t i = 0; i < digits_ptr.size(); ++i) {
        digits_ptr[i]->draw();
    }

    if (bVerbose) {
        ofSetColor( textColor );

        sprintf(theTime, "sexagesimal: %02d:%02d:%02d", h, m, s);
        font.drawString( theTime, 20, ofGetHeight()-60 );

        unsigned int padding = mtxCurrent.height;

        if (bConvByDigits) {
            sprintf(theTime, "binary: %s %s:%s %s:%s %s",
                    toBinaryStr( h/10, padding ).c_str(),
                    toBinaryStr( h%10, padding ).c_str(),
                    toBinaryStr( m/10, padding ).c_str(),
                    toBinaryStr( m%10, padding ).c_str(),
                    toBinaryStr( s/10, padding ).c_str(),
                    toBinaryStr( s%10, padding ).c_str());
            font.drawString( theTime, 20, ofGetHeight()-25 );
        } else {
            sprintf(theTime, "binary: %s:%s:%s",
                    toBinaryStr( h, padding ).c_str(),
                    toBinaryStr( m, padding ).c_str(),
                    toBinaryStr( s, padding ).c_str());
            font.drawString( theTime, 20, ofGetHeight()-25 );
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
