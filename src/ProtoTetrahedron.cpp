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
        std::cout<< "edges"<<i<<": v0 = "<< *edges.at(i).getV0() << ", v1 = " << *edges.at(i).getV1() << std::endl;
    }
    
    // create temp faces (CCW winding)
    tempFaces.push_back(ProtoFace(&edges.at(0), &edges.at(1), &edges.at(3)));
    tempFaces.push_back(ProtoFace(&edges.at(2), &edges.at(4), &edges.at(1)));
    tempFaces.push_back(ProtoFace(&edges.at(0), &edges.at(5), &edges.at(2)));
    tempFaces.push_back(ProtoFace(&edges.at(3), &edges.at(4), &edges.at(5)));
    
    std::cout<<"\n";
    for(int i=0; i<tempFaces.size(); i++){
        for(int j=0; j<3; j++){
            std::cout<< "tempFaces"<<i<<" edge "<<j<<": v0 = "<< *tempFaces.at(i).p_edges[j]->getV0()<< ", v1 = " << *tempFaces.at(i).p_edges[j]->getV1() << std::endl;
        }
        std::cout<<"\n";
    }

    subdivide(tempFaces);
    
}

void ProtoTetrahedron::subdivide(std::vector<ProtoFace>& faces)
{
    /**********
     calculate
     subdivison
     vertices
     -----.----
     \   /\   /
     *\ /  \ /*
     **.----.**
     ***\  /***
     ****\/****
     *********/

    std::vector<ProtoFace> fs;
    std::vector<ProtoEdge> es;
    
    // add mid points to each edge
    for(int i=0; i<edges.size(); ++i){
        ofVec3f v = (*edges.at(i).getV0() + *edges.at(i).getV1())/2;
        tempVerts.push_back(v);
        edges.at(i).setMidV(&v);
    }
    
    // create new edges and faces
    for(int i=0; i<faces.size(); ++i){
        // perimeter edges
        es.push_back(ProtoEdge(faces.at(i).p_edges[0]->getV0(), faces.at(i).p_edges[0]->getMidV()));
        es.push_back(ProtoEdge(faces.at(i).p_edges[0]->getMidV(), faces.at(i).p_edges[0]->getV1()));
        
        es.push_back(ProtoEdge(faces.at(i).p_edges[1]->getV0(), faces.at(i).p_edges[1]->getMidV()));
        es.push_back(ProtoEdge(faces.at(i).p_edges[1]->getMidV(), faces.at(i).p_edges[1]->getV1()));
        
        es.push_back(ProtoEdge(faces.at(i).p_edges[2]->getV0(), faces.at(i).p_edges[2]->getMidV()));
        es.push_back(ProtoEdge(faces.at(i).p_edges[2]->getMidV(), faces.at(i).p_edges[2]->getV1()));
        
        // center edges
        es.push_back(ProtoEdge(faces.at(i).p_edges[0]->getMidV(), faces.at(i).p_edges[1]->getMidV()));
        es.push_back(ProtoEdge(faces.at(i).p_edges[1]->getMidV(), faces.at(i).p_edges[2]->getMidV()));
        es.push_back(ProtoEdge(faces.at(i).p_edges[2]->getMidV(), faces.at(i).p_edges[0]->getMidV()));
        
        // create new faces
        fs.push_back(ProtoFace(es.at(1 + 8*i), es.at(4 + 8*i), es.at(8 + 8*i)));
        fs.push_back(ProtoFace(es.at(0 + 8*i), es.at(6 + 8*i), es.at(2 + 8*i)));
        fs.push_back(ProtoFace(es.at(6 + 8*i), es.at(8 + 8*i), es.at(7 + 8*i)));
        fs.push_back(ProtoFace(es.at(7 + 8*i), es.at(5 + 8*i), es.at(3 + 8*i)));
    }
    
    //edges.clear();
    std::cout<< "es.size() = " << es.size() << std::endl;
     std::cout<< "edges.size() = " << edges.size() << std::endl;
    for(int i=0; i<es.size(); i++){
        std::cout<< "es"<<i<<": v0 = "<< *es.at(i).getV0() << ", v1 = " << *es.at(i).getV1() << std::endl;
    }
    
    //tempFaces.clear();
    //tempFaces = fs;
    
    for( int i=0; i<fs.size(); ++i){
        /*std::cout<< *fs.at(i).e0.getV0() << std::endl;
        std::cout<< *fs.at(i).e0.getV1() << std::endl;
        std::cout<< *fs.at(i).e1.getV0() << std::endl;
        std::cout<< *fs.at(i).e1.getV1() << std::endl;
         std::cout<< *fs.at(i).e2.getV0() << std::endl;
         std::cout<< *fs.at(i).e2.getV1() << std::endl;*/
    }
    
    //edges.clear();
    //edges.resize(es.size());
    //std::cout<< "edges.size() = " << edges.size() << std::endl;
    //edges = es;
    //edges.resize(es.size());
    //for(int i=0; i<edges.size(); i++){
       // edges.at(i) = es.at(i);
        //std::cout<< *edges.at(i).getV0() << std::endl;
       // edges.push_back(es.at(i));
    //}
    
   // for(int i=0; i<edges.size(); i++){
        //std::cout<< "edges"<<i<<": v0 = "<< *edges.at(i).getV0() << ", v1 = " << *edges.at(i).getV1() << std::endl;
   // }

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

 void ProtoTetrahedron::displayEdges()
{
   // std::cout<< "tempFaces.size() = " << tempFaces.size()<< std::endl;
    glPushMatrix();
    glTranslatef(loc.x, loc.y, loc.z);
    glScalef(dim.w, dim.h, dim.d);
    glColor3f(200, 200, 200);
    glBegin(GL_POLYGON);
    for( int i=0; i<tempFaces.size(); ++i){
       // std::cout<< *tempFaces.at(i).e0.getV0() << std::endl;
       // std::cout<< *tempFaces.at(i).e1.getV0() << std::endl;
         //std::cout<< *tempFaces.at(i).e2.getV0() << std::endl;
        //glVertex3f(edges.at(i).getV0()->x, edges.at(i).getV0()->y, edges.at(i).getV0()->z);
        //glVertex3f(edges.at(i).getV1()->x, edges.at(i).getV1()->y, edges.at(i).getV1()->z);
        //tempFaces.at(i).display();
    }
    glEnd();
    glPopMatrix();
}