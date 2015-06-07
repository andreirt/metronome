#include "DayImages.h"

DayImages::DayImages( int year, int month, int day )
{

}

DayImages::~DayImages()
{
    //dtor
}

void DayImages::draw( float time, float x, float y, float width, float height )
{
    ofSetColor( ofColor( time* 255, time*255, time*255) );
    ofRect( x, y, width, height);
}

