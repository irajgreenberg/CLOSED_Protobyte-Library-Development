#pragma once

#include "ofMain.h"
#include "Particle.h"
#include "ProtoOrg001.h"

class testApp : public ofBaseApp{

public:
    
    Particle p;
    ProtoOrg001 pOrg;
    
    
    static const int PARTICLE_COUNT=2000;
    vector<Particle> parts;
    
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
};
