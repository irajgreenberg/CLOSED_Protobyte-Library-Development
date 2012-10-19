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

Tube::Tube(const Spline3d& path,  float radii[]): // varied thickness
path(path), radii(radii){
    
}

Tube::Tube(const Spline3d& path, float radius):
path(path), radius(radius){
    
}

// overrides base class
void Tube::calcVerts()
{
    
}

void Tube::calcInds()
{
    
}

Spline3d& Tube::getPath()
{
    return path;
}