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

Tube::Tube(const ofVec3f& loc, const Dimension3D& dim, const Spline3d& path,  float radii[], int crossSectionDetail): // varied thickness
ProtoOrgBase(loc, dim), path(path), crossSectionDetail(crossSectionDetail){
     for (int i = 0; i < path.getVertsLength(); i++) {
         this->radii.push_back(radii[i]);
     }
    init();
}

Tube::Tube(const ofVec3f& loc, const Dimension3D& dim, const Spline3d& path, float radius, int crossSectionDetail):
ProtoOrgBase(loc, dim), path(path), radius(radius), crossSectionDetail(crossSectionDetail){
    float t = 0;
    for (int i = 0; i < path.getVertsLength(); i++) {
       // ******** don't leave like this ********
        this->radii.push_back(3+abs(cos(t+=PI/45.0))*radius*3);
    }
    init();
}

// overrides base class
void Tube::calcVerts()
{
    std::vector<FrenetFrame> ff = path.getFrenetFrame();
    std::vector<ofVec3f> vecs = path.getVerts();
    
    for (int i = 0; i <ff.size(); i++) {
        // calculate cross-section vertices
        float th = 0;
        for(int j=0; j<crossSectionDetail; j++){
            float x = cos(th)*radii[i];
            float y = sin(th)*radii[i];
            float z = 0;
            float px = vecs[i+1].x + x*ff[i].getN().x + y*ff[i].getB().x;
            float py = vecs[i+1].y + x*ff[i].getN().y + y*ff[i].getB().y;
            float pz = vecs[i+1].z + x*ff[i].getN().z + y*ff[i].getB().z;
            verts.push_back(ofVec3f(px, py, pz));
            th -= PI*2/crossSectionDetail;
        }
    }
}

void Tube::calcInds()
{
    int crossSectionCount = path.getVertsLength();
    // indices
    for(int i=0; i<path.getVertsLength()/*ringCount*/; i++){
        for(int j=0; j<crossSectionDetail/*ringDetail*/; j++){
            
            int i0 = i*crossSectionDetail + j;
            int i1 = (i+1)*crossSectionDetail + j;
            int i2 = i*crossSectionDetail + j+1;
            int i3 = (i+1)*crossSectionDetail + j+1;
            int i4 = j;
            int i5 = i*crossSectionDetail;
            int i6 = crossSectionDetail + j+1;
            int i7 = (i+1)*crossSectionDetail;
            int i8 = j+1;
            
            if(i<crossSectionCount-1){
                if(j<crossSectionDetail-1){
                    inds.push_back( Tuple3i(i0, i2, i3) );
                    inds.push_back( Tuple3i(i0, i3, i1) );
                    
                } else {
                    // j+1 = 0
                    inds.push_back( Tuple3i(i0, i5, i7) );
                    inds.push_back( Tuple3i(i0, i7, i1) );
                }
            } else {
                if(j<crossSectionDetail-1){
                    //i+1 = 0
                    inds.push_back( Tuple3i(i0, i2, i8) );
                    inds.push_back( Tuple3i(i0, i8, i4) );
                    
                } else {
                    //i+1 =0, j+1 = 0
                    //inds.push_back( Tuple3i(i0, i5, 0) );
                    //inds.push_back( Tuple3i(i0, 0, i4) );
                }
            }
        }
    }

    
}

const Spline3d& Tube::getPath() const
{
    return path;
}