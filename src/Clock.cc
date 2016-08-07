#include "Clock.h"

Clock::Clock() : h(0), m(0), s(0)
{
    bVerbose      = false;
    bSingleColumn = false;
    position.set(100, 200);
    textColor.setHex(0xffffff);
    font.load("font/andalemono.ttf", 22);
}

Clock::~Clock()
{
    // code from graffitiAnalysis
    //for (size_t i = 0; i < digitss.size(); i++) {
        //delete digitss[i];
    //}
}

//--------------------------------------------------------------
void Clock::setup()
{
    bool matrix_format[][6] = {
        {false, true, false, true, false, true},
        {false, true, true,  true, true,  true},
        {true,  true, true,  true, true,  true},
        {true,  true, true,  true, true,  true}
    };

    size_t width = sizeof(matrix_format[0]) / sizeof(bool);
    size_t height = sizeof(matrix_format) / sizeof(matrix_format[0]);

    for (size_t i = 0; i < width; ++i) {
        for (size_t j = 0; j < height; ++j) {
            if (! matrix_format[j][i])
                continue;

            Digit digit( ofVec2f(position.x + i*100, position.y + j*100) );
            digits.push_back(digit);

            // TODO Implement new in the future
            //digitss.push_back( new Digit() );
            //polys.push_back( new polyEditable() );
            //selectedId = polys.size() - 1;

            // code from graffitiAnalysis
            //polys[ selectedId ]->enable();
            //polys[ selectedId ]->setup();
        }
    }
}

//--------------------------------------------------------------
void Clock::update()
{
    int i;
    string bsu, bsd, bmu, bmd, bhu, bhd;

    s = ofGetSeconds();
    m = ofGetMinutes();
    h = ofGetHours();

    bsu = toBinary( s % 10 );
    bsd = toBinary( s / 10 );
    bmu = toBinary( m % 10 );
    bmd = toBinary( m / 10 );
    bhu = toBinary( h % 10 );
    bhd = toBinary( h / 10 );

    reverse( begin(bsu), end(bsu) );
    reverse( begin(bsd), end(bsd) );
    reverse( begin(bmu), end(bmu) );
    reverse( begin(bmd), end(bmd) );
    reverse( begin(bhu), end(bhu) );
    reverse( begin(bhd), end(bhd) );

    i = digits.size() - 1;
    for (char & c : bsu) {
        if (bsu == "0") digits.at(16).setStatus('0');
        digits.at(i).setStatus(c);
        --i;
    }
    i = 15;
    for (char & c : bsd) {
        if (bsd == "0") digits.at(13).setStatus('0');
        digits.at(i).setStatus(c);
        --i;
    }

    i = 12;
    for (char & c : bmu) {
        if (bmu == "0") digits.at(9).setStatus('0');
        digits.at(i).setStatus(c);
        --i;
    }
    i = 8;
    for (char & c : bmd) {
        if (bmd == "0") digits.at(6).setStatus('0');
        digits.at(i).setStatus(c);
        --i;
    }

    i = 5;
    for (char & c : bhu) {
        if (bhu == "0") digits.at(2).setStatus('0');
        digits.at(i).setStatus(c);
        --i;
    }
    i = 1;
    for (char & c : bhd) {
        if (bhd == "0") digits.at(0).setStatus('0');
        digits.at(i).setStatus(c);
        --i;
    }
}

//--------------------------------------------------------------
void Clock::draw()
{
    char theTime[64];
    ofSetColor( textColor );

    for (size_t i = 0; i < digits.size(); ++i) {
        digits[i].draw();
    }

    sprintf(theTime, "sexagesimal: %02d:%02d:%02d", h, m, s);
    font.drawString(theTime , 100, 100 );

    //sprintf(theTime, "binary: %6s:%6s:%6s",
            //toBinary(h).c_str(),
            //toBinary(m).c_str(),
            //toBinary(s).c_str());
    //font.drawString(theTime , 100, 150 );
}

//--------------------------------------------------------------
string Clock::toBinary(int dec)
{
    string bin;

    if (dec == 0) {
        return "0";
    }

    while (dec != 0) {
        bin = (dec%2 == 0 ? "0" :"1") + bin;
        dec /= 2;
    }

    return bin;
}
