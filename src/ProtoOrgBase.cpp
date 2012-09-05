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

void ProtoOrgBase::display(int renderStyle)
{
    
}

void ProtoOrgBase::displayNormals()
{
    
}

void ProtoOrgBase::move()
{
    
}

void ProtoOrgBase::init()
{
    
}

// vertex normals calculations
void ProtoOrgBase::calculateVertexNormals()
{
    float theta = 0;
    for (int i=0; i<3; i++){
        verts.push_back(ofVec3f(cos(theta), sin(theta)));
        theta += PI*2/3;
    }
    
    faces.push_back(Face3D(&verts[0], &verts[1], &verts[2]));
}