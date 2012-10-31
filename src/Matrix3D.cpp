//
//  Matrix3D.cpp
//  Protobyte_iig001
//
//  Created by Ira on 10/26/12.
//
//

#include "Matrix3D.h"

using namespace ijg;

Matrix3D::Matrix3D()
{
    
}

/**
 * Rotation Matrix - around arbitrary axis
 */
void Matrix3D::rotate(float theta, const ofVec3f& axis, ofVec3f& v)
{
    float c = cos(theta);
    float s = sin(theta);
    // row 1
    r0c0 = c + (axis.x*axis.x) * (1-c);
    r0c1 = axis.x*axis.y*(1-c)-s*axis.z;
    r0c2 = axis.z*axis.x*(1-c)+s*axis.y;
    //row 2
    r1c0 = axis.x*axis.y*(1-c) + s*axis.z;
    r1c1 = c + (axis.y*axis.y) * (1-c);
    r1c2 = axis.z*axis.y*(1-c)-s*axis.x;
    //row 3
    r2c0 = axis.x*axis.z*(1-c)-s*axis.y;
    r2c1 = axis.y*axis.z*(1-c)+s*axis.x;
    r2c2 = c + (axis.z*axis.z) * (1-c);
    
    ofVec3f temp = v;
    v.x = temp.x*r0c0 + temp.y*r0c1 + temp.z*r0c2;
    v.y = temp.x*r1c0 + temp.y*r1c1 + temp.z*r1c2;
    v.z = temp.x*r2c0 + temp.y*r2c1 + temp.z*r2c2;
    
}

 ofVec3f Matrix3D::getRotate(float theta, const ofVec3f& axis, const ofVec3f& vec)
{
    float c = cos(theta);
    float s = sin(theta);
    // row 1
    r0c0 = c + (axis.x*axis.x) * (1-c);
    r0c1 = axis.x*axis.y*(1-c)-s*axis.z;
    r0c2 = axis.z*axis.x*(1-c)+s*axis.y;
    //row 2
    r1c0 = axis.x*axis.y*(1-c) + s*axis.z;
    r1c1 = c + (axis.y*axis.y) * (1-c);
    r1c2 = axis.z*axis.y*(1-c)-s*axis.x;
    //row 3
    r2c0 = axis.x*axis.z*(1-c)-s*axis.y;
    r2c1 = axis.y*axis.z*(1-c)+s*axis.x;
    r2c2 = c + (axis.z*axis.z) * (1-c);
    
    ofVec3f temp;
    temp.x = vec.x*r0c0 + vec.y*r0c1 + vec.z*r0c2;
    temp.y = vec.x*r1c0 + vec.y*r1c1 + vec.z*r1c2;
    temp.z = vec.x*r2c0 + vec.y*r2c1 + vec.z*r2c2;
    return temp;
}

void Matrix3D::inverse()
{
    
}
void Matrix3D::determinent()
{
    
}
