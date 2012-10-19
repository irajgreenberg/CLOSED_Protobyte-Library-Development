//
//  Tube.cpp
//  Protobyte_iig001
//
//  Created by Ira on 10/17/12.
//
//

#include "Tube.h"

using namespace ijg;

std::ostream& operator<<(std::ostream& out, const Tube& tube)
{
    out << "No Information to report at the moment";
    return out;
}

Tube::Tube()
{
    
}

Tube::Tube(const ofVec3f& loc, const Dimension3D& dim, const Spline3d& path,  float radii[]): // varied thickness
ProtoOrgBase(loc, dim), path(path), radii(radii){
    
}

Tube::Tube(const ofVec3f& loc, const Dimension3D& dim, const Spline3d& path, float radius):
ProtoOrgBase(loc, dim), path(path), radius(radius){
    
}

// overrides base class
void Tube::calcVerts()
{
    
}

void Tube::calcInds()
{
    
}

const Spline3d& Tube::getPath() const
{
    return path;
}