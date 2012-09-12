//
//  TriangleSortTester.cpp
//  Protobyte_iig001
//
//  Created by Ira on 9/9/12.
//
//

#include "TriangleSortTester.h"

using namespace ijg;

TriangleSortTester::TriangleSortTester(){
    init();
}


// overridden methods

// vertex calculations
void TriangleSortTester::init()
{
    clearAll(); // ensure vectors are cleaned
    calcVerts();
    calcInds();
    calcFaces();
    calcNorms();
    calcPrimitives();
}

// vertex calculations
void TriangleSortTester::calcVerts()
{
    // vertices
    for(int i=0; i<5; i++){
        float theta = -PI/4; // spine detail arc
        // START CALCULATE VERTICES
        for(int j=0; j<3; j++){
            verts.push_back( ofVec3f(cos(theta), sin(theta), 10*i) );
            
            theta += PI*2/3;
        }
    }
}

void TriangleSortTester::calcInds(){
    // indices
    for(int i=0; i<5; i++){
        for(int j=0; j<3; j++){
            
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

void TriangleSortTester::calcFaces()
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
void TriangleSortTester::setSpines(int spines)
{
    this->spines = spines;
    init();
}

int TriangleSortTester::getSpines()
{
    return spines;
}

void TriangleSortTester::setSpineDetail(int spineDetail)
{
    this->spineDetail = spineDetail;
    init();
}

int TriangleSortTester::getSpineDetail()
{
    return spineDetail;
}

void TriangleSortTester::setIsClosed(bool isClosed)
{
    this->isClosed = isClosed;
}

bool TriangleSortTester::getIsClosed(){
    return isClosed;
}
