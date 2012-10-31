#include "ProtoController.h"
#include "Matrix3D.h"
#include "Quaternion.h"

using namespace ijg;

// temp experiemntal space
//
//
/*
float testRadius = 200;
ofVec3f vs[8];
Matrix3D m;
 */
//
//


// - eventually delete



//============================================================================
// Lighting variables - from ProtoLib
//============================================================================

// Basic 3-point lighting setup (Key, Fill, Back)
// light0 - Key
float light0Ambient[] = { 0, 0, 0, 0 };
float light0Diffuse[] = {.5, .65, .4 }; // warmer
float light0Specular[] = {  1, .85, .75, 1 };
float light0Pos[4] = { -50, 150.2, 100, 0 };  // 4th arg 0=infinity, 1=position

// light 1 � Fill
float light1Ambient[] = { 0, 0, 0, 1 };
float light1Diffuse[] = {.3, .3, .5, 1 }; // cooler
float light1Specular[] = {  1.2, 1.2, 1.2, 1 };
float light1Pos[4] = { 0, 0, 0, 0 };  // 4th arg 0=infinity, 1=position

// light 2 � Back
float light2Ambient[] = { 0, 0, 0, 1 };
float light2Diffuse[] = {1, .2, .1, 1 };
float light2Specular[] = {  1.2, 1.2, 1.2, 1 };
float light2Pos[4] = { 100.5, .2, 20, 0 };  // 4th arg 0=infinity, 1=position

// Materials
float mat_specular[] = { 1.0, .5, 1.0, 1.0 };
float mat_shininess[] = { 128 }; // use range 0 to 128




//--------------------------------------------------------------
void ProtoController::setup(){
    
    // environment states
	ofBackground(0,0,0);
	ofSetWindowTitle("Protobyte Library Development");
    ofSetFrameRate(60);
    
    ofSetVerticalSync(true); // is this necessary
    
	// this sets the camera's distance from the object
	cam.setDistance(-10);
    cam.enableMouseInput();
    
    
    ofEnableAlphaBlending(); // enable alpha
    glShadeModel (GL_FLAT);
    glShadeModel (GL_SMOOTH);
	
    glEnable (GL_DEPTH_TEST);
    
    
    // Explicitely set face winding rule
    glFrontFace(GL_CW); // or GL_CW
    
    // Hide back faces of surfaces
    glEnable(GL_CULL_FACE);
    
    // enable alpha - requires faces drawn back to front
    // not fully implemented
    glEnable (GL_BLEND);
    
    // try different blends
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glBlendFunc(GL_ONE, GL_ONE);
    
    // The Type Of Depth Testing To Do
    glDepthFunc(GL_LEQUAL);
   //glDepthFunc(GL_ALWAYS);
    //glEnable (GL_POLYGON_STIPPLE);
    // Really Nice Perspective Calculations
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    
    /*
     glEnable(GL_POINT_SIZE);
     glEnable(GL_LINE_WIDTH);
     glPointSize(1);
     glLineWidth(1);
     */
    glEnable(GL_NORMALIZE);
    
    setLighting();
    
    pOrg02.setSpines(80);
    pOrg02.setSpineDetail(80);
    
    pOrg02_b.setSpines(30);
    pOrg02_b.setSpineDetail(30);
    
    pOrg02_c.setSpines(20);
    pOrg02_c.setSpineDetail(20);
    
    //const ofVec3f& loc, const Dimension3D& dim, int spines, int spineDetail, bool isClosed
    pOrg03 = ProtoOrg002(ofVec3f(0, 0, 0), Dimension3D(200, 200, 200), 60, 20, false);
    
    //pOrg02_c.exportSTL();
    
    toroid1 =  ProtoToroid(ofVec3f(0, 0, 0), Dimension3D(240, 240, 240), 60, 80, .09);
    toroid1.exportSTL();
    std::cout << toroid1 << std::endl;
    
    // Spline3d(const std::vector<ofVec3f>& controlPts, int interpDetail, bool isCurveClosed, float smoothness); 
    std::vector<ofVec3f> vecs;
    const int LEN = 40;
    float radii[100];
    float theta = 0;
    for(int i=0; i<LEN; i++){
        vecs.push_back(ofVec3f(ofRandom(-200, 200), ofRandom(-200, 200), ofRandom(-200, 200)));
        radii[i] = abs(sin(theta +=PI/180)*4);
        radii[i] = 20;
    }
    spline1 = Spline3d(vecs, 20, false, 1);
    //spline1.setTerminalSmooth(false); // not working yet
    
    tube = Tube(ofVec3f(), Dimension3D(), spline1, 8, 10);
    tube.exportSTL();
    
    
    
    // experimental test space
    //
    //
    /*
     float tt = 0;
    for(int i=0; i<8; i++){
        vs[i] = ofVec3f(cos(tt)*testRadius, sin(tt)*testRadius, 0);
        tt += PI*2/8;
    }
     */
    //
    //
    // Eventually Delete
    
}

