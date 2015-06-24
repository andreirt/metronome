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
const string ofApp::SAVE_LABEL = "Salvar";
const string ofApp::CANCEL_LABEL = "Cancelar";
const string ofApp::SUPPORT_BUTTON_NAME = "support";



//--------------------------------------------------------------
void ofApp::setup(){
    this->grayscale = new GrayscaleSequence();

    this->timelapse = new Timelapse("imagem_");
    this->metronome = new Metronome( this->timelapse, 0, 0, 0, ofGetWidth(), ofGetHeight(), 1000 );

    ofSetFrameRate(60);
    ofBackground(0, 0, 0);

    this->grabber = new ofVideoGrabber();

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
    this->gui->addWidgetDown(this->recordToggle);

    this->reproductionToggle = new ofxUIToggle(ofApp::REPRODUCTION_LABEL, true, 16, 16);
    this->reproductionToggle->setDrawOutline(true);
    this->gui->addWidgetRight(this->reproductionToggle);

    this->gui->addSpacer("spacer", 1) ;

    this->recordPanel = new ofxUICanvas (0, 0, 450, 200);
    this->recordPanel->setFontSize(OFX_UI_FONT_SMALL, 8);
    this->recordPanel->setWidgetSpacing(10);
    this->gui->addWidgetSouthOf(this->recordPanel, "spacer");

    this->rotationPanel = new ofxUICanvas(0, 0, 300, 200);
    this->rotationPanel->setFontSize(OFX_UI_FONT_SMALL, 8);
    this->rotationPanel->setWidgetSpacing(10);
    this->gui->addWidgetRight(this->rotationPanel);

    this->reproductionPanel = new ofxUICanvas(0, 0, ofGetWidth(), 200);
    this->reproductionPanel->setFontSize(OFX_UI_FONT_SMALL, 8);
    this->reproductionPanel->setWidgetSpacing(10);
    this->gui->addWidgetSouthOf(this->reproductionPanel, "spacer");


    vector<ofVideoDevice> devices = this->grabber->listDevices();
    vector<string> *cameras = new vector<string>;
    vector<ofVideoDevice>::iterator it;

    for (it = devices.begin(); it != devices.end(); it++) {
        ofVideoDevice device = *it;
        cameras->push_back(device.deviceName);
    }

    this->selectedCameraIndex = 1;
    this->cameraList = this->recordPanel->addDropDownList(ofApp::CAMERA_LABEL, *cameras, 300, 10);
    this->cameraList->setAllowMultiple(false);
    this->cameraList->setDrawOutline(true);

    this->recordPanel->addWidgetDown( new ofxUILabel(180, ofApp::IMAGE_WIDTH_LABEL, OFX_UI_FONT_SMALL) );
    this->cameraWidthTextInput = new ofxUITextInput("CameraWidth", "1920", 80, 18);
    this->cameraWidthTextInput->setOnlyNumericInput(true);
    this->cameraWidthTextInput->setDrawOutline(true);
    this->cameraWidthTextInput->setDrawOutlineHighLight(true);
    this->recordPanel->addWidgetRight(this->cameraWidthTextInput);
    this->textInputs.push_back(this->cameraWidthTextInput);

    this->recordPanel->addWidgetDown( new ofxUILabel(180, ofApp::IMAGE_HEIGHT_LABEL, OFX_UI_FONT_SMALL) );
    this->cameraHeightTextInput = new ofxUITextInput("CameraHeight", "1080", 80, 18);
    this->cameraHeightTextInput->setOnlyNumericInput(true);
    this->cameraHeightTextInput->setDrawOutline(true);
    this->cameraHeightTextInput->setDrawOutlineHighLight(true);
    this->recordPanel->addWidgetRight(this->cameraHeightTextInput);
    this->textInputs.push_back(this->cameraHeightTextInput);

    this->recordPanel->addWidgetDown(new ofxUILabel(180, ofApp::IMAGE_PREFIX_LABEL, OFX_UI_FONT_SMALL));
    this->recordImagePrefixTextInput = new ofxUITextInput("ImagePrefix", "imagem_", 200, 18);
    this->recordImagePrefixTextInput->setDrawOutline(true);
    this->recordImagePrefixTextInput->setDrawOutlineHighLight(true);
    this->recordPanel->addWidgetRight(this->recordImagePrefixTextInput);
    this->textInputs.push_back(this->recordImagePrefixTextInput);

    this->recordPanel->addWidgetDown(new ofxUILabel(180, ofApp::SAVE_IMAGE_LABEL, OFX_UI_FONT_SMALL));
    this->intervalToSaveTextInput = new ofxUITextInput("A cada", "15", 60, 18);
    this->intervalToSaveTextInput->setOnlyNumericInput(true);
    this->intervalToSaveTextInput->setDrawOutline(true);
    this->intervalToSaveTextInput->setDrawOutlineHighLight(true);
    this->recordPanel->addWidgetRight( this->intervalToSaveTextInput );
    this->recordPanel->addWidgetRight( new ofxUILabel(10, "minutos", OFX_UI_FONT_SMALL) );
    this->textInputs.push_back(this->intervalToSaveTextInput);

    this->rotations = 0;

    this->rotationPanel->addLabel("Rotação da imagem", OFX_UI_FONT_SMALL);

    this->zeroRotationToggle = new ofxUIToggle(ofApp::ZERO_DEGREES_LABEL, true, 16, 16);
    this->zeroRotationToggle->setDrawOutline(true);
    this->rotationPanel->addWidgetDown(this->zeroRotationToggle);

    this->ninetyRotationToggle = new ofxUIToggle(ofApp::NINETY_DEGREES_LABEL, true, 16, 16);
    this->ninetyRotationToggle->setDrawOutline(true);
    this->rotationPanel->addWidgetDown(this->ninetyRotationToggle);

    this->oneHundredEightyRotationToggle = new ofxUIToggle(ofApp::ONE_HUNDRED_EIGHTY_DEGREES_LABEL, true, 16, 16);
    this->oneHundredEightyRotationToggle->setDrawOutline(true);
    this->rotationPanel->addWidgetDown(this->oneHundredEightyRotationToggle);

    this->twoHundredSeventyRotationToggle = new ofxUIToggle(ofApp::TWO_HUNDRED_SEVENTY_DEGREES_LABEL, true, 16, 16);
    this->twoHundredSeventyRotationToggle->setDrawOutline(true);
    this->rotationPanel->addWidgetDown(this->twoHundredSeventyRotationToggle);


    this->reproductionPanel->addWidgetDown( new ofxUILabel(250, ofApp::IMAGE_PREFIX_LABEL, OFX_UI_FONT_SMALL) );
    this->reproductionImagePrefixTextInput = new ofxUITextInput("ImagePrefix", "imagem_", 200, 18);
    this->reproductionImagePrefixTextInput->setDrawOutline(true);
    this->reproductionImagePrefixTextInput->setDrawOutlineHighLight(true);
    this->reproductionPanel->addWidgetRight(this->reproductionImagePrefixTextInput);
    this->textInputs.push_back(this->reproductionImagePrefixTextInput);

    this->reproductionPanel->addWidgetDown( new ofxUILabel(250, ofApp::MAX_FRAME_TIME_LABEL, OFX_UI_FONT_SMALL) );
    this->cycleMaxTimeTextInput = new ofxUITextInput("MaxCycleTime", "30", 80, 18);
    this->cycleMaxTimeTextInput->setOnlyNumericInput(true);
    this->cycleMaxTimeTextInput->setDrawOutline(true);
    this->cycleMaxTimeTextInput->setDrawOutlineHighLight(true);
    this->reproductionPanel->addWidgetRight(this->cycleMaxTimeTextInput);
    this->textInputs.push_back(this->cycleMaxTimeTextInput);

    this->reproductionPanel->addWidgetDown( new ofxUILabel(250, ofApp::ITERATION_NUMBER_LABEL, OFX_UI_FONT_SMALL) );
    this->divisionsMaxNumberTextInput = new ofxUITextInput("DivisionsNumber", "7", 80, 18);
    this->divisionsMaxNumberTextInput->setOnlyNumericInput(true);
    this->divisionsMaxNumberTextInput->setDrawOutline(true);
    this->divisionsMaxNumberTextInput->setDrawOutlineHighLight(true);
    this->reproductionPanel->addWidgetRight(this->divisionsMaxNumberTextInput);
    this->textInputs.push_back(this->divisionsMaxNumberTextInput);

    this->showAtStartupToggle = new ofxUIToggle(ofApp::SHOW_ON_START_LABEL, true, 16, 16);
    this->showAtStartupToggle->setDrawOutline(true);
    this->gui->addWidgetDown(this->showAtStartupToggle);

    this->fullScreenToggle = new ofxUIToggle(ofApp::FULL_SCREEN_LABEL, true, 16, 16);
    this->fullScreenToggle->setDrawOutline(true);
    this->gui->addWidgetDown(this->fullScreenToggle);

    this->gui->addSpacer();

    ofxUILabelButton* saveButton = this->gui->addLabelButton(ofApp::SAVE_LABEL, false, 100, 20);
    saveButton->setDrawFill(true);
    saveButton->setDrawOutline(true);

    ofxUILabelButton* cancelButton = new ofxUILabelButton(ofApp::CANCEL_LABEL, false, 100, 20);
    cancelButton->setDrawFill(true);
    cancelButton->setDrawOutline(true);
    this->gui->addWidgetRight(cancelButton);
    this->gui->addSpacer();

    this->gui->addLabel("Metrônomo - Andrei Thomaz, 2015");
    this->gui->addLabel("Integrante do projeto Máquinas do Tempo, desenvolvido com apoio da Bolsa de Artes Visual da Funarte 2014");
    this->gui->addLabel("Desenvolvido em C++ / OpenFrameworks e distribuído sob a licença MPL");
    this->gui->addLabel("Programação por Andrei Thomaz e Vitor Andrioli");
    this->gui->addSpacer();

    this->gui->addLabel("Realização");
    this->gui->addImageButton(ofApp::SUPPORT_BUTTON_NAME, "funarte.png", false, 509, 60);

    ofAddListener(this->gui->newGUIEvent, this, &ofApp::guiEvent);
    ofAddListener(this->recordPanel->newGUIEvent, this, &ofApp::recordPanelEvent);
    ofAddListener(this->rotationPanel->newGUIEvent, this, &ofApp::rotationPanelEvent);
    ofAddListener(this->reproductionPanel->newGUIEvent, this, &ofApp::reproductionPanelEvent);

    this->recordPanel->loadSettings("record.xml");
    this->reproductionPanel->loadSettings("reproduction.xml");
    this->gui->loadSettings("settings.xml");

    this->applyConfigurationChanges();

    ofLog() << "this->recordToggle->getValue(): " << this->recordToggle->getValue();
    ofLog() << "this->reproductionToggle->getValue(): " << this->reproductionToggle->getValue();

    if (this->showAtStartup) {
        this->showConfigurationPanel();
    } else {
        this->hideConfigurationPanel();
    }
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
    this->gui->setWidth(ofGetWidth());
    this->gui->setHeight(ofGetHeight());

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}

