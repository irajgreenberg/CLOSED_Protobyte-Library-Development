//
//  SubDivSurf.cpp
//  Protobyte_iig001
//
//  Created by Ira on 11/10/12.
//
//

#include "SubDivSurf.h"
using namespace ijg;


namespace ijg {
    std::ostream& operator<<(std::ostream& output, const SubDivSurf& surf)
    {
     std::cout<< (ijg::ProtoOrgBase)surf << std::endl;
        output << "SubDivsurv obj: [ subdivLevel = "<< surf.subdivLevel <<" ]";
        return output;
    }
}

SubDivSurf::SubDivSurf()
{ }
SubDivSurf::SubDivSurf(ofVec3f vecs[3], const ofVec3f& loc, const Dimension3D& dim, int subdivLevel):
ProtoOrgBase(loc, dim), v0(vecs[0]), v1(vecs[1]), v2(vecs[2]), subdivLevel(subdivLevel){
    init();
}

// overrides base class
void SubDivSurf::calcVerts()
{
    // initival vecs
    tempVecs.push_back(v0);
    tempVecs.push_back(v1);
    tempVecs.push_back(v2);
    
    
    // subdivide 1 level
    it = tempVecs.begin();
    ++it;
    tempVecs.insert(it, (v0+v1)/2);//+ofRandom(-.5, .5));
    ++it;
    tempVecs.insert(it, (v1+v2)/2);//+ofRandom(-.5, .5));
    ++it;
    tempVecs.insert(it, (v2+v0)/2);//+ofRandom(-.5, .5));
    
    
    // read list
    list<ofVec3f>::iterator i;
    for(i=tempVecs.begin(); i != tempVecs.end(); ++i) {
        verts.push_back(*i);
        cout  << "tempVecs = " << *i << std::endl;
    }
    
    for(int i=0; i< verts.size(); ++i) {
        //cout  << "verts = " << verts.at(i) << std::endl;
    }
    
}

/**
 * Divide each tri face into 4 tri faces
 */
void SubDivSurf::calcInds()
{
    inds.push_back( Tuple3i(0,1,5));
    inds.push_back( Tuple3i(1,2,3));
    inds.push_back( Tuple3i(1,3,5));
    inds.push_back( Tuple3i(4,5,3));
}

/*void sub(Face3D f){
    ofVec3f v0 = f.v0;
    ofVec3f v1 = f.v1;
    ofVec3f v2 = f.v2;
    // initival vecs
    tempVecs.push_back(v0);
    tempVecs.push_back(v1);
    tempVecs.push_back(v2);
    
    
    // subdivide 1 level
    it = tempVecs.begin();
    ++it;
    tempVecs.insert(it, (v0+v1)/2);//+ofRandom(-.5, .5));
    ++it;
    tempVecs.insert(it, (v1+v2)/2);//+ofRandom(-.5, .5));
    ++it;
    tempVecs.insert(it, (v2+v0)/2);//+ofRandom(-.5, .5));
    
}*/


// getters & setters
void SubDivSurf::setSubdivLevel(int subdivLevel)
{
    this->subdivLevel = subdivLevel;
}

int SubDivSurf::getSubdivLevel() const
{
    return subdivLevel;
}