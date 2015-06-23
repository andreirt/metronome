#include "ofApp.h"

const string ofApp::RECORD_LABEL = "Gravação";
const string ofApp::CAMERA_LABEL = "Escolha a câmera";
const string ofApp::IMAGE_WIDTH_LABEL = "Largura da câmera";
const string ofApp::IMAGE_HEIGHT_LABEL = "Altura da câmera";
const string ofApp::CAMERA_ROTATION_LABEL = "Rotação da câmera";
const string ofApp::ZERO_DEGREES_LABEL = "0 graus";
const string ofApp::NINETY_DEGREES_LABEL = "90 graus";
const string ofApp::ONE_HUNDRED_EIGHTY_DEGREES_LABEL = "180 graus";
const string ofApp::TWO_HUNDRED_SEVENTY_DEGREES_LABEL = "270 graus";
const string ofApp::SAVE_IMAGE_LABEL = "Salvar imagem a cada";
const string ofApp::IMAGE_PREFIX_LABEL = "Prefixo da imagem";

const string ofApp::REPRODUCTION_LABEL = "Reprodução";
const string ofApp::MAX_FRAME_TIME_LABEL = "Tempo máximo de cada ciclo";
const string ofApp::ITERATION_NUMBER_LABEL = "Número máximo de divisões";

const string ofApp::GENERAL_LABEL = "Opções gerais";
const string ofApp::FULL_SCREEN_LABEL = "Tela cheia";
const string ofApp::SHOW_ON_START_LABEL = "Exibir essa tela ao iniciar";



