#pragma once

#include "ofMain.h"
#include "GrayscaleSequence.h"
#include "Metronome.h"
#include "Timelapse.h"
#include "ofxUI.h"

class ofApp : public ofBaseApp{

private:
    ofVideoGrabber* grabber;

    Metronome* metronome;
    GrayscaleSequence* grayscale;
    Timelapse* timelapse;

    ofxUICanvas *gui;
    ofxUICanvas *recordPanel;
    ofxUICanvas *reproductionPanel;
    ofxUICanvas *imagePanel;

    ofxUIToggle *recordToggle;
    ofxUIToggle *reproductionToggle;

    ofxUIToggle* zeroRotationToggle;
    ofxUIToggle* ninetyRotationToggle;
    ofxUIToggle* oneHundredEightyRotationToggle;
    ofxUIToggle* twoHundredSeventyRotationToggle;
    int rotations;

    ofxUIToggle* showAtStartupToggle;

    ofxUIToggle* fullScreenToggle;

    std::vector<ofxUITextInput*> textInputs;
    ofxUIDropDownList* cameraList;

    ofxUITextInput *cameraWidthTextInput;
    ofxUITextInput *cameraHeightTextInput;

    ofxUITextInput *intervalToSaveTextInput;
    int intervalToSaveImage;

    ofxUITextInput *imagePrefixTextInput;
    ofxUITextInput *cycleMaxTimeTextInput;
    ofxUITextInput *divisionsMaxNumberTextInput;

    const static string RECORD_LABEL;
    const static string CAMERA_LABEL;
    const static string IMAGE_WIDTH_LABEL;
    const static string IMAGE_HEIGHT_LABEL;
    const static string CAMERA_ROTATION_LABEL;
    const static string ZERO_DEGREES_LABEL;
    const static string NINETY_DEGREES_LABEL;
    const static string ONE_HUNDRED_EIGHTY_DEGREES_LABEL;
    const static string TWO_HUNDRED_SEVENTY_DEGREES_LABEL;
    const static string SAVE_IMAGE_LABEL;
    const static string IMAGE_PREFIX_LABEL;

    const static string REPRODUCTION_LABEL;
    const static string MAX_FRAME_TIME_LABEL;
    const static string ITERATION_NUMBER_LABEL;

    const static string GENERAL_LABEL;
    const static string FULL_SCREEN_LABEL;
    const static string SHOW_ON_START_LABEL;

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

        void guiEvent(ofxUIEventArgs &e);
        void recordPanelEvent(ofxUIEventArgs &e);
        void reproductionPanelEvent(ofxUIEventArgs &e);
		void hideConfigurationPanel();
		void showConfigurationPanel();
		void showRecordPanel();
		void showReproductionPanel();
		void unfocusAllTextInputs(ofxUITextInput* except);

};
