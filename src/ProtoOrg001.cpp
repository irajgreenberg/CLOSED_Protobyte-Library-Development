//
//  ProtoOrg001.cpp
//  animatingParticles
//
//  Created by Ira on 8/29/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "ProtoOrg001.h"

ProtoOrg001::ProtoOrg001(int spines, int spineDetail, float radius):
spines(spines), spineDetail(spineDetail), radius(radius)
{
}

void ProtoOrg001::init()
{
    // Calculate vertices
    // apex vertex
    float x = (cos(PI/4-PI) - sin(PI/4-PI))*radius;
    float y = radius/2+(sin(PI/4-PI) + cos(PI/4-PI))*radius;
    float z = 0;
    apex = ofVec3f(x, y, z);
    
    float phi = 0; // spine rotaitons
    for(int i=0; i<spines; i++){
        float theta = -PI/4; // spine detail arc
        vecs2D.push_back ( vector<ofVec3f>() ); // add vector for each spine
        for(int j=0; j<spineDetail-1; j++){
            /* 1.  Z rotation for inital spine
             x' = x*cos q - y*sin q
             y' = x*sin q + y*cos q 
             */
            x = (cos(theta) - sin(theta))*radius;
            y = radius/2+(sin(theta) + cos(theta))*radius;
            z = 0;
            
            /* 2.  y rotation to place spines
             // eventually concatenate expressions
             x' = z*sin q + x*cos q 
             z' = z*cos q - x*sin q
             */
            float x2 = z*cos(phi) - x*sin(phi);
            float z2 = z*sin(phi) + x*cos(phi);
            vecs2D[i].push_back (ofVec3f(x2, y, z2));
            theta -= PI/2/spineDetail;
            
        } 
        phi += PI*2/spines;
    }
    // END VERTICES
    
    
    // build faces
      // quad face divided into 2 tri faces
    for(int i=0; i<spines; i++){
        for(int j=0; j<spineDetail-1; j++){
            // open spines
            if (i<spines-1){
                
                if (j<spineDetail-2){
                    faces.push_back(IGFace3D(&(vecs2D[i][j]), &(vecs2D[i][j+1]), &(vecs2D[i+1][j+1])));
                    faces.push_back(IGFace3D(&(vecs2D[i][j]), &(vecs2D[i+1][j+1]), &(vecs2D[i+1][j])));
                    
                } else {
                    // connect spine to apex
                    faces.push_back(IGFace3D(&(vecs2D[i][j]), &apex, &(vecs2D[i+1][j])));
                }
            
                // close spines
            }  else {
                if (j<spineDetail-2){
                    faces.push_back(IGFace3D(&(vecs2D[i][j]), &(vecs2D[i][j+1]), &(vecs2D[0][j+1])));
                    faces.push_back(IGFace3D(&(vecs2D[i][j]), &(vecs2D[0][j+1]), &(vecs2D[0][j])));
                    
                } else {
                    // connect spine to apex
                    faces.push_back(IGFace3D(&(vecs2D[i][j]), &apex, &(vecs2D[0][j])));
                } 
            }
        } // END FACES
        
    }
}

void ProtoOrg001::display(int renderStyle)
{
    switch(renderStyle){
        case 0: // points
            break;
        case 1: // lines
            for(int i=0; i<vecs2D.size(); i++){
                ofBeginShape();
                
                for(int j=0; j<vecs2D[i].size(); j++){
                    ofVertex(vecs2D[i][j].x, vecs2D[i][j].y, vecs2D[i][j].z);
                }
                ofVertex(apex.x, apex.y, apex.z);
                ofEndShape();
            }
            
            break;
        case 2: // faces
            for(int i=0; i<faces.size(); i++){
                faces[i].display();
            }
            break;
        case 3: // points and lines
            break;
        case 4: // points and faces
            break;
        case 5: // lines amd faces
            break;
        case 6: // all
            break;
        default: // faces
            int x = 0;
    }
    
}

void ProtoOrg001::display()
{
    
    for(int i=0; i<vecs2D.size(); i++){
        ofBeginShape();
        
        for(int j=0; j<vecs2D[i].size(); j++){
            ofVertex(vecs2D[i][j].x, vecs2D[i][j].y, vecs2D[i][j].z);
        }
        ofVertex(apex.x, apex.y, apex.z);
        ofEndShape();
    }
    
}