//
//  IGFace3D.h
//  animatingParticles
//  automicatlly calculates face normals
//
//  Created by Ira on 8/30/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef animatingParticles_IGFace3D_h
#define animatingParticles_IGFace3D_h

#include "ofMain.h"

class IGFace3D {
    
public:
    
    explicit IGFace3D(ofVec3f* v0=0, ofVec3f* v1=0, ofVec3f* v2=0);
    IGFace3D(ofVec3f vecs[3]);
    IGFace3D(ofVec3f* p_vecs[3]);
    
    ofVec3f nrml;
    ofVec3f* vecs; // pointer to array
    ofVec3f* p_vecs[3]; // array of vec pointers
    
    ofVec3f& getNormal();
    
    void display();
    
private:
    void calcNormal();
    
    
};

#endif
