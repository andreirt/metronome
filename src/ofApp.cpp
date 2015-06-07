#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    //this->grayscale = new GrayscaleSequence();

    this->timelapse = new Timelapse("ampulheta_");
    this->metronome = new Metronome( this->timelapse, 0, 0, 0, ofGetWidth(), ofGetHeight(), 600 );

    ofSetFrameRate(60);
    ofBackground(0, 0, 0);
}

//--------------------------------------------------------------
void ofApp::update(){
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
