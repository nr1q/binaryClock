#include "Clock.h"

Clock::Clock ()
{
    s = 0;
    m = 0;
    h = 0;
    lastTime = 0;
    currTime = 0;
    bVerbose = false;
    b24Hours = false;
    bConvByDigits = true;

    // Splitted and rotated and reversed matrix format:
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
    //int i;
    //string bsu, bsd, bmu, bmd, bhu, bhd;

    lastTime = currTime;
    currTime = ofGetElapsedTimeMillis() / 1000;

    if (currTime != lastTime) {
        updateMatrix();
    }

    s = ofGetSeconds();
    m = ofGetMinutes();
    h = b24Hours ? ofGetHours() : ofGetHours() % 12;

    //bsu = toBinaryStr( s % 10 );
    //bsd = toBinaryStr( s / 10 );
    //bmu = toBinaryStr( m % 10 );
    //bmd = toBinaryStr( m / 10 );
    //bhu = toBinaryStr( h % 10 );
    //bhd = toBinaryStr( h / 10 );

    //reverse( begin(bsu), end(bsu) );
    //reverse( begin(bsd), end(bsd) );
    //reverse( begin(bmu), end(bmu) );
    //reverse( begin(bmd), end(bmd) );
    //reverse( begin(bhu), end(bhu) );
    //reverse( begin(bhd), end(bhd) );

    //i = digits.size() - 1;
    //for (char & c : bsu) {
        //if (bsu == "0") digits.at(16).setStatus('0');
        //digits.at(i).setStatus(c);
        //--i;
    //}
    //i = 15;
    //for (char & c : bsd) {
        //if (bsd == "0") digits.at(13).setStatus('0');
        //digits.at(i).setStatus(c);
        //--i;
    //}

    //i = 12;
    //for (char & c : bmu) {
        //if (bmu == "0") digits.at(9).setStatus('0');
        //digits.at(i).setStatus(c);
        //--i;
    //}
    //i = 8;
    //for (char & c : bmd) {
        //if (bmd == "0") digits.at(6).setStatus('0');
        //digits.at(i).setStatus(c);
        //--i;
    //}

    //i = 5;
    //for (char & c : bhu) {
        //if (bhu == "0") digits.at(2).setStatus('0');
        //digits.at(i).setStatus(c);
        //--i;
    //}
    //i = 1;
    //for (char & c : bhd) {
        //if (bhd == "0") digits.at(0).setStatus('0');
        //digits.at(i).setStatus(c);
        //--i;
    //}
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

    // Map of the increments
    //                              32->x............................
    //              16->x...............................x............
    //       8->x...............x...............x...............x....
    //   4->x.......x.......x.......x.......x.......x.......x.......x
    // 2->x...x...x...x...x...x...x...x...x...x...x...x...x...x...x..
    //1->x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.

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

    //for (size_t i = 0; i < digits.size(); ++i) {
        //digits[i].draw();
    //}

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
