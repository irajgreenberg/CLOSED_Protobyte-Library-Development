//
//  ProtoTetrahedron.cpp
//  Protobyte_iig001
//
//  Created by Ira on 11/4/12.
//
//

#include "ProtoTetrahedron.h"

// temp prototype
void subDivide();

namespace ijg {
    std::ostream& operator<<(std::ostream& out, const ProtoTetrahedron& tetrahedron)
    {
        std::cout<< (ijg::ProtoOrgBase)tetrahedron << std::endl;
        out << "ProtoToroid obj: [ subdivisionLevel = "<< tetrahedron.subdivisionLevel << " ]";
        return out;
    }
}

using namespace ijg;
ProtoTetrahedron::ProtoTetrahedron()
{
    
}

ProtoTetrahedron::ProtoTetrahedron(const ofVec3f& loc, const Dimension3D& dim, int subdivisionLevel):
ProtoOrgBase(loc, dim), subdivisionLevel(subdivisionLevel){
    init();
}

// overrides base class
void ProtoTetrahedron::calcVerts()
{
    // unit size
    float radius = .5;
    float theta = 0;
    float h = .816496581; // = sqrt(2)/sqrt(3)
    
    
    //base pts
    for(int i=0; i<3; i++){
        verts.push_back(ofVec3f(cos(theta)*radius, sin(theta)*radius));
        theta += PI*2/3;
    }
    // top pt
    verts.push_back(ofVec3f(0, 0, -h));
    
    // for initial faces
    inds.push_back( Tuple3i(0, 1, 2) );
    inds.push_back( Tuple3i(0, 3, 1) );
    inds.push_back( Tuple3i(1, 3, 2) );
    inds.push_back( Tuple3i(2, 3, 0) );
    
    // base faces
    for(int i=0; i<4; i++){
        ofVec3f* v1 = &verts.at(inds.at(i).elem0);
        ofVec3f* v2 = &verts.at(inds.at(i).elem1);
        ofVec3f* v3 = &verts.at(inds.at(i).elem2);
        tempFaces.push_back(Face3D(v1, v2, v3));
    }
    
    for(int i=0; i<subdivisionLevel; i++){
        
    }
    
}

void ProtoTetrahedron::calcInds()
{
    inds.push_back( Tuple3i(0, 1, 2) );
    inds.push_back( Tuple3i(0, 3, 1) );
    inds.push_back( Tuple3i(1, 3, 2) );
    inds.push_back( Tuple3i(2, 3, 0) );
    
    
}

// getters/setters
void ProtoTetrahedron::setSubdivisionLevel(int subdivisionLevel)
{
    this->subdivisionLevel = subdivisionLevel;
}

int ProtoTetrahedron::getSubdivisionLevel() const
{
    return subdivisionLevel;
}