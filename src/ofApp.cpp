#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    this->grayscale = new GrayscaleSequence();

    this->timelapse = new Timelapse("imagem_");
    this->metronome = new Metronome( this->timelapse, 0, 0, 0, ofGetWidth(), ofGetHeight(), 1000 );

    ofSetFrameRate(60);
    ofBackground(0, 0, 0);


}

static int previousMetronomes = 0;

//--------------------------------------------------------------
void ofApp::update(){
    Metronome::startCycle();
    this->metronome->update();

}

//--------------------------------------------------------------
void ofApp::draw(){
    this->metronome->draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
