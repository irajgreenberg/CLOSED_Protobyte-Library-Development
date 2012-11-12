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
    // measures for unit size tetrahedron
    float radius = .5;
    float theta = 0;
    float h = .816496581; // = sqrt(2)/sqrt(3)
    
    
    /* calculate initial 4 vertices */
     // top
    tempVerts.push_back(ofVec3f(0, 0, -h));
    //bases
    for(int i=0; i<3; i++){
        tempVerts.push_back(ofVec3f(cos(theta)*radius, sin(theta)*radius));
        theta += PI*2/3;
    }
    // calculate 6 initial edges, composed of vertex references
    edges.push_back(ProtoEdge(&tempVerts.at(0), &tempVerts.at(1)));
    edges.push_back(ProtoEdge(&tempVerts.at(0), &tempVerts.at(2)));
    edges.push_back(ProtoEdge(&tempVerts.at(0), &tempVerts.at(3)));
    edges.push_back(ProtoEdge(&tempVerts.at(1), &tempVerts.at(2)));
    edges.push_back(ProtoEdge(&tempVerts.at(2), &tempVerts.at(3)));
    edges.push_back(ProtoEdge(&tempVerts.at(3), &tempVerts.at(1)));
    
    for(int i=0; i<edges.size(); i++){
        //std::cout<< "edges"<<i<<": v0 = "<< *edges.at(i).getV0() << ", v1 = " << *edges.at(i).getV1() << std::endl;
    }
    
    // create temp faces
    tempFaces.push_back(ProtoFace(&edges.at(0), &edges.at(1), &edges.at(3)));
    tempFaces.push_back(ProtoFace(&edges.at(2), &edges.at(1), &edges.at(4)));
    tempFaces.push_back(ProtoFace(&edges.at(0), &edges.at(2), &edges.at(5)));
    tempFaces.push_back(ProtoFace(&edges.at(3), &edges.at(4), &edges.at(5)));
    
    subdivide(tempFaces);
    
 std::cout<<"\n";
    
    // divide edges
    for(int i=0; i<edges.size(); ++i){
        ofVec3f v = (*edges.at(i).getV0() + *edges.at(i).getV1())/2;
        tempVerts.push_back(v);
        //tempEdges.push_back(ProtoEdge(edges.at(i).getV0(), &*it));
    }
    
    std::cout<<"\n";
    
    for(int i=0; i<tempVerts.size(); ++i){
         std::cout<< "tempVerts"<<i<<": = "<< tempVerts.at(i) << std::endl;
    }
   
   /* for(int i=0; i<inds.size(); i++){
        edges.push_back(ProtoEdge(&verts.at(inds.at(i).elem0), &verts.at(inds.at(i).elem1)));
        edges.push_back(ProtoEdge(&verts.at(inds.at(i).elem1), &verts.at(inds.at(i).elem2)));
        edges.push_back(ProtoEdge(&verts.at(inds.at(i).elem2), &verts.at(inds.at(i).elem0)));
    }
    */
    // calculate 4 initial faces, composed of edge references
   /* inds.push_back( Tuple3i(0, 2, 1) );
    inds.push_back( Tuple3i(0, 1, 3) );
    inds.push_back( Tuple3i(1, 2, 3) );
    inds.push_back( Tuple3i(2, 0, 3) );*/
   
    
    
    
   
    
    
    // base faces
   /* for(int i=0; i<4; i++){
        ofVec3f* v1 = &verts.at(inds.at(i).elem0);
        ofVec3f* v2 = &verts.at(inds.at(i).elem1);
        ofVec3f* v3 = &verts.at(inds.at(i).elem2);
        tempFaces.push_back(ProtoFace(v1, v2, v3));
    }*/
    
    /********** 
     calculate 
     subdivison
     vertices
     -----.----
     \   /\   /
      \ /  \ /
       .----.
        \  /
         \/
     ********/
    subdivisionLevel = 1;
    
     for(int i=0; i<tempFaces.size(); i++){
         
     }
    
    for(int i=0; i<subdivisionLevel; i++){
        for(int j=0; j<edges.size(); j++) {
        
        // edges add 
        }
    }
    
}

void ProtoTetrahedron::subdivide(std::vector<ProtoFace>& faces)
{
    std::vector<ProtoFace> fs;
    std::vector<ProtoEdge> es;
    
    // add mid points to each edge
    for(int i=0; i<edges.size(); ++i){
        ofVec3f v = (*edges.at(i).getV0() + *edges.at(i).getV1())/2;
        tempVerts.push_back(v);
        edges.at(i).setMidV(&v);
    }

    /*
     tempFaces.push_back(ProtoFace(&edges.at(0), &edges.at(1), &edges.at(3)));
     tempFaces.push_back(ProtoFace(&edges.at(2), &edges.at(1), &edges.at(4)));
     tempFaces.push_back(ProtoFace(&edges.at(0), &edges.at(2), &edges.at(5)));
     tempFaces.push_back(ProtoFace(&edges.at(3), &edges.at(4), &edges.at(5)));
     */
    // create new edges on faces
    for(int i=0; i<faces.size(); ++i){
        es.push_back(ProtoEdge());
        es.push_back(ProtoEdge());
        es.push_back(ProtoEdge());
        es.push_back(ProtoEdge());
    }
}

void ProtoTetrahedron::calcInds()
{
    /*inds.push_back( Tuple3i(0, 1, 2) );
    inds.push_back( Tuple3i(0, 3, 1) );
    inds.push_back( Tuple3i(1, 3, 2) );
    inds.push_back( Tuple3i(2, 3, 0) );*/
    
    
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