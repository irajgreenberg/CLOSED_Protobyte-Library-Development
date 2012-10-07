//
//  ProtoToroid.cpp
//  Protobyte_iig001
//
//  Created by Ira on 10/6/12.
//
//

#include "ProtoToroid.h"
using namespace ijg;


std::ostream& operator<<(std::ostream& output, const ProtoToroid& toroid)
{
    //output << "Dimenion3D obj: [ w = "<<dim.w<<" h = "<<dim.h<<" d = "<<dim.d<<" ]";
    return output;
    
    output << "ProtoToroid obj: [ ringCount = "<<toroid.getRingCount()<<" ringDetail = "<<toroid.getRingDetail()<<" ringRadius = "<<toroid.getRingRadius()<<" ]";
}

ProtoToroid::ProtoToroid(const ofVec3f& loc, const Dimension3D& dim, int ringCount, int ringDetail, float ringRadius):
ProtoOrgBase(loc, dim),ringCount(ringCount), ringDetail(ringDetail), ringRadius(ringRadius) {
    init();
}

void ProtoToroid::calcVerts()
{
    // vertices
    float x, y, z;
    float phi = 0; // ring rotations
    for(int i=0; i<ringCount; i++){
        float theta = 0;
        // START CALCULATE VERTICES
        for(int j=0; j<ringDetail; j++){
            // 1.  Z rotation for inital ring
            x = 1-ringRadius + (cos(theta) - sin(theta))*ringRadius;
            y = (sin(theta) + cos(theta))*ringRadius;
            z = 0;
            
            // 2.  y rotation to place rings
            float x2 = z*cos(phi) - x*sin(phi);
            float z2 = z*sin(phi) + x*cos(phi);
            
            std::cout<<"x2 = "<< x2<< std::endl;
            // fill vertices with floats
            verts.push_back( ofVec3f(x2, y, z2) );
            
            theta -= PI*2/ringDetail;
        }
        phi += PI*2/ringCount;
    }
}

void ProtoToroid::calcInds(){
    // indices
    for(int i=0; i<ringCount; i++){
        for(int j=0; j<ringDetail; j++){
            
            int t1_0 = i*ringDetail + j;
            int t1_1 = (i+1)*ringDetail + j;
            int t1_2 = i*ringDetail + j+1;
            
            int t2_0 = (i+1)*ringDetail + j;
            int t2_1 = i*ringDetail + j+1;
            int t2_2 = (i+1)*ringDetail + j+1;
            
            // std::cout<<"t1_0 = " << t1_0 <<std::endl;
            // std::cout<<"t1_1 = " << t1_1 <<std::endl;
            // std::cout<<"t1_2 = " << t1_2 <<std::endl;
            if(j<ringDetail-1){
                
                if(i<ringCount-1){
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


// getters & setters
int ProtoToroid::getRingCount() const
{
    return ringCount;
}

void ProtoToroid::setRingCount(int ringCount)
{
    this->ringCount = ringCount;
}

int ProtoToroid::getRingDetail() const
{
    return ringDetail;
}

void ProtoToroid::setRingDetail(int ringDetail)
{
    this->ringDetail = ringDetail;
}

float ProtoToroid::getRingRadius() const
{
    return ringRadius;
}

void ProtoToroid::setRingRadius(float ringRadius)
{
    this->ringRadius = ringRadius;
}
