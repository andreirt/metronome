#include "Metronome.h"
#include <stdlib.h>

const int Metronome::DIRECTION_FORWARD = 1;
const int Metronome::DIRECTION_BACKWARDS = 2;
const int Metronome::DIRECTION_STOPPED = 3;
const int Metronome::MAX_ITERATION = 8;

Metronome::Metronome( DayImages* images, int iteration, float x, float y, float width, float height, unsigned int frames )
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->images = images;
    this->iteration = iteration;

    if (frames > 0) {
         this->frames = frames;
    }
    else {
         this->frames = 300 + (rand() % 300);
    }

    this->firstHalf = NULL;
    this->secondHalf = NULL;
    this->currentFrame = 0;
    this->direction = Metronome::DIRECTION_FORWARD;
    this->hasBeenDivided = false;
}

Metronome::~Metronome()
{
    if (this->firstHalf != NULL) {
        delete this->firstHalf;
        this->firstHalf = NULL;
    }
    if (this->secondHalf != NULL) {
        delete this->secondHalf;
        this->secondHalf = NULL;
    }
}

bool Metronome::hasStopped()
{
    return this->direction == Metronome::DIRECTION_STOPPED && this->firstHalf == NULL && this->secondHalf == NULL;
}

void Metronome::update()
{
    if (this->firstHalf == NULL && this->secondHalf == NULL) {
        if (this->direction == Metronome::DIRECTION_FORWARD) {
            ++this->currentFrame;
            if (this->currentFrame > this->frames) {
                this->currentFrame = this->frames - 1;
                this->direction = Metronome::DIRECTION_BACKWARDS;
            }
        }
        else if (this->direction == Metronome::DIRECTION_BACKWARDS) {
            --this->currentFrame;
            if (this->currentFrame == 0) {
                if (!this->hasBeenDivided && this->iteration < Metronome::MAX_ITERATION) {

                    ofLog() << "splitting: " << this->x << ", " << this->y << ", " << this->width << ", " << this->height;

                    // splits the metronome in two
                    if (this->width > this->height) {
                        this->firstHalf = new Metronome( this->images, this->iteration + 1,
                                                        this->x, this->y, this->width / 2, this->height,
                                                        this->frames );
                        this->secondHalf = new Metronome( this->images, this->iteration + 1,
                                                         this->x + this->width / 2, this->y, this->width / 2, this->height,
                                                         0 );
                    }
                    else {
                        this->firstHalf = new Metronome( this->images, this->iteration + 1,
                                                        this->x, this->y, this->width, this->height / 2,
                                                        this->frames );
                        this->secondHalf = new Metronome( this->images, this->iteration + 1,
                                                         this->x, this->y + this->height / 2, this->width, this->height / 2,
                                                         0 );
                    }

                    this->hasBeenDivided = true;

                }

                this->direction = Metronome::DIRECTION_STOPPED;
            }
        }
    }
    else {
        this->firstHalf->update();
        this->secondHalf->update();

        if (this->firstHalf->hasStopped() && this->secondHalf->hasStopped()) {
            // hora de deletá-los
            this->currentFrame = 0;
            this->direction = Metronome::DIRECTION_FORWARD;

            delete this->firstHalf;
            this->firstHalf = NULL;

            delete this->secondHalf;
            this->secondHalf = NULL;

            ofLog() << "joined: " << this->x << ", " << this->y << ", " << this->width << ", " << this->height;
        }
    }
}

void Metronome::draw()
{
    if (this->firstHalf != NULL && this->secondHalf != NULL) {
        this->firstHalf->draw();
        this->secondHalf->draw();
    }
    else {
        float time = ((float) this->currentFrame) / (float) this->frames;
        this->images->draw( time, this->x, this->y, this->width, this->height );
    }
}

