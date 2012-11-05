#pragma once

#include "ofMain.h"
#include "Particle.h"
#include "ProtoOrg001.h"
#include "ProtoOrg002.h"
#include "ProtoToroid.h"
#include "Spline3d.h"
#include "ProtoTube.h"
#include "ProtoTetrahedron.h"

//#include "ProtoOrgBase.h"

class ProtoController : public ofBaseApp{

public:
    
    
    ijg::ProtoToroid toroid1;
    ijg::Spline3d spline1;
    ijg::ProtoTube tube;
    ijg::ProtoTetrahedron tetrahedron;
    
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
