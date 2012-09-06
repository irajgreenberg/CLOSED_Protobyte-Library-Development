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
 *
 *
 */
#include "ofmain.h"
#include "Tuple3i.h"
#include "Face3D.h"

namespace ijg {
    
    class ProtoOrgBase {
        
    public:
        
        // composites for convenince
        vector <ofVec3f> verts;
        vector <Tuple3i> inds;
        vector <ofVec3f>  norms;
        vector <Face3D>  faces;
        
        // primitive buffers
        vector <GLint> indices;
        vector <GLfloat>  vertices;
        vector <GLfloat>  normals;
        
        
        // prototypes
        explicit ProtoOrgBase(); // cster 
        virtual ~ProtoOrgBase(); // for super (base) class
        void clearAll();
        void display();
        void display(int renderStyle);
        void displayNormals();
        void move();
        
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
