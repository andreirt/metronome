#include "Timelapse.h"

Timelapse::Timelapse( string prefix )
{
    this->prefix = prefix;
    this->filenames.resize(44, "");
    this->images.resize(44);

    ofDirectory dataFolder(".");
    dataFolder.allowExt("png");
    int numberOfPngFiles = dataFolder.listDir();
    for (int i = 0; i < numberOfPngFiles; i++) {

        string filename = dataFolder.getName(i);
        if (filename.find(prefix) == 0) {

            string temp = filename.substr( prefix.length(), string::npos );
            string fileNumber = temp.substr( 0, temp.length() - 4); // ".png"
            int index = ofToInt(fileNumber);
            this->filenames[ index ] = filename;

            ofLog() << "index: " << index << ", " << filename;

        }

    }
}

Timelapse::~Timelapse()
{
    //dtor
}

void Timelapse::draw( float time, float x, float y, float width, float height )
{
    int fileNumber = (int) floorf(time * 44.0);
    if (fileNumber > 43)
        fileNumber = 43;

    int offset = 0;
    int index = fileNumber;
    bool found = false;

    while ((fileNumber + offset < this->filenames.size() && fileNumber >= 0) ||
           (fileNumber - offset >= 0 && fileNumber - offset < this->filenames.size())) {

        if (fileNumber + offset < this->filenames.size() && fileNumber >= 0) {
            if (this->filenames[ fileNumber + offset ].length() > 0) {
                found = true;
                break;
            }
        }

        if ( fileNumber - offset >= 0 && fileNumber - offset < this->filenames.size()) {
            if (this->filenames[ fileNumber - offset ].length() > 0) {
                found = true;
                break;
            }
        }

        ++offset;

    }

    if (found) {

        if (!this->images[index].isAllocated()) {
            this->images[index].loadImage( this->filenames[index] );
        }

        if (this->images[index].isAllocated()) {
            this->images[index].drawSubsection( x, y, width, height, x, y );
        }

    }

}