//============================================================================
// Set up the lighting
//============================================================================
void ProtoController::setLighting(){
    
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glColorMaterial(GL_FRONT,GL_DIFFUSE);
    //glColorMaterial(GL_FRONT,GL_SPECULAR);
    
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
    glLightfv(GL_LIGHT2, GL_SPECULAR, light2Specular);
    glLightfv(GL_LIGHT2, GL_AMBIENT, light2Ambient);
    
    
    // enable the lights/materials
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_SPECULAR); // does this do anything
    glEnable(GL_AMBIENT);  // does this do anything
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    
}




//--------------------------------------------------------------
void ProtoController::update(){
}

//--------------------------------------------------------------
void ProtoController::draw(){
    cam.begin();
    
    ofRotateX(180);
    
    //ofNoFill();

    
    // draw opaque first
    glDisable(GL_CULL_FACE);
    //glRotatef(ofGetFrameNum(), 1, 0, 0);
    //glRotatef(ofGetFrameNum(), 0, 0, 1);

   
    ofSetColor(0, 255, 255);
    ofPushMatrix();
    ofScale(50, 50, 50);
    //pOrg02_c.display();
    ofPopMatrix();
   
    
    glDepthMask(GL_FALSE); // turn off - for transparency

     //glDisable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    ofSetColor(75, 100, 125, 190);
    ofPushMatrix();
    ofScale(100, 100, 100);
    //pOrg02_b.display();
    ofPopMatrix();
    
       
    ofSetColor(155, 255, 255, 80);
    ofPushMatrix();
    ofScale(200, 200, 200);
    //pOrg02.display();
    ofPopMatrix();
    
    //pOrg03.display();
    ofPushMatrix();
    //glRotatef(180, 1, 0, 0);
    //pOrg03.display();
    
    glDepthMask(GL_TRUE);
    //toroid1.display();
    tube.display();
    ofPopMatrix();
    
    // glEnable(GL_DEPTH_TEST);
    // turn back on
    glDepthMask(GL_TRUE); // turn back on
    
    
    // Render spline path
    light0Ambient[0] =  light0Ambient[1] = light0Ambient[2] = 1;
    light1Ambient[0] =  light1Ambient[1] = light1Ambient[2] = 1;
    setLighting();
    glDisable(GL_CULL_FACE);
    //spline1.display();
    //spline1.displayControlPts();
    //spline1.displayInterpPts();
    spline1.displayFrenetFrames(30);
    //spline1.drawCrossSections();
    
    cam.end();
    
    // reset culling/lighting
    glEnable(GL_CULL_FACE);
    light0Ambient[0] =  light0Ambient[1] = light0Ambient[2] = 0;
    light1Ambient[0] =  light1Ambient[1] = light1Ambient[2] = 0;
    setLighting();
    
    
    
    // testing area
    //
    //
    /*
    glBegin(GL_POLYGON);
    for(int i=0; i<8; i++){
        //m.rotate(PI/180, ofVec3f(.7, 1, .4), vs[i]); // axis/angle rot
        //Quaternion q(ofVec3f(0, 0, 1), PI/180); // quaternion rot
        //q.rotate(vs[i]);
        glVertex3f(vs[i].x, vs[i].y, vs[i].z);
    }
    glEnd();
    cam.end();
    */
    
    //
    //
    // Eventually Delete
}

//--------------------------------------------------------------
void ProtoController::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ProtoController::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ProtoController::mouseMoved(int x, int y){
    
}

//--------------------------------------------------------------
void ProtoController::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ProtoController::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ProtoController::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ProtoController::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ProtoController::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ProtoController::dragEvent(ofDragInfo dragInfo){
    
}