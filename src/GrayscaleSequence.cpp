#include "GrayscaleSequence.h"
#include "ofMain.h"

GrayscaleSequence::GrayscaleSequence()
{
    //ctor
}

GrayscaleSequence::~GrayscaleSequence()
{
    //dtor
}

void GrayscaleSequence::draw( float time, float x, float y, float width, float height )
{
    ofSetColor( ofColor( time* 255, time*255, time*255) );
    ofRect( x, y, width, height);
}
