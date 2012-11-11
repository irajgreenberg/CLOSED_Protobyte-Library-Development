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
#include "ProtoFace.h"
#include "ProtoEdge.h"
#include "Dimension3D.h"

#include <iostream>
#include <fstream>
#include<sys/stat.h>
#include<sys/types.h>

namespace ijg {
    
    class ProtoOrgBase {
        
    public:
        
        friend std::ostream& operator<<(std::ostream& output, const ProtoOrgBase& protoBase);
        ofVec3f loc;
        Dimension3D dim;
        
        // composites for convenince
        vector <ofVec3f> verts;
        vector <Tuple3i> inds;
        vector <ofVec3f>  norms;
        vector <ofColor> colrs;
        vector <ProtoFace>  faces;
        vector <ProtoEdge>  edges;
        
        // primitive buffers
        vector <GLint> indices;
        vector <GLfloat>  vertices;
        vector <GLfloat>  colors;
        vector <GLfloat>  normals;
        
        // for sorting – front to back for transparency - NOT CURRENTLY IMPLEMENTED
        vector<GLfloat> tempVecs;
        
        
        // prototypes
        ProtoOrgBase();  // cster
        ProtoOrgBase(const ofVec3f& loc, const Dimension3D& dim); // cster
        ProtoOrgBase(const ofVec3f& loc, const Dimension3D& dim, const ofColor& colr); // cster
        ProtoOrgBase(const ofVec3f& loc, const Dimension3D& dim, std::vector<ofColor> colrs); // cster
        virtual ~ProtoOrgBase(); // for super (base) class
        void clearAll();
        void display();
        void display(int renderStyle);
        void displayNormals(float len);
        void move();
        
        //NOT CURRENTLY IMPLEMENTED
        void quickFaceSort(vector <GLint>indices, vector <GLfloat>vertices, vector <GLfloat>normals, int left, int right);
        
        // export ProtoObj to STL format
        void exportSTL();
        
        //VertexPacked_VNC getData();
        
    private:
        
        
    protected:
        /***overridden in subclasses***/
        // vertex calculations
        void init();
            
        // vertex calculations
        virtual void calcVerts();
        
        // indices calculations
        virtual void calcInds();
        
        /***used by subclasses***/
        // vertex normals calculations
        void calcNorms();
        
        void calcFaces();
        
        // primitves for drawElements
        void calcPrimitives();
        
    };
}

#endif
