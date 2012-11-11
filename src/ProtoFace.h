//
//  ProtoFace.h
//  animatingParticles
//  automicatlly calculates face normals
//
//  Created by Ira on 8/30/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef animatingParticles_ProtoFace_h
#define animatingParticles_ProtoFace_h

#include "ofMain.h"

namespace ijg {

    
    class ProtoFace {
        
    public:
        
        explicit ProtoFace(ofVec3f* v0=0, ofVec3f* v1=0, ofVec3f* v2=0);
        ProtoFace(const ofVec3f& v0, const ofVec3f& v1, const ofVec3f& v2);
        ProtoFace(ofVec3f vecs[3]);
        ProtoFace(ofVec3f* p_vecs[3]);
        
        ofVec3f v0, v1, v2;
        ofVec3f normal, centroid;
        ofVec3f* vecs; // pointer to array
        ofVec3f* p_vecs[3]; // array of vec pointers
        
        ofVec3f& getNormal();
        
        void display();
        void displayNormal(float len);
        
    private:
        void calcNormal();
        void calcCentroid();
        
        
    };
}

#endif
