#ifndef METRONOME_H
#define METRONOME_H

#include "TimeRepresentation.h"

class Metronome
{
public:
    Metronome( TimeRepresentation* timeRepresentation, int iteration, float x, float y, float width, float height, unsigned int frames = 0 );
    virtual ~Metronome();

    void update();
    void draw();

protected:
private:
    float x;
    float y;
    float width;
    float height;
    unsigned int frames;
    TimeRepresentation* timeRepresentation;

    unsigned int iteration;
    unsigned int currentFrame;
    unsigned int direction;
    Metronome* firstHalf;
    Metronome* secondHalf;
    bool hasBeenDivided;

    static const int DIRECTION_FORWARD;
    static const int DIRECTION_BACKWARDS;
    static const int DIRECTION_STOPPED;
    static const int MAX_ITERATION;

    bool hasStopped();
};

#endif // METRONOME_H
