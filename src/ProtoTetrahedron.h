//
//  ProtoTetrahedron.h
//  Protobyte_iig001
//
//  Created by Ira on 11/4/12.
//
//

#ifndef Protobyte_iig001_Tetrahedron_h
#define Protobyte_iig001_Tetrahedron_h

#include "ProtoOrgBase.h"

namespace ijg{
    
    class ProtoTetrahedron: public ProtoOrgBase{
    
    public:
        friend std::ostream& operator<<(std::ostream& out, const ProtoTetrahedron& tetrahedron);
        ProtoTetrahedron();
        ProtoTetrahedron(const ofVec3f& loc, const Dimension3D& dim, int subdivisionLevel);
        
        // overrides base class
        void calcVerts();
        void calcInds();
        
        //getters/setters
        void setSubdivisionLevel(int subdivisionLevel = 3);
        int getSubdivisionLevel() const;
        void displayEdges();
        
    private:
        int subdivisionLevel;
        std::vector<ProtoFace> tempFaces;
        // dyanmically insert vertices based on subdivision
        std::vector<ofVec3f> tempVerts;
        std::vector<ProtoEdge> tempEdges;
        std::list<ofVec3f> dynamicVerts;
        std::list<ofVec3f>::iterator it;
        
        void subdivide(std::vector<ProtoFace>&);
    };

}

#endif