//--------------------------------------------------------------
void ofApp::setup(){
    this->grabber = new ofVideoGrabber();

    this->grayscale = new GrayscaleSequence();

    this->timelapse = new Timelapse("imagem_");
    this->metronome = new Metronome( this->timelapse, 0, 0, 0, ofGetWidth(), ofGetHeight(), 1000 );

    ofSetFrameRate(60);
    ofBackground(0, 0, 0);

    this->gui = new ofxUICanvas(0, 0, ofGetWidth(), ofGetHeight());
    this->gui->setWidgetSpacing(10);
    this->gui->setFontSize(OFX_UI_FONT_SMALL, 8);
    this->gui->setFontSize(OFX_UI_FONT_LARGE, 18);

    ofxUIColor backgroundColor = ofxUIColor::white;
    ofxUIColor fillColor = ofxUIColor::black;
    ofxUIColor fillHightlightColor = ofxUIColor::black;
    ofxUIColor outline = ofxUIColor::black;
    ofxUIColor outlineHighlight = ofxUIColor::red;
    ofxUIColor paddedColor = ofxUIColor::blue;
    ofxUIColor paddedOutlineColor = ofxUIColor::orange;

    this->gui->setUIColors( backgroundColor, outline, outlineHighlight, fillColor, fillHightlightColor, paddedColor, paddedOutlineColor );

    this->gui->addLabel("title", "Metrônomo", OFX_UI_FONT_LARGE);
    this->gui->addSpacer();

    this->recordToggle = new ofxUIToggle(ofApp::RECORD_LABEL, true, 16, 16);
    this->recordToggle->setDrawOutline(true);
    this->gui->addWidgetDown(recordToggle);

    this->reproductionToggle = new ofxUIToggle(ofApp::REPRODUCTION_LABEL, true, 16, 16);
    this->reproductionToggle->setDrawOutline(true);
    this->gui->addWidgetRight(reproductionToggle);

    this->gui->addSpacer("spacer", 1) ;

    this->recordPanel = new ofxUICanvas(0, 0, ofGetWidth(), 260);
    this->recordPanel->setFontSize(OFX_UI_FONT_SMALL, 8);
    this->recordPanel->setWidgetSpacing(10);
    this->gui->addWidgetSouthOf(this->recordPanel, "spacer");

    /*this->reproductionPanel = new ofxUICanvas(0, 0, 300, 260);
    this->reproductionPanel->setFontSize(OFX_UI_FONT_SMALL, 8);
    this->reproductionPanel->setWidgetSpacing(10);
    this->gui->addWidgetSouthOf(this->reproductionPanel, "spacer");*/


    vector<ofVideoDevice> devices = this->grabber->listDevices();
    vector<string> *cameras = new vector<string>;
    vector<ofVideoDevice>::iterator it;

    for (it = devices.begin(); it != devices.end(); it++) {
        ofVideoDevice device = *it;
        cameras->push_back(device.deviceName);
    }

    this->cameraList = this->recordPanel->addDropDownList(ofApp::CAMERA_LABEL, *cameras, 300, 10);
    this->cameraList->setAllowMultiple(false);
    this->cameraList->setDrawOutline(true);

    this->recordPanel->addWidgetDown( new ofxUILabel(170, ofApp::IMAGE_WIDTH_LABEL, OFX_UI_FONT_SMALL) );
    this->cameraWidthTextInput = new ofxUITextInput("CameraWidth", "1920", 80, 18);
    this->cameraWidthTextInput->setOnlyNumericInput(true);
    this->cameraWidthTextInput->setDrawOutline(true);
    this->cameraWidthTextInput->setDrawOutlineHighLight(true);
    this->recordPanel->addWidgetRight(this->cameraWidthTextInput);
    this->textInputs.push_back(this->cameraWidthTextInput);

    this->recordPanel->addWidgetDown( new ofxUILabel(170, ofApp::IMAGE_HEIGHT_LABEL, OFX_UI_FONT_SMALL) );
    this->cameraHeightTextInput = new ofxUITextInput("CameraHeight", "1080", 80, 18);
    this->cameraHeightTextInput->setOnlyNumericInput(true);
    this->cameraHeightTextInput->setDrawOutline(true);
    this->cameraHeightTextInput->setDrawOutlineHighLight(true);
    this->recordPanel->addWidgetRight(this->cameraHeightTextInput);
    this->textInputs.push_back(this->cameraHeightTextInput);

    this->rotations = 0;

    this->recordPanel->addLabel("Rotação da imagem", OFX_UI_FONT_SMALL);

    this->zeroRotationToggle = new ofxUIToggle(ofApp::ZERO_DEGREES_LABEL, true, 16, 16);
    this->zeroRotationToggle->setDrawOutline(true);
    this->recordPanel->addWidgetDown(this->zeroRotationToggle);

    this->ninetyRotationToggle = new ofxUIToggle(ofApp::NINETY_DEGREES_LABEL, true, 16, 16);
    this->ninetyRotationToggle->setDrawOutline(true);
    this->recordPanel->addWidgetDown(this->ninetyRotationToggle);

    this->oneHundredEightyRotationToggle = new ofxUIToggle(ofApp::ONE_HUNDRED_EIGHTY_DEGREES_LABEL, true, 16, 16);
    this->oneHundredEightyRotationToggle->setDrawOutline(true);
    this->recordPanel->addWidgetDown(this->oneHundredEightyRotationToggle);

    this->twoHundredSeventyRotationToggle = new ofxUIToggle(ofApp::TWO_HUNDRED_SEVENTY_DEGREES_LABEL, true, 16, 16);
    this->twoHundredSeventyRotationToggle->setDrawOutline(true);
    this->recordPanel->addWidgetDown(this->twoHundredSeventyRotationToggle);

    this->recordPanel->addWidgetEastOf( new ofxUILabel(170, ofApp::IMAGE_PREFIX_LABEL, OFX_UI_FONT_SMALL) , "CameraWidth" );
    this->imagePrefixTextInput = new ofxUITextInput("ImagePrefix", "imagem_", 200, 18);
    this->imagePrefixTextInput->setDrawOutline(true);
    this->imagePrefixTextInput->setDrawOutlineHighLight(true);
    this->recordPanel->addWidgetRight(this->imagePrefixTextInput);
    this->textInputs.push_back(this->imagePrefixTextInput);

    this->recordPanel->addWidgetEastOf( new ofxUILabel(180, ofApp::SAVE_IMAGE_LABEL, OFX_UI_FONT_SMALL), "CameraHeight");
    this->intervalToSaveTextInput = new ofxUITextInput("A cada", "15", 60, 18);
    this->intervalToSaveTextInput->setOnlyNumericInput(true);
    this->intervalToSaveTextInput->setDrawOutline(true);
    this->intervalToSaveTextInput->setDrawOutlineHighLight(true);
    this->recordPanel->addWidgetRight( this->intervalToSaveTextInput );
    this->recordPanel->addWidgetRight( new ofxUILabel(170, "minutos", OFX_UI_FONT_SMALL) );
    this->textInputs.push_back(this->intervalToSaveTextInput);






    ofAddListener(this->gui->newGUIEvent, this, &ofApp::guiEvent);
    ofAddListener(this->recordPanel->newGUIEvent, this, &ofApp::recordPanelEvent);
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
    if (key == OF_KEY_TAB) {
       if (this->gui->isVisible()) {
            //this->cancelConfigurationChanges();
            this->hideConfigurationPanel();
        }
        else {
            this->showConfigurationPanel();
        }
    }
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

void ofApp::guiEvent(ofxUIEventArgs &e) {
    if (e.getName() == ofApp::RECORD_LABEL) {
        this->showRecordPanel();
    } else if (e.getName() == ofApp::REPRODUCTION_LABEL) {
        this->showReproductionPanel();
    }

    if (e.getKind() == OFX_UI_WIDGET_TEXTINPUT){
        ofxUITextInput *ti = (ofxUITextInput *) e.widget;
        if (ti->getInputTriggerType() == OFX_UI_TEXTINPUT_ON_FOCUS){
            this->unfocusAllTextInputs(ti);
        }
    }
}

void ofApp::recordPanelEvent(ofxUIEventArgs &e) {

    if (e.getKind() == OFX_UI_WIDGET_TEXTINPUT){
        ofxUITextInput *ti = (ofxUITextInput *) e.widget;
        if (ti->getInputTriggerType() == OFX_UI_TEXTINPUT_ON_FOCUS){
            this->unfocusAllTextInputs(ti);
        }
    }
}

void ofApp::reproductionPanelEvent(ofxUIEventArgs &e) {

    if (e.getKind() == OFX_UI_WIDGET_TEXTINPUT){
        ofxUITextInput *ti = (ofxUITextInput *) e.widget;
        if (ti->getInputTriggerType() == OFX_UI_TEXTINPUT_ON_FOCUS){
            this->unfocusAllTextInputs(ti);
        }
    }
}

void ofApp::showRecordPanel() {
    this->reproductionToggle->setValue(false);
    this->reproductionPanel->setVisible(false);
    this->recordPanel->setVisible(true);
}

void ofApp::showReproductionPanel() {
    this->recordToggle->setValue(false);
    this->recordPanel->setVisible(false);
    this->reproductionPanel->setVisible(true);
}

void ofApp::hideConfigurationPanel() {
    this->gui->setVisible(false);
    ofHideCursor();
}

void ofApp::showConfigurationPanel() {
    this->gui->setVisible(true);
    this->gui->disableKeyEventCallbacks();
    ofShowCursor();
}

void ofApp::unfocusAllTextInputs(ofxUITextInput* except){
    for (int i = 0; i < this->textInputs.size(); i ++){
        if (except != this->textInputs[i]){
            this->textInputs[i]->setFocus(false);
        }
    }
}

