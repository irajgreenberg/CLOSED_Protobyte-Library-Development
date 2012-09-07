#include "testApp.h"

using namespace ijg;


// new lighting vals
// light and material values
// 1 light Ð (light0)
GLfloat light0_pos[] = {-100, -100, 400};
GLfloat light0_amb[] = {0.0, 0.0, 0.0};
GLfloat light0_dif[] = {100.0, 100.0, 100.0};
GLfloat light0_spec[] = {1.0, 1.0, 1.0};


GLfloat mat_amb[] = {.11f, 0.06f, .11f, 1.0f};
GLfloat mat_dif[] = {0.43f, 0.47f, 0.54f, 1.0f};
GLfloat mat_spec[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat mat_emis[] = {0.0f, 0.0f, 0.0f, 0.0f};
GLfloat mat_shin = 100;



//============================================================================
// Lighting variables - from ProtoLib
//============================================================================

// Basic 3-point lighting setup (Key, Fill, Back)
// light0 - Key
float light0Ambient[] = { .2, .2, .2, 1 };
float light0Diffuse[] = {100.75, 60.5, 100.75, 1 }; // warmer
float light0Specular[] = {  1, 100, 1, 1 };
float light0Pos[4] = { -5.5, 1.2, 2, 0 };  // 4th arg 0=infinity, 1=position

// light 1 Ð Fill
float light1Ambient[] = { 0, 0, 0, 1 };
float light1Diffuse[] = {.2, 100.2, .3, 1 }; // cooler
float light1Specular[] = {  1.2, 1.2, 1.2, 1 };
float light1Pos[4] = { .5, 0, 0, 0 };  // 4th arg 0=infinity, 1=position

// light 2 Ð Back
float light2Ambient[] = { 0, 0, 0, 1 };
float light2Diffuse[] = {1, .6, .1, 1 };
float light2Specular[] = {  1.2, 1.2, 1.2, 1 };
float light2Pos[4] = { .5, .2, -1, 0 };  // 4th arg 0=infinity, 1=position

// Materials
float mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
float mat_shininess[] = { 128 }; // use range 0 to 128




//--------------------------------------------------------------
void testApp::setup(){
    // single particle
    p.setLoc(ofVec2f(200, 200));
    p.setSpd(ofVec2f(.4, .857));
    
    // multiple particles
    for(int i=0; i<PARTICLE_COUNT; i++){
        float x = ofGetWidth()/2 + ofRandom(-3, 3);
        float y = ofRandom(-3, 5);
        float xs = ofRandom(-1.8, 1.8);
        float ys = ofRandom(.75, 1.3);
        parts.push_back(Particle(ofVec2f(x, y), ofVec2f(xs, ys)));
    }
    
    //ProtoOrg
   // pOrg = ProtoOrg001(28, 28, 200);
    //pOrg.spines = 75;
   // pOrg.init();
    pOrg02.setSpines(15);
    pOrg02.setSpineDetail(15);
    
    
    
    // environment states
    ofSetCircleResolution(20);
	ofBackground(0,0,0);
	ofSetWindowTitle("particles example");
    ofSetFrameRate(60);
    
    ofSetVerticalSync(true);

	// this sets the camera's distance from the object
	cam.setDistance(0);
    cam.enableMouseInput();
    
    
    ofEnableAlphaBlending(); // enable alpha
    glShadeModel (GL_FLAT);
    //glShadeModel (GL_SMOOTH);
	
    
    /* initialize lighting */
    glEnable (GL_DEPTH_TEST);
   // glEnable (GL_LIGHTING);
    //glEnable (GL_LIGHT0);
    
    
    // Explicitely set face winding rule
    glFrontFace(GL_CW); // or GL_CW
    
    // Hide back faces of surfaces
    //glEnable(GL_CULL_FACE);
    
    // enable alpha - requires faces drawn back to front
    // not fully implemented
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    
    
    

    /*// set lights
    glLightfv (GL_LIGHT0, GL_POSITION, light0_pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0_amb);
    glLightfv (GL_LIGHT0, GL_DIFFUSE, light0_dif);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0_spec);
        
    // set materials
    glMaterialfv(GL_FRONT, GL_AMBIENT,  mat_amb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,  mat_dif);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_spec);
    glMaterialfv(GL_FRONT, GL_EMISSION, mat_emis);
    glMaterialf(GL_FRONT, GL_SHININESS,  mat_shin);
    //
    */
    //glColorMaterial (GL_FRONT_AND_BACK, GL_DIFFUSE);
    
    
    
    
    //ofSetBackgroundAuto(false); //disable automatic background redraw
    
    //ofLogVerbose() << "a verbose print";
    //ofLogNotice() << "a regular notice print";
    
    setLighting();
    
    
}

//============================================================================
// Set up the lighting
//============================================================================
void testApp::setLighting(){
    
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glColorMaterial(GL_FRONT,GL_DIFFUSE);
    
    // light0
    glLightfv(GL_LIGHT0, GL_POSITION, light0Pos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0Diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0Specular);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0Ambient);
    
    // light1
    glLightfv(GL_LIGHT1, GL_POSITION, light1Pos);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1Diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light1Specular);
    glLightfv(GL_LIGHT1, GL_AMBIENT, light1Ambient);
    
    // light2
    glLightfv(GL_LIGHT2, GL_POSITION, light2Pos);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, light2Diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light2Specular);
    glLightfv(GL_LIGHT2, GL_AMBIENT, light2Ambient);
    
    
    // enable the lights/materials
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_SPECULAR);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    
}




//--------------------------------------------------------------
void testApp::update(){
    p.move();
    
    // particles
    for(int i=0; i<PARTICLE_COUNT; i++){
        parts[i].move();
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    
    cam.begin();

    ofRotateX(180);
    // ofRotateY(ofRadToDeg(-.5));
    
    
    //ofSetColor(255,130,0);
    //ofFill();
    //p.display();
    
    // particles
    //ofSetColor(75, 75, 255, 20);
    //ofFill();
    for(int i=0; i<PARTICLE_COUNT; i++){
        // parts[i].display();
    }
    
    
    ofSetColor(155, 255, 255, 225);
    //ofNoFill();
    
    ofPushMatrix();
    ofScale(200, 200, 200);
    pOrg02.display();
    
    //ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    //ofScale(1.9, 1.9, 1.9);
    //pOrg.display(2);
    //pOrg.displayNormals();
    
    
    //ofNoFill();
    ofSetColor(255, 255, 255);
    //pOrg02.displayNormals();
    
    //pOrg.display(2);
    //ofSetColor(175, 95, 30);
    //pOrg.display(2);
    
    ofPopMatrix();
    
       cam.end();
    
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){
    
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 
    
}