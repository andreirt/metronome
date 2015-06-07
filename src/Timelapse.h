#ifndef TIMELAPSE_H
#define TIMELAPSE_H

#include "TimeRepresentation.h"
#include <vector>
#include "ofMain.h"

class Timelapse : public TimeRepresentation
{
public:
    Timelapse( string prefix );
    virtual ~Timelapse();

    virtual void draw( float time, float x, float y, float width, float height );
protected:
private:
    string prefix;
    vector<string> filenames;
    vector<ofImage> images;
};

#endif // TIMELAPSE_H
