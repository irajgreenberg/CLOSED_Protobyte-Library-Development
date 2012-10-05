//
//  ProtoOrgBase.h
//  animatingParticles
//
//  Created by Ira on 8/29/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef animatingParticles_ProtoOrg002_h
#define animatingParticles_ProtoOrg002_h

/**
 * Base class for ProtoOrganisms
 * Quick sort from http://www.algolist.net/Algorithms/Sorting/Quicksort
 *
 */
#include "ofmain.h"
#include "Tuple3i.h"
#include "Face3D.h"

#include <iostream>
#include <fstream>
#include<sys/stat.h>
#include<sys/types.h>

namespace ijg {
    
    class ProtoOrgBase {
        
    public:
        
        // composites for convenince
        vector <ofVec3f> verts;
        vector <Tuple3i> inds;
        vector <ofVec3f>  norms;
        vector <ofColor> colrs;
        vector <Face3D>  faces;
        
        // primitive buffers
        vector <GLint> indices;
        vector <GLfloat>  vertices;
        vector <GLfloat>  colors;
        vector <GLfloat>  normals;
        
        // for sorting – front to back for transparency
        vector<GLfloat> tempVecs;
        
        
        // prototypes
        explicit ProtoOrgBase(); // cster 
        virtual ~ProtoOrgBase(); // for super (base) class
        void clearAll();
        void display();
        void display(int renderStyle);
        void displayNormals();
        void move();
        
        void quickFaceSort(vector <GLint>indices, vector <GLfloat>vertices, vector <GLfloat>normals, int left, int right);
        
        // export ProtoObj to STL format
        void exportSTL();
        
        //VertexPacked_VNC getData();
        
    private:
        
        
    protected:
        /***overridden in subclasses***/
        // vertex calculations
        virtual void init();
            
        // vertex calculations
        virtual void calcVerts();
        
        // indices calculations
        virtual void calcInds();
        
        /***used by subclasses***/
        // vertex normals calculations
        void calcNorms();
        
        // primitves for drawElements
        void calcPrimitives();
        
    };
}

#endif
