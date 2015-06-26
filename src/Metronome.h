#ifndef METRONOME_H
#define METRONOME_H

#include "TimeRepresentation.h"

class Metronome
{
public:
    Metronome( TimeRepresentation* timeRepresentation, int iteration, int maxInteractions, float x, float y, float width, float height, unsigned int frames = 0 );
    virtual ~Metronome();

    void update();
    void draw();
    int getNumChildren();
    static void startCycle();
    bool hasStopped();

protected:
private:
    float x;
    float y;
    float width;
    float height;
    unsigned int frames;
    int maxInteractions;
    TimeRepresentation* timeRepresentation;

    unsigned int iteration;
    unsigned int currentFrame;
    unsigned int direction;
    Metronome* firstHalf;
    Metronome* secondHalf;
    bool hasBeenDivided;
    int id;


    static const int DIRECTION_FORWARD;
    static const int DIRECTION_BACKWARDS;
    static const int DIRECTION_STOPPED;



};

#endif // METRONOME_H
