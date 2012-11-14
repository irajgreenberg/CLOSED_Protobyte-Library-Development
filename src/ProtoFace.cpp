//
//  ProtoFace.cpp
//  animatingParticles
//
//  Created by Ira on 8/30/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <ProtoFace.h>

using namespace ijg;



ProtoFace:: ProtoFace()
{
}


ProtoFace::ProtoFace(const ofVec3f& v0, const ofVec3f& v1, const ofVec3f& v2):
v0(v0), v1(v1), v2(v2)
{
    vecs[0] = v0;
    vecs[1] = v1;
    vecs[2] = v2;
    
    calcNormal();
    calcCentroid();  
}

ProtoFace::ProtoFace(ofVec3f vs[3])
{
    v0 = vecs[0] = vs[0];
    v1 = vecs[1] = vs[1];
    v2 = vecs[2] = vs[2];

    
    calcNormal();
    calcCentroid();
}

ProtoFace::ProtoFace(const ProtoEdge& e0, const ProtoEdge& e1, const ProtoEdge& e2):
e0(e0), e1(e1), e2(e2)
{
    edges[0] = e0;
    edges[1] = e1;
    edges[2] = e2;
    
    v0 = vecs[0] = edges[0].getV0();
    v1 = vecs[1]= edges[1].getV0();
    v2 = vecs[2]= edges[2].getV0();
    
    calcNormal();
    calcCentroid();
}




ofVec3f& ProtoFace::getNormal()
{
    return normal;
}

// Must be calcualted anytime vertex geometry is transformed.
// transformationa to the Graphics context don't require
// new normal calculation.
void ProtoFace::calcNormal()
{
    /*
     Face v0, v1, v2
     vector U = v1 - v0
     vector V = v2 - v0
     normal U X V
     Nx = UyVz - UzVy
     Ny = UzVx - UxVz
     Nz = UxVy - UyVx
     */
    
    ofVec3f U = vecs[1]-vecs[0];
    ofVec3f V = vecs[2]-vecs[0];
    
    normal.x = U.y*V.z - U.z*V.y;
    normal.y = U.z*V.x - U.x*V.z;
    normal.z = U.x*V.y - U.y*V.x;
    
    normal.normalize();
    
    //normal*=.04;
}

void ProtoFace::calcCentroid()
{
    centroid = ofVec3f((vecs[0].x+vecs[1].x+vecs[2].x)/3,
                       (vecs[0].y+vecs[1].y+vecs[2].y)/3,
                       (vecs[0].z+vecs[1].z+vecs[2].z)/3
                       );
   // std::cout<< "centroid = " << centroid << std::endl;
}

void ProtoFace::display()
{
    
    ofBeginShape();

    //glNormal3fv(&n[i][0]);
    ofVertex(vecs[0].x, vecs[0].y, vecs[0].z);
    ofVertex(vecs[1].x, vecs[1].y, vecs[1].z);
    ofVertex(vecs[2].x, vecs[2].y, vecs[2].z);
    ofEndShape(true);
}

void ProtoFace::displayNormal(float len)
{
    
    ofPushStyle();
    
    ofNoFill();
    ofSetColor(255, 255, 255);
    //ofBeginShape();
    glBegin(GL_LINES);
    glVertex3f(centroid.x, centroid.y, centroid.z);
    glVertex3f(centroid.x+normal.x*len, centroid.y+normal.y*len, centroid.z+normal.z*len);
    //ofEndShape();
    glEnd();
    
    ofPopStyle();
}







