#ifndef GRAYSCALESEQUENCE_H
#define GRAYSCALESEQUENCE_H

#include "TimeRepresentation.h"


class GrayscaleSequence : public TimeRepresentation
{
    public:
        GrayscaleSequence();
        virtual ~GrayscaleSequence();

        void draw( float time, float x, float y, float width, float height );
    protected:
    private:
};

#endif // GRAYSCALESEQUENCE_H
