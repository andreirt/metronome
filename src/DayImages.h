#ifndef DAYIMAGES_H
#define DAYIMAGES_H

#include "ofMain.h"

class DayImages
{
public:
    DayImages( int year, int month, int day );
    virtual ~DayImages();

    void draw( float time, float x, float y, float width, float height );
protected:
private:
    std::vector<ofImage*> images;
    std::string prefix;

};

#endif // DAYIMAGES_H
