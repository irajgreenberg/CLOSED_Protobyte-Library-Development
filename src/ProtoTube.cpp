//
//  Tube.cpp
//  Protobyte_iig001
//
//  Created by Ira on 10/17/12.
//
//

#include "ProtoTube.h"

using namespace ijg;

std::ostream& operator<<(std::ostream& out, const ProtoTube& tube)
{
    out << "No Information to report at the moment";
    return out;
}

ProtoTube::ProtoTube()
{
    
}

ProtoTube::ProtoTube(const ofVec3f& loc, const Dimension3D& dim, const Spline3d& path,  float radii[], int crossSectionDetail): // varied thickness
ProtoOrgBase(loc, dim), path(path), crossSectionDetail(crossSectionDetail){
     for (int i = 0; i < path.getVertsLength(); i++) {
         this->radii.push_back(radii[i]);
     }
    init();
}

ProtoTube::ProtoTube(const ofVec3f& loc, const Dimension3D& dim, const Spline3d& path, float radius, int crossSectionDetail):
ProtoOrgBase(loc, dim), path(path), radius(radius), crossSectionDetail(crossSectionDetail){
    float t = 0;
    for (int i = 0; i < path.getVertsLength(); i++) {
       // ******** don't leave like this ********
        // testing varying radii
        //this->radii.push_back(.5+abs(cos(t+=PI/15))*radius*15);
        this->radii.push_back(radius);
    }
    init();
}

// overrides method in base class
void ProtoTube::calcVerts()
{
    std::vector<FrenetFrame> ff = path.getFrenetFrame();
    std::vector<ofVec3f> vecs = path.getVerts();
    
    for (int i = 0; i <ff.size(); i++) {
        // calculate cross-section vertices
        float theta = 0;
        for(int j=0; j<crossSectionDetail; j++){
            //float x = cos(th)*(radii[i] + ofRandom(-5, 5)); //bumpy
            //float y = sin(th)*(radii[i] + ofRandom(-5, 5)); //bumpy
            
            // calculate cross section shape
            float x = cos(theta)*radii[i];
            float y = sin(theta)*radii[i];
            
            float z = 0;
            theta += PI*2/crossSectionDetail;
            
            // transform to Frenet frame of reference
            float px = vecs[i+1].x + x*ff[i].getN().x + y*ff[i].getB().x;
            float py = vecs[i+1].y + x*ff[i].getN().y + y*ff[i].getB().y;
            float pz = vecs[i+1].z + x*ff[i].getN().z + y*ff[i].getB().z;
            verts.push_back(ofVec3f(px, py, pz));
            
        }
    }
}

void ProtoTube::calcInds()
{
    int frameCount = path.getFrenetFrame().size();
    int crossSectionCount = path.getVertsLength();
    // indices
    for(int i=0; i<frameCount-2/*ringCount*/; i++){
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

const Spline3d& ProtoTube::getPath() const
{
    return path;
}