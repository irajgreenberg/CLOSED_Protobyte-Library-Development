#include "testApp.h"

using namespace ijg;


GLfloat lightOnePosition[] = {-100, -100, 800, 1.0};
GLfloat lightOneColor[] = {255, 255, 255, 1.0};
GLfloat lightAmbientLight[] = {0.0, 0.0, 0.0};
GLfloat lightSpecularLight[] = {1.0, 1.0, 1.0};
GLfloat mShininess[] = {128};

GLfloat mat_diffuse[] = {0.1f, 0.5f, 0.8f, 1.0f};
GLfloat mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat no_mat[] = {0.0f, 0.0f, 0.0f, 1.0f};
GLfloat no_shininess = 0.0f;
GLfloat low_shininess = 5.0f;
GLfloat high_shininess = 100.0f;
GLfloat mat_emission[] = {0.3f, 0.2f, 0.2f, 0.0f};


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
	
	// this uses depth information for occlusion
	// rather than always drawing things on top of each other
	glEnable(GL_DEPTH_TEST);

	// this sets the camera's distance from the object
	cam.setDistance(0);
    cam.enableMouseInput();
    
    
    ofEnableAlphaBlending(); // enable alpha
    glShadeModel (GL_FLAT);
    //glShadeModel (GL_SMOOTH);
	
    
    /* initialize lighting */
    glEnable (GL_DEPTH_TEST);
    glEnable (GL_LIGHTING);
    glEnable (GL_LIGHT0);
    
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecularLight);
    //glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbientLight);
    glLightfv (GL_LIGHT0, GL_POSITION, lightOnePosition);
    glLightfv (GL_LIGHT0, GL_DIFFUSE, lightOneColor);
    //glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mShininess);
    
    //glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, no_mat);
    //glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, low_shininess);
    //glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_emission);
    
    //glColorMaterial (GL_FRONT_AND_BACK, GL_DIFFUSE);
    
    
    
    
    
    glEnable (GL_COLOR_MATERIAL);
    
    //ofSetBackgroundAuto(false); //disable automatic background redraw
    
    //ofLogVerbose() << "a verbose print";
    //ofLogNotice() << "a regular notice print";
    
    
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
    
    
    ofSetColor(255,130,0);
    ofFill();
    //p.display();
    
    // particles
    ofSetColor(75, 75, 255, 20);
    ofFill();
    for(int i=0; i<PARTICLE_COUNT; i++){
        // parts[i].display();
    }
    
    
    ofSetColor(0, 255, 0, 255);
    //ofNoFill();
    
    ofPushMatrix();
    ofScale(200, 200, 200);
    pOrg02.display();
    
    //ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    //ofScale(1.9, 1.9, 1.9);
    //pOrg.display(2);
    //pOrg.displayNormals();
    
    
    ofNoFill();
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