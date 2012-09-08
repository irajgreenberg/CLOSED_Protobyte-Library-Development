#pragma once

#include "ofMain.h"
#include "Particle.h"
#include "ProtoOrg001.h"
#include "ProtoOrg002.h"

//#include "ProtoOrgBase.h"

class testApp : public ofBaseApp{

public:
    
    ijg::ProtoOrgBase pBase;
    ijg::ProtoOrg002 pOrg02;
    
    
    ofEasyCam cam; // add mouse controls for camera movement
    
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    void setLighting();
};
