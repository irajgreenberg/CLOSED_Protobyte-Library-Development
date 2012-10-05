//
//  Face3D.h
//  animatingParticles
//  automicatlly calculates face normals
//
//  Created by Ira on 8/30/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef animatingParticles_Face3D_h
#define animatingParticles_Face3D_h

#include "ofMain.h"

namespace ijg {

    
    class Face3D {
        
    public:
        
        explicit Face3D(ofVec3f* v0=0, ofVec3f* v1=0, ofVec3f* v2=0);
        Face3D(ofVec3f vecs[3]);
        Face3D(ofVec3f* p_vecs[3]);
        
        ofVec3f normal, centroid;
        ofVec3f* vecs; // pointer to array
        ofVec3f* p_vecs[3]; // array of vec pointers
        
        ofVec3f& getNormal();
        
        void display();
        void displayNormal();
        
    private:
        void calcNormal();
        void calcCentroid();
        
        
    };
}

#endif
