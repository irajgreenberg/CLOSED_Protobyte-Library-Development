//
//  ProtoOrgBase.cpp
//  Protobyte_iig001
//
//  Created by Ira on 9/5/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "ProtoOrgBase.h"

using namespace ijg;

ProtoOrgBase::ProtoOrgBase()
{
    init();
}

ProtoOrgBase::~ProtoOrgBase()
{
    
}

void ProtoOrgBase::clearAll()
{
    if(verts.size()>0){
        verts.clear();
    }
    if(inds.size()>0){
        inds.clear();
    }
    if(faces.size()>0){
        faces.clear();
    }
    if(norms.size()>0){
        norms.clear();
    }
    if(vertices.size()>0){
        vertices.clear();
    }
    if(indices.size()>0){
        indices.clear();
    }
    if(normals.size()>0){
        normals.clear();
    }
}

void ProtoOrgBase::init()
{
    clearAll();
    calcVerts();
    calcNorms();
    calcPrimitives();
}

void ProtoOrgBase::calcVerts()
{
    // verts
    float theta = 0;
    for (int i=0; i<3; i++){
        verts.push_back(ofVec3f(cos(theta), sin(theta)));
        theta += PI*2/3;
        
    }
    // inds
    inds.push_back(Tuple3i(0, 1, 2));
    faces.push_back(Face3D(&verts[0], &verts[1], &verts[2]));
}

void ProtoOrgBase::calcInds()
{
}

void ProtoOrgBase::calcNorms()
{
    // get face normals
    for ( int i=0; i<faces.size(); i++){
        norms.push_back(ofVec3f(faces[i].getNormal()));
    }
    
    // vertex normals
    for (int i=0; i<verts.size(); i++){
        ofVec3f temp;
        for (int j=0; j<faces.size(); j++){
            if(&verts[i] == faces[j].p_vecs[0]|| &verts[i] == faces[j].p_vecs[1] || &verts[i] == faces[j].p_vecs[2]){
               // std::cout << "in normals loop" << std::endl;
                temp += faces[j].getNormal();
            }
            temp.normalize();
            norms.push_back(temp);
        }
    }
}

void ProtoOrgBase::calcPrimitives()
{
    // vertices
    for (int i=0; i<verts.size(); i++){
        vertices.push_back(verts[i].x);
        vertices.push_back(verts[i].y);
        vertices.push_back(verts[i].z);
    }
    // indices
    for (int i=0; i<inds.size(); i++){
        indices.push_back(inds[i].elem0);
        indices.push_back(inds[i].elem1);
        indices.push_back(inds[i].elem2);
    }
    
    // normals
    for (int i=0; i<norms.size(); i++){
        normals.push_back(norms[i].x);
        normals.push_back(norms[i].y);
        normals.push_back(norms[i].z);
    }

}

void ProtoOrgBase::display()
{

    //std::cout << "indices.size() = " << indices.size() << std::endl;
    
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
	glNormalPointer(GL_FLOAT, 0, &normals[0]);
	
	//Draw Protobyte
	glDrawElements (GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, &indices[0]);
	
	//disable the client state and texture
	//glDisable(GL_TEXTURE_2D);
	glDisableClientState(GL_NORMAL_ARRAY);
	//glDisableClientState (GL_TEXTURE_COORD_ARRAY);
	glDisableClientState (GL_VERTEX_ARRAY);

}


 void  ProtoOrgBase::displayNormals()
{
    for(int i=0; i<faces.size(); i++){
        faces[i].displayNormal();
    }

}

void ProtoOrgBase::move()
{
    
}











