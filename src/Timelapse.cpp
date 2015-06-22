#include "Timelapse.h"

Timelapse::Timelapse( string prefix )
{
    this->prefix = prefix;
    this->filenames.clear();
    this->images.clear();

    ofDirectory dataFolder(".");
    dataFolder.allowExt("png");
    int numberOfPngFiles = dataFolder.listDir();
    for (int i = 0; i < numberOfPngFiles; i++) {

        string filename = dataFolder.getName(i);
        if (filename.find(prefix) == 0) {
            this->filenames.push_back(filename);
        }

    }

    // ordena a lista de nomes
    std::sort (this->filenames.begin(), this->filenames.end());

    while (this->filenames.size() > 100)
        this->filenames.pop_back();

    this->images.resize( this->filenames.size() );
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


