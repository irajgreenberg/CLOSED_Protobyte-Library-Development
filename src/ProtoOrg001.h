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
#include "Face3D.h"

namespace ijg {
    
    class ProtoOrg001 {
        
    public:
        
        // spines with roation with no point at top
        
        int spines; // umbrella spines
        int spineDetail; // cross-supports
        float radius;
        
        ofVec3f apex; // top point
        vector< vector <ofVec3f> > vecs2D;
        vector <ofVec3f> vecs1D;
        vector <GLint> indices;
        vector <GLfloat>  vertices;
        vector <ofVec3f>  norms;
        vector <GLfloat>  normals;
        vector <Face3D>  faces;
        
        // to dynamically fill
        // vecs2D.push_back ( vector<ofVec3f>() );
        //vector<int> indices;
        
        
        
        // each vertex in multiple faces. Use address of each face to test for
        
        // prototypes
        explicit ProtoOrg001(int spines = 6, int spineDetail = 12, float radius = 1); // cster
        void init(); // do vertex calcs
        void display();
        void display(int renderStyle);
        void displayNormals();
        
        
        
        
    private:
        // make more politiclaly correct eventually
        void calculateVertexNormals();
        
    };
    
}
#endif
