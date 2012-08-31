#include "testApp.h"

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
    pOrg = ProtoOrg001(60, 60, 200);
    //pOrg.spines = 75;
    pOrg.init();
    
    // environment states
    ofSetCircleResolution(20);
	ofBackground(255,255,255);
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
   
    
    ofSetColor(0, 100, 0, 45);
    ofNoFill();
    ofPushMatrix();
    
    //ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    //ofScale(1.9, 1.9, 1.9);
   // pOrg.display(1);
    pOrg.display(2);
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