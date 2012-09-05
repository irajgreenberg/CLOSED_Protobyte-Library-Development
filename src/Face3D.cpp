//
//  Face3D.cpp
//  animatingParticles
//
//  Created by Ira on 8/30/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <Face3D.h>

using namespace ijg;

Face3D::Face3D(ofVec3f* v0, ofVec3f* v1, ofVec3f* v2)
{
    p_vecs[0] = v0;
    p_vecs[1] = v1;
    p_vecs[2] = v2;
    
    calcNormal();
    calcCentroid();
}

Face3D::Face3D(ofVec3f vs[3])
{
    vecs = vs;
    p_vecs[0] = &(vecs[0]);
    p_vecs[1] = &(vecs[1]);
    p_vecs[2] = &(vecs[2]);
    
    calcNormal();
    calcCentroid();
}


ofVec3f& Face3D::getNormal()
{
    return normal;
}

// Must be calcualted anytime vertex geometry is transformed.
// transformationa to the Graphics context don't require
// new normal calculation.
void Face3D::calcNormal()
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
    
    ofVec3f V = *p_vecs[1]-*p_vecs[0];
    ofVec3f U = *p_vecs[2]-*p_vecs[0];
    
    normal.x = U.y*V.z - U.z*V.y;
    normal.y = U.z*V.x - U.x*V.z;
    normal.z = U.x*V.y - U.y*V.x;
    
    normal.normalize();
    
    normal*=30;
}

void Face3D::calcCentroid()
{
    centroid = ofVec3f((p_vecs[0]->x+p_vecs[1]->x+p_vecs[2]->x)/3,
                       (p_vecs[0]->y+p_vecs[1]->y+p_vecs[2]->y)/3,
                       (p_vecs[0]->z+p_vecs[1]->z+p_vecs[2]->z)/3
                       );
   // std::cout<< "centroid = " << centroid << std::endl;
}

void Face3D::display()
{
    
    ofBeginShape();

    //glNormal3fv(&n[i][0]);
    ofVertex(p_vecs[0]->x, p_vecs[0]->y, p_vecs[0]->z);
    ofVertex(p_vecs[1]->x, p_vecs[1]->y, p_vecs[1]->z);
    ofVertex(p_vecs[2]->x, p_vecs[2]->y, p_vecs[2]->z);
    ofEndShape(true);
}

void Face3D::displayNormal()
{
    
    ofPushStyle();
    
    ofNoFill();
    ofSetColor(255, 255, 255);
    //ofBeginShape();
    glBegin(GL_LINES);
    glVertex3f(centroid.x, centroid.y, centroid.z);
    glVertex3f(centroid.x+normal.x, centroid.y+normal.y, centroid.z+normal.z);
    //ofEndShape();
    glEnd();
    
    ofPopStyle();
}







