//
//  ProtoOrg001.h
//  animatingParticles
//
//  Created by Ira on 8/29/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef animatingParticles_ProtoOrg001_h
#define animatingParticles_ProtoOrg001_h

/**
 * Organism with jelly fish like strcuture
 *
 *
 */
#include "ofmain.h"
#include "IGFace3D.h"

class ProtoOrg001 {
    
public:
    
    // spines with roation with no point at top
  
    int spines; // umbrella spines
    int spineDetail; // cross-supports
    float radius;
    
    ofVec3f apex; // top point
    vector< vector <ofVec3f> > vecs2D;
    vector <IGFace3D>  faces;
    
    // to dynamically fill
    // vecs2D.push_back ( vector<ofVec3f>() );
    vector<int> indices;

    
    // each vertex in multiple faces. Use address of each face to test for
    
    // prototypes
    explicit ProtoOrg001(int spines = 6, int spineDetail = 12, float radius = 1); // cster
    void init(); // do vertex calcs
    void display();
    void display(int renderStyle);
    
   
    
    
private:
    // make more politiclaly correct eventually
    
};


#endif
