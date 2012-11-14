#include "ProtoController.h"
#include "Matrix3D.h"
#include "Quaternion.h"

using namespace ijg;


//============================================================================
// Lighting variables - from ProtoLib
//============================================================================

// Basic 3-point lighting setup (Key, Fill, Back)
// light0 - Key
float light0Ambient[] = { 0, 0, 0, 0 };
float light0Diffuse[] = {.5, .65, .4 }; // warmer
float light0Specular[] = {  1, .85, .75, 1 };
float light0Pos[4] = { -50, 150.2, 100, 0 };  // 4th arg 0=infinity, 1=position

// light 1 Ð Fill
float light1Ambient[] = { 0, 0, 0, 1 };
float light1Diffuse[] = {.3, .3, .5, 1 }; // cooler
float light1Specular[] = {  1.2, 1.2, 1.2, 1 };
float light1Pos[4] = { 0, 0, 0, 0 };  // 4th arg 0=infinity, 1=position

// light 2 Ð Back
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
    glFrontFace(GL_CCW); // or GL_CW
    
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
    
    toroid1 =  ProtoToroid(ofVec3f(0, 0, 0), Dimension3D(240, 240, 240), 60, 80, .09);
    toroid1.exportSTL();
    std::cout << toroid1 << std::endl;
    
    //TUBE/TENDRIL
    // Spline3d(const std::vector<ofVec3f>& controlPts, int interpDetail, bool isCurveClosed, float smoothness);
    std::vector<ofVec3f> vecs;
    const int LEN = 20;
    float radii[LEN*35-2];
    float theta = 0;
    for(int i=0; i<LEN; i++){
        vecs.push_back(ofVec3f(ofRandom(-300, 300), ofRandom(-300, 300), ofRandom(-300, 300)));
    }

    //spline1 = Spline3d(vecs, 15, false, .5);
    //spline1.setTerminalSmooth(false); // not working yet
    
    //tube = ProtoTube(ofVec3f(), Dimension3D(), spline1, 4, 40);
    //tube.exportSTL();
    
    // TETRAHEDRON
    tetrahedron = ProtoTetrahedron(ofVec3f(0, 0, 0), Dimension3D(200, 200, 200), 3);
    
    
    
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
    
    //(ofVec3f vecs[3], const ofVec3f& loc, const Dimension3D& dim, int subdivLevel):
    ofVec3f vs[3] = { ofVec3f(cos(0),sin(0)),ofVec3f(cos(120*PI/180.0),sin(120*PI/180.0)), ofVec3f(cos(240*PI/180.0),sin(240*PI/180.0)) };
    sds = SubDivSurf(vs, ofVec3f(0, 0, 0), Dimension3D(100, 100, 100), 2);
    
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
     glEnable(GL_LIGHTING);
    
    cam.begin();
     //glEnable(GL_DEPTH_TEST);
    glPushMatrix();
    //ofRotateX(180);
    glTranslatef(0, 0, -50);
    
    //ofNoFill();

    
    // draw opaque first
    //glDisable(GL_CULL_FACE);
    
   // glRotatef(ofGetFrameNum(), 1, 0, 0);
   // glRotatef(ofGetFrameNum(), 0, 0, 1);
   
    
    //glDepthMask(GL_FALSE); // turn off - for transparency
    
    
    glDepthMask(GL_TRUE);
    toroid1.display();
    //toroid1.displayNormals(.3);
   // tube.display();
    
    ofSetColor(155, 255, 255, 80);
    //glShadeModel (GL_FLAT);
    glEnable(GL_LIGHTING);
    tetrahedron.display();
    glDisable(GL_LIGHTING);
    tetrahedron.displayNormals(.3);
    tetrahedron.displayEdges();
    
    // subdivision surface
    //sds.display();
     //glDisable(GL_LIGHTING);
    //sds.displayNormals(.5);
    
    glPopMatrix();
    
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
    //spline1.displayFrenetFrames(30);
    //spline1.drawCrossSections();
    
    cam.end();
    
    // reset culling/lighting
    glEnable(GL_CULL_FACE);
    light0Ambient[0] =  light0Ambient[1] = light0Ambient[2] = 0;
    light1Ambient[0] =  light1Ambient[1] = light1Ambient[2] = 0;
    setLighting();
    
    
    
    // testing area
 
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