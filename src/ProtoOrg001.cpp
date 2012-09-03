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

    // apex vertex
    float x = (cos(PI/4-PI) - sin(PI/4-PI))*radius;
    float y = radius/2+(sin(PI/4-PI) + cos(PI/4-PI))*radius;
    float z = 0;
    apex = ofVec3f(x, y, z);
    
    float phi = 0; // spine rotations
    for(int i=0; i<spines; i++){
        float theta = -PI/4; // spine detail arc
        
        // add each vector to 2d vector
        vecs2D.push_back ( vector<ofVec3f>() ); 
        
        // START CALCULATE VERTICES
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
            
            // vertices stored as 2d vector of ofVec3f's
            vecs2D[i].push_back(ofVec3f(x2, y, z2));
            
            // fill vertices with floats
            vertices.push_back(x2);
            vertices.push_back(y);
            vertices.push_back(z2);
            //vecs1D.push_back(ofVec3f(x2, y, z2));
            theta -= PI/2/spineDetail;
            
        } 
        phi += PI*2/spines;
    }
     // add final apex
    vertices.push_back(apex.x);
    vertices.push_back(apex.y);
    vertices.push_back(apex.z);
    // END VERTICES
    
    
      // START CALCULATE FACES AND INDICES
      // quad face divided into 2 tri faces
    
    // NOTE put Apex at end of vertices array
   int apexPos = spines * (spineDetail-1);
    for(int i=0; i<spines; i++){
        for(int j=0; j<spineDetail-1; j++){
            GLint sd = spineDetail-1;
            GLint prevBot = sd*i + j;
            GLint prevTop = sd*i + j+1;
            GLint nextBot = sd*(i+1) + j;
            GLint nextTop = sd*(i+1) + j+1;
            
            // open spines
            if (i<spines-1){
                
                if (j<spineDetail-2){
                    faces.push_back(IGFace3D(&(vecs2D[i][j]), &(vecs2D[i][j+1]), &(vecs2D[i+1][j+1])));
                    faces.push_back(IGFace3D(&(vecs2D[i][j]), &(vecs2D[i+1][j+1]), &(vecs2D[i+1][j])));
                    
                    indices.push_back(prevBot); indices.push_back(prevTop); indices.push_back(nextTop);
                    indices.push_back(prevBot); indices.push_back(nextTop); indices.push_back(nextBot);
                    
                } else {
                    // connect spine to apex
                    faces.push_back(IGFace3D(&(vecs2D[i][j]), &apex, &(vecs2D[i+1][j])));
                    
                    indices.push_back(prevBot); indices.push_back(apexPos); indices.push_back(nextBot);
                }
            
                // close spines
            }  else {
                if (j<spineDetail-2){
                    faces.push_back(IGFace3D(&(vecs2D[i][j]), &(vecs2D[i][j+1]), &(vecs2D[0][j+1])));
                    faces.push_back(IGFace3D(&(vecs2D[i][j]), &(vecs2D[0][j+1]), &(vecs2D[0][j])));
                    
                    indices.push_back(prevBot); indices.push_back(prevTop); indices.push_back(j+1);
                    indices.push_back(prevBot); indices.push_back(j+1); indices.push_back(j);
                    
                } else {
                    // connect spine to apex
                    faces.push_back(IGFace3D(&(vecs2D[i][j]), &apex, &(vecs2D[0][j])));
                    
                    indices.push_back(prevBot); indices.push_back(apexPos); indices.push_back(j);
                } 
            }
        } // END CALCULATE FACES AND INDICES
        
    }
    
    // calc faces (again for now)
    
    for(int i=0; i<indices.size(); i++){
        //std::cout << "indices["<<i<<"] = " << (int)indices[i] << std::endl;
        //if((i+1)%3==0) std::cout << "\n";
    }
}

void ProtoOrg001::calculateVertexNormals()
{
    for(int i=0; i<vertices.size(); i++){
        for(int j=0; j<faces.size(); j++){
        
        }
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
    std::cout << "indices.size() = " << indices.size() << std::endl;
    
    glEnableClientState (GL_VERTEX_ARRAY);
	//glEnableClientState (GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	
	//bind the ground texture
	//glBindTexture(GL_TEXTURE_2D, gltexture);
    
	//this is a pointer to the texture coords in the vertices array
	//char *evilPointer = (char *)vertexlist;
	//evilPointer+=sizeof(GL_FLOAT)*3;
	
	//set the pointers
	//glTexCoordPointer(2,GL_FLOAT,sizeof(GL_FLOAT) * 5,evilPointer);
	glVertexPointer (3, GL_FLOAT, 0, &vertices[0]);
	//glNormalPointer(GL_FLOAT, 0, normallist);
	
	//Draw Protobyte
    int elementCount = ((spines*(spineDetail-1)*2)+spines)*3;
	glDrawElements (GL_TRIANGLE_STRIP, indices.size(), GL_UNSIGNED_INT, &indices[0]);
	
	//disable the client state and texture
	//glDisable(GL_TEXTURE_2D);
	//glDisableClientState(GL_NORMAL_ARRAY);
	//glDisableClientState (GL_TEXTURE_COORD_ARRAY);
	glDisableClientState (GL_VERTEX_ARRAY);
	
    
}



void ProtoOrg001::displayNormals()
{
    for(int i=0; i<faces.size(); i++){
        faces[i].displayNormal();
    }

}