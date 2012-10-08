//
//  ProtoToroid.cpp
//  Protobyte_iig001
//
//  Created by Ira on 10/6/12.
//
//

#include "ProtoToroid.h"


namespace ijg {
    
    std::ostream& operator<<(std::ostream& output, const ProtoToroid& toroid)
    {
        std::cout<< (ijg::ProtoOrgBase)toroid << std::endl;
        output << "ProtoToroid obj: [ ringCount = "<<toroid.getRingCount()<<" ringDetail = "<<toroid.getRingDetail()<<" ringRadius = "<<toroid.getRingRadius()<<" ]";
        return output;
    }
}


using namespace ijg;

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
            x = 1-ringRadius*1.2 + (cos(theta) - sin(theta))*ringRadius;
            y = (sin(theta) + cos(theta))*ringRadius;
            z = 0;
            
            // STAR 
            /*
             // 1.  Z rotation for inital ring
             if (i % 2==0) {
             x = 1-ringRadius + (cos(theta) - sin(theta))*ringRadius;
             y = (sin(theta) + cos(theta))*ringRadius;
             z = 0;
             } else {
             float r = ofRandom(1.1, 1.2);
             x = r-ringRadius*1.2 + (cos(theta) - sin(theta))*ringRadius*r;
             y = (sin(theta) + cos(theta))*ringRadius;
             z = 0;
             }*/
            
            // 2.  y rotation to place rings
            float x2 = z*cos(phi) - x*sin(phi);
            float z2 = z*sin(phi) + x*cos(phi);
            
            //std::cout<<"x2 = "<< x2<< std::endl;
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
            
            int i0 = i*ringDetail + j;
            int i1 = (i+1)*ringDetail + j;
            int i2 = i*ringDetail + j+1;
            int i3 = (i+1)*ringDetail + j+1;
            int i4 = j;
            int i5 = i*ringDetail;
            int i6 = ringDetail + j+1;
            int i7 = (i+1)*ringDetail;
            int i8 = j+1;
            
            if(i<ringCount-1){
                if(j<ringDetail-1){
                    inds.push_back( Tuple3i(i0, i2, i3) );
                    inds.push_back( Tuple3i(i0, i3, i1) );
                    
                } else {
                    // j+1 = 0
                    inds.push_back( Tuple3i(i0, i5, i7) );
                    inds.push_back( Tuple3i(i0, i7, i1) );
                }
            } else {
                if(j<ringDetail-1){
                    //i+1 = 0
                    inds.push_back( Tuple3i(i0, i2, i8) );
                    inds.push_back( Tuple3i(i0, i8, i4) );
                    
                } else {
                    //i+1 =0, j+1 = 0
                    inds.push_back( Tuple3i(i0, i5, 0) );
                    inds.push_back( Tuple3i(i0, 0, i4) );
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
