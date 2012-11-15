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
    edges.push_back(ProtoEdge(tempVerts.at(0), tempVerts.at(1)));
    edges.push_back(ProtoEdge(tempVerts.at(0), tempVerts.at(2)));
    edges.push_back(ProtoEdge(tempVerts.at(0), tempVerts.at(3)));
    edges.push_back(ProtoEdge(tempVerts.at(1), tempVerts.at(2)));
    edges.push_back(ProtoEdge(tempVerts.at(2), tempVerts.at(3)));
    edges.push_back(ProtoEdge(tempVerts.at(3), tempVerts.at(1)));
    
    for(int i=0; i<edges.size(); i++){
        std::cout<< "edges"<<i<<": v0 = "<< edges.at(i).getV0() << ", v1 = " << edges.at(i).getV1() << std::endl;
    }
    
    // create temp faces (CCW winding)
    tempFaces.push_back(ProtoFace(edges.at(0), edges.at(1), edges.at(3)));
    tempFaces.push_back(ProtoFace(edges.at(2), edges.at(4), edges.at(1)));
    tempFaces.push_back(ProtoFace(edges.at(0), edges.at(5), edges.at(2)));
    tempFaces.push_back(ProtoFace(edges.at(3), edges.at(4), edges.at(5)));
    
    std::cout<<"\n";
    for(int i=0; i<tempFaces.size(); i++){
        for(int j=0; j<3; j++){
            std::cout<< "tempFaces"<<i<<" edge "<<j<<": v0 = "<< tempFaces.at(i).edges[j].getV0()<< ", v1 = " << tempFaces.at(i).edges[j].getV1() << std::endl;
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
    ///////////////////GET rid of this/////////////////////
    /*for(int i=0; i<edges.size(); ++i){
     ofVec3f v = (edges.at(i).getV0() + edges.at(i).getV1())/2;
     tempVerts.push_back(v);
     //std::cout << "v = " << v << std::endl;
     edges.at(i).setMidV(v);
     std::cout << "edges.at(i).getV0() = " << edges.at(i).getV0() << std::endl;
     std::cout << "edges.at(i).getMidV() = " << edges.at(i).getMidV() << std::endl;
     std::cout << "edges.at(i).getV2() = " << edges.at(i).getV1() << std::endl;
     }*/
    
    // create new edges and faces
    for(int i=0; i<faces.size(); ++i){
        
        // add mid points to each edge
        for(int j=0; j<3; ++j){
            ofVec3f v = (faces.at(i).edges[j].getV0() + faces.at(i).edges[j].getV1())/2;
            tempVerts.push_back(v);
            faces.at(i).edges[j].setMidV(v);
            //std::cout << "v = " << v << std::endl;
            //faces.at(i).edges[0].setMidV(v);
        }
        
        
        
        // perimeter edges
        es.push_back(ProtoEdge(faces.at(i).edges[0].getV0(), faces.at(i).edges[0].getMidV()));
        es.push_back(ProtoEdge(faces.at(i).edges[0].getMidV(), faces.at(i).edges[0].getV1()));
        
        es.push_back(ProtoEdge(faces.at(i).edges[1].getV0(), faces.at(i).edges[1].getMidV()));
        es.push_back(ProtoEdge(faces.at(i).edges[1].getMidV(), faces.at(i).edges[1].getV1()));
        
        es.push_back(ProtoEdge(faces.at(i).edges[2].getV0(), faces.at(i).edges[2].getMidV()));
        es.push_back(ProtoEdge(faces.at(i).edges[2].getMidV(), faces.at(i).edges[2].getV1()));
        
        // center edges
        es.push_back(ProtoEdge(faces.at(i).edges[0].getMidV(), faces.at(i).edges[1].getMidV()));
        es.push_back(ProtoEdge(faces.at(i).edges[1].getMidV(), faces.at(i).edges[2].getMidV()));
        es.push_back(ProtoEdge(faces.at(i).edges[2].getMidV(), faces.at(i).edges[0].getMidV()));
        
        // create new faces
        fs.push_back(ProtoFace(es.at(1 + 9*i), es.at(4 + 9*i), es.at(8 + 9*i)));
        fs.push_back(ProtoFace(es.at(0 + 9*i), es.at(6 + 9*i), es.at(2 + 9*i)));
        fs.push_back(ProtoFace(es.at(6 + 9*i), es.at(8 + 9*i), es.at(7 + 9*i)));
        fs.push_back(ProtoFace(es.at(7 + 9*i), es.at(5 + 9*i), es.at(3 + 9*i)));
    }

    /*for(int i=0; i<es.size(); i++){
        std::cout<< "es"<<i<<": v0 = "<< es.at(i).getV0() << ", v1 = " << es.at(i).getV1() << std::endl;
    }*/
    
    tempFaces = fs;
    
    for( int i=0; i<fs.size(); ++i){
        /*std::cout<< *fs.at(i).e0.getV0() << std::endl;
         std::cout<< *fs.at(i).e0.getV1() << std::endl;
         std::cout<< *fs.at(i).e1.getV0() << std::endl;
         std::cout<< *fs.at(i).e1.getV1() << std::endl;
         std::cout<< *fs.at(i).e2.getV0() << std::endl;
         std::cout<< *fs.at(i).e2.getV1() << std::endl;*/
    }
    
    edges = es;
    
    for(int i=0; i<edges.size(); i++){
        std::cout<< "edges"<<i<<": v0 = "<< edges.at(i).getV0() << ", v1 = " << edges.at(i).getV1() << std::endl;
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

void ProtoTetrahedron::displayEdges()
{
    //std::cout<< "tempFaces.size() = " << tempFaces.size()<< std::endl;
    glPushMatrix();
    glTranslatef(loc.x, loc.y, loc.z);
    glScalef(dim.w, dim.h, dim.d);
    glColor3f(200, 200, 200);
    
    for( int i=0; i<tempFaces.size(); ++i){
        glBegin(GL_LINES);
        glVertex3f(tempFaces.at(i).edges[0].getV0().x, tempFaces.at(i).edges[0].getV0().y, tempFaces.at(i).edges[0].getV0().z);
        glVertex3f(tempFaces.at(i).edges[0].getV1().x, tempFaces.at(i).edges[0].getV1().y, tempFaces.at(i).edges[0].getV1().z);
        
        glVertex3f(tempFaces.at(i).edges[1].getV0().x, tempFaces.at(i).edges[1].getV0().y, tempFaces.at(i).edges[1].getV0().z);
        glVertex3f(tempFaces.at(i).edges[1].getV1().x, tempFaces.at(i).edges[1].getV1().y, tempFaces.at(i).edges[1].getV1().z);
        
        glVertex3f(tempFaces.at(i).edges[2].getV0().x, tempFaces.at(i).edges[2].getV0().y, tempFaces.at(i).edges[2].getV0().z);
        glVertex3f(tempFaces.at(i).edges[2].getV1().x, tempFaces.at(i).edges[2].getV1().y, tempFaces.at(i).edges[2].getV1().z);
        glEnd();
    }
    // std::cout<< "edges.size() = " << edges.size()<< std::endl;
    
    for( int i=0; i<edges.size(); ++i){
        glBegin(GL_LINES);
        // glVertex3f(edges.at(i).getV0().x, edges.at(i).getV0().y, edges.at(i).getV0().z);
        // glVertex3f(edges.at(i).getV1().x, edges.at(i).getV1().y, edges.at(i).getV1().z);
        glEnd();
    }
    
    glPopMatrix();
}