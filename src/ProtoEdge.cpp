//
//  ProtoEdge.cpp
//  Protobyte_iig001
//
//  Created by Ira on 11/10/12.
//
//

#include "ProtoEdge.h"
using namespace ijg;

ProtoEdge::ProtoEdge()
{
}

ProtoEdge::ProtoEdge(ofVec3f* p_v0, ofVec3f* p_v1):
p_v0(p_v0), p_v1(p_v1)
{
    
}

// don't implement these
//ProtoEdge::ProtoEdge(const ProtoEdge& edge){}
//ProtoEdge& ProtoEdge::operator=(const ProtoEdge& edge){}

void ProtoEdge::setV0(ofVec3f* p_v0)
{
    this->p_v0 = p_v0;
}

void ProtoEdge::setV1(ofVec3f* p_v1)
{
    this->p_v1 = p_v1;
}

ofVec3f* ProtoEdge::getV0()
{
    return p_v0;
}

ofVec3f* ProtoEdge::getV1()
{
    return p_v1;
}

ofVec3f* ProtoEdge::getMidV()
{
    return p_midV;
}

void ProtoEdge::setMidV(ofVec3f* p_midV)
{
    this->p_midV = p_midV;
}