void ofApp::applyConfigurationChanges() {
    if (this->zeroRotationToggle->getValue()) {
        this->rotations = 0;
    }
    if (this->ninetyRotationToggle->getValue()) {
        this->rotations = 1;
    }
    else if (this->oneHundredEightyRotationToggle->getValue()) {
        this->rotations = 2;
    }
    else if (this->twoHundredSeventyRotationToggle->getValue()) {
        this->rotations = 3;
    }

    this->zeroRotationToggle->setValue(this->rotations == 0);
    this->ninetyRotationToggle->setValue(this->rotations == 1);
    this->oneHundredEightyRotationToggle->setValue(this->rotations == 2);
    this->twoHundredSeventyRotationToggle->setValue(this->rotations == 3);

    if (this->rotations % 2 == 0) {
        this->imageWidth = this->cameraWidthTextInput->getIntValue();
        this->imageHeight = this->cameraHeightTextInput->getIntValue();
    }
    else {
        this->imageWidth = this->cameraHeightTextInput->getIntValue();
        this->imageHeight = this->cameraWidthTextInput->getIntValue();
    }

    this->showAtStartup = this->showAtStartupToggle->getValue();
    this->fullScreen = this->fullScreenToggle->getValue();

    this->intervalToSave = this->intervalToSaveTextInput->getIntValue();
    this->recordImagePrefix = this->recordImagePrefixTextInput->getTextString();
    this->reproductionImagePrefix = this->reproductionImagePrefixTextInput->getTextString();
    this->cycleMaxTime = this->cycleMaxTimeTextInput->getIntValue();
    this->divisionsMax = this->divisionsMaxNumberTextInput->getIntValue();

    if (this->fullScreen) {
        ofSetFullscreen(true);
    }
    else {
        ofSetFullscreen(false);
        ofSetWindowShape(this->imageWidth, this->imageHeight);
    }

    this->gui->setWidth(ofGetWidth());
    this->gui->setHeight(ofGetHeight());
}

