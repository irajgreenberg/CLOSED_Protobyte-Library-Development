//
//  ProtoOrg002.cpp
//  Protobyte_iig001
//
//  Created by Ira on 9/5/12.
//
//

#include "ProtoOrg002.h"

using namespace ijg;

ProtoOrg002::ProtoOrg002(int spines, int spineDetail, bool isClosed, float radius, float height):
spines(spines), spineDetail(spineDetail), isClosed(isClosed), radius(radius), height(height){
    init();
}


// overridden methods

// vertex calculations
void ProtoOrg002::init()
{
    clearAll(); // ensure vectors are cleaned
    calcVerts();
    calcInds();
    calcFaces();
    calcNorms();
    calcPrimitives();
}

// vertex calculations
void ProtoOrg002::calcVerts()
{
    // vertices
    float x, y, z;
    float phi = 0; // spine rotations
    for(int i=0; i<spines; i++){
        float theta = -PI/4; // spine detail arc
        // START CALCULATE VERTICES
        for(int j=0; j<spineDetail; j++){
            // 1.  Z rotation for inital spine
            x = (cos(theta) - sin(theta))*(radius+ofRandom(.01));
            y = radius/2+(sin(theta) + cos(theta))*(radius+ofRandom(.01));
            z = 0;
            
            // 2.  y rotation to place spines
            float x2 = z*cos(phi) - x*sin(phi);
            float z2 = z*sin(phi) + x*cos(phi);
            
            
            // fill vertices with floats
            verts.push_back( ofVec3f(x2, y, z2) );
            
            theta -= PI/2/spineDetail;
        }
        phi += PI*2/spines;
    }
}

void ProtoOrg002::calcInds(){
    // indices
    for(int i=0; i<spines; i++){
        for(int j=0; j<spineDetail; j++){
            
            int t1_0 = i*spineDetail + j;
            int t1_1 = (i+1)*spineDetail + j;
            int t1_2 = i*spineDetail + j+1;
            
            int t2_0 = (i+1)*spineDetail + j;
            int t2_1 = i*spineDetail + j+1;
            int t2_2 = (i+1)*spineDetail + j+1;
            
            // std::cout<<"t1_0 = " << t1_0 <<std::endl;
            // std::cout<<"t1_1 = " << t1_1 <<std::endl;
            // std::cout<<"t1_2 = " << t1_2 <<std::endl;
            if(j<spineDetail-1){
                
                if(i<spines-1){
                    inds.push_back( Tuple3i(t1_2, t1_1, t1_0) );
                    inds.push_back( Tuple3i(t2_0, t2_1, t2_2) );
                    
                } else {
                    inds.push_back( Tuple3i(t1_2, j, t1_0) );
                    inds.push_back( Tuple3i(j, t2_1, j+1) );
                }
            }
        }
    }
}
    
    void ProtoOrg002::calcFaces()
    {
        // calc faces
        for(int i=0; i<inds.size(); i++){
            faces.push_back( Face3D(&verts[inds[i].elem0], &verts[inds[i].elem1], &verts[inds[i].elem2]) );
            //std::cout<<"inds["<<i<<"].elem0 = " <<inds[i].elem0 <<std::endl;
            //std::cout<<"inds["<<i<<"].elem1 = " <<inds[i].elem1 <<std::endl;
            //std::cout<<"inds["<<i<<"].elem2 = " <<inds[i].elem2 <<std::endl;
        }
        
    }
    
    
    // getters & setters
    void ProtoOrg002::setSpines(int spines)
    {
        this->spines = spines;
        init();
    }
    
    int ProtoOrg002::getSpines()
    {
        return spines;
    }
    
    void ProtoOrg002::setSpineDetail(int spineDetail)
    {
        this->spineDetail = spineDetail;
        init();
    }
    
    int ProtoOrg002::getSpineDetail()
    {
        return spineDetail;
    }
    
    void ProtoOrg002::setIsClosed(bool isClosed)
    {
        this->isClosed = isClosed;
    }
    
    bool ProtoOrg002::getIsClosed(){
        return isClosed;
    }