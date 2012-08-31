//
//  IGFace3D.cpp
//  animatingParticles
//
//  Created by Ira on 8/30/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <IGFace3D.h>


IGFace3D::IGFace3D(ofVec3f* v0, ofVec3f* v1, ofVec3f* v2) 
{
    p_vecs[0] = v0;
    p_vecs[1] = v1;
    p_vecs[2] = v2;
}

IGFace3D::IGFace3D(ofVec3f vs[3])
{
    vecs = vs;
    p_vecs[0] = &(vecs[0]);
    p_vecs[1] = &(vecs[1]);
    p_vecs[2] = &(vecs[2]);
}


ofVec3f& IGFace3D::getNormal()
{
    return nrml;
}

// Must be calcualted anytime vertex geometry is transformed.
// transformationa to the Graphics context don't require 
// new normal calculation.
void IGFace3D::calcNormal()
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
    
    ofVec3f U = *p_vecs[1]-*p_vecs[0];
    ofVec3f V = *p_vecs[2]-*p_vecs[0];
    
    nrml.x = U.y*V.z - U.z*V.y;
    nrml.y = U.z*V.x - U.x*V.z;
    nrml.z = U.x*V.y - U.y*V.x;
    
    nrml.normalize();
}

void IGFace3D::display()
{

    ofBeginShape();
    ofVertex(p_vecs[0]->x, p_vecs[0]->y, p_vecs[0]->z);
    ofVertex(p_vecs[1]->x, p_vecs[1]->y, p_vecs[1]->z);
    ofVertex(p_vecs[2]->x, p_vecs[2]->y, p_vecs[2]->z);
    ofEndShape(true);
}