void ofApp::guiEvent(ofxUIEventArgs &e) {
    ofLog() << "event: " << e.getName();
    if (e.getName() == ofApp::RECORD_LABEL && e.getToggle()->getValue()) {
        this->showRecordPanel();
    }
    else if (e.getName() == ofApp::REPRODUCTION_LABEL && e.getToggle()->getValue()) {
        this->showReproductionPanel();
    }

    else if (e.getName() == ofApp::SAVE_LABEL) {
        // catches the click when mouse is released, not pressed
        if (!e.getButton()->getValue()) {
            this->recordPanel->saveSettings("record.xml");
            this->reproductionPanel->saveSettings("reproduction.xml");
            this->gui->saveSettings("settings.xml");
            this->applyConfigurationChanges();
            //this->reset();
            this->hideConfigurationPanel();

        }
    }
    else if (e.getName() == ofApp::CANCEL_LABEL) {
        // catches the click when mouse is released, not pressed
        if (!e.getButton()->getValue()) {
            //this->cancelConfigurationChanges();
            this->hideConfigurationPanel();

        }
    }
    else if (e.getName() == ofApp::SUPPORT_BUTTON_NAME) {
        // catches the click when mouse is released, not pressed
        if (!e.getButton()->getValue()) {
            ofLaunchBrowser("http://www.funarte.gov.br/");
        }
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

void ofApp::rotationPanelEvent(ofxUIEventArgs &e) {
    if (e.getName() == ofApp::ZERO_DEGREES_LABEL && e.getToggle()->getValue()) {
        this->ninetyRotationToggle->setValue(false);
        this->oneHundredEightyRotationToggle->setValue(false);
        this->twoHundredSeventyRotationToggle->setValue(false);
    }
    else if (e.getName() == ofApp::NINETY_DEGREES_LABEL && e.getToggle()->getValue()) {
        this->zeroRotationToggle->setValue(false);
        this->oneHundredEightyRotationToggle->setValue(false);
        this->twoHundredSeventyRotationToggle->setValue(false);
    }
    else if (e.getName() == ofApp::ONE_HUNDRED_EIGHTY_DEGREES_LABEL && e.getToggle()->getValue()) {
        this->zeroRotationToggle->setValue(false);
        this->ninetyRotationToggle->setValue(false);
        this->twoHundredSeventyRotationToggle->setValue(false);
    }
    else if (e.getName() == ofApp::TWO_HUNDRED_SEVENTY_DEGREES_LABEL && e.getToggle()->getValue()) {
        this->zeroRotationToggle->setValue(false);
        this->ninetyRotationToggle->setValue(false);
        this->oneHundredEightyRotationToggle->setValue(false);
    }
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
    this->reproductionPanel->setVisible(false);
    this->recordPanel->setVisible(true);
    this->rotationPanel->setVisible(true);
    this->reproductionToggle->setValue(false);
}

void ofApp::showReproductionPanel() {
    this->recordPanel->setVisible(false);
    this->rotationPanel->setVisible(false);
    this->reproductionPanel->setVisible(true);
    this->recordToggle->setValue(false);
}

void ofApp::hideConfigurationPanel() {
    this->gui->setVisible(false);
    this->recordPanel->setVisible(false);
    this->reproductionPanel->setVisible(false);
    this->rotationPanel->setVisible(false);
    ofHideCursor();
}

void ofApp::showConfigurationPanel() {
    this->gui->setVisible(true);

    if (this->recordToggle->getValue()) {
        this->showRecordPanel();
        this->rotationPanel->setVisible(true);
    } else {
        this->reproductionPanel->setVisible(true);
    }

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

