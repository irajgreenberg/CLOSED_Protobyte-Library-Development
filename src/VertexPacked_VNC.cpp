//
//  VertexPacked_VNC.cpp
//  Protobyte_iig001
//
//  Created by Ira on 9/3/12.
//
//

#include "VertexPacked_VNC.h"

using namespace ijg;

VertexPacked_VNC::VertexPacked_VNC(float x, float y, float z,
                                   float r, float g, float b, float a):
x(x), y(y), z(z), r(r), g(g), b(b), a(a)
{
    vec.x = x;
    vec.y = y;
    vec.z = z;
    rgba[0] = r;
    rgba[1] = g;
    rgba[2] = b;
    rgba[3] = a;
    init();
}

VertexPacked_VNC::VertexPacked_VNC(const ofVec3f& vec)
{
    this->vec = vec;
    x = vec.x;
    y = vec.y;
    z = vec.z;
    init();
}

VertexPacked_VNC::VertexPacked_VNC(const ofVec3f& vec, float rgba[])
{
    this->vec = vec;
    x = vec.x;
    y = vec.y;
    z = vec.z;
    
    setRGBA(rgba);
    init();
}

void VertexPacked_VNC::init()
{
    nx = ny = nz = 0;
}

void VertexPacked_VNC::setNorm(const ofVec3f& norm)
{
    this->norm = norm;
    nx = norm.x;
    ny = norm.y;
    nz = norm.z;
}


void VertexPacked_VNC::setRGBA(float r, float g, float b, float a)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

void VertexPacked_VNC::setRGBA(float rgba[])
{
    this->rgba[0] = rgba[0];
    this->rgba[1] = rgba[1];
    this->rgba[2] = rgba[2];
    this->rgba[3] = rgba[3];
    r = rgba[0];
    g = rgba[1];
    b = rgba[2];
    a = rgba[3];
}


float* VertexPacked_VNC::getData()
{
    data[0]=x;
    data[1]=y;
    data[2]=z;
    data[3]=nx;
    data[4]=ny;
    data[5]=nz;
    data[6]=r;
    data[7]=g;
    data[8]=b;
    data[9]=a;
    
    return data;
}
