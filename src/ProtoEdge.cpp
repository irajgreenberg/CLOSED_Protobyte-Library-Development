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

ProtoEdge::ProtoEdge(const ofVec3f& v0, const ofVec3f& v1):
v0(v0), v1(v1)
{
    
}

// don't implement these
//ProtoEdge::ProtoEdge(const ProtoEdge& edge){}
//ProtoEdge& ProtoEdge::operator=(const ProtoEdge& edge){}

void ProtoEdge::setP_v0(ofVec3f* p_v0)
{
    this->p_v0 = p_v0;
}

void ProtoEdge::setP_v1(ofVec3f* p_v1)
{
    this->p_v1 = p_v1;
}

void ProtoEdge::setP_midV(ofVec3f* p_midV)
{
    this->p_midV = p_midV;
}


ofVec3f* ProtoEdge::getP_v0()
{
    return p_v0;
}

ofVec3f* ProtoEdge::getP_v1()
{
    return p_v1;
}

ofVec3f* ProtoEdge::getP_midV()
{
    return p_midV;
}

void ProtoEdge::setV0(const ofVec3f& v0)
{
    this->v0 = v0;
}
void ProtoEdge::setV1(const ofVec3f& v1)
{
    this->v1 = v1;
}

void ProtoEdge::setMidV(const ofVec3f& midV)
{
    this->midV = midV;
}

ofVec3f& ProtoEdge::getV0()
{
    return v0;
}
ofVec3f& ProtoEdge::getV1()
{
    return v1;
}
ofVec3f& ProtoEdge::getMidV()
{
    return midV;
}

