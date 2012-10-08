//
//  ExtrudeObj.h
//  Protobyte Library V01
//
//  Created by Ira Greenberg on 8/2/11.
//  Copyright 2011 SMU. All rights reserved.
//
// Library Usage:
// This work is licensed under the Creative Commons 
// Attribution-NonCommercial-ShareAlike 3.0 Unported License. 
// To view a copy of this license, visit 
// http://creativecommons.org/licenses/by-nc-sa/3.0/ 
// or send a letter to Creative Commons, 
// 444 Castro Street, Suite 900, 
// Mountain View, California, 94041, USA.
//

#ifndef Protobyte_Library_V01_ExtrudeObj_h
#define Protobyte_Library_V01_ExtrudeObj_h

#include "Curve3d.h"
#include "Geom3d.h"
#include "Matrix4d.h"
//#include "Bourke.h"



class ExtrudeObj: public Geom3d {
    
public:
    ExtrudeObj();
    ExtrudeObj(Curve3d* path, int detail);
	ExtrudeObj(Curve3d* path, float radius, int detail);
    
    ~ExtrudeObj();
    void displayPath();
    void setRadius(float radius);
    float getRadius();
    void checkIntersection();
    
private:
    float radius;
    Curve3d* path;
    int pathCount;
    Vector3df* controlPts;
    std::vector<Vector3df> pathVertices;
    Vector3df* pathVerts;
    
    Vector3df* unalignedVerts; // used to allign cross-sections
    
    // temporary stuff
    Vector3df tempEllipse[24];
    
    
    void init();    
    void createVertices();
    void createIndices();
    
    
};


#endif
