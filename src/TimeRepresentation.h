#ifndef TIMEREPRESENTATION_H
#define TIMEREPRESENTATION_H


class TimeRepresentation
{
    public:
        TimeRepresentation();
        virtual ~TimeRepresentation();

        virtual void draw( float time, float x, float y, float width, float height ) = 0;
    protected:
    private:
};

#endif // TIMEREPRESENTATION_H
