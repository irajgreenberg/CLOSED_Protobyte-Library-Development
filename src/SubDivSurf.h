//
//  SubDivSurf.h
//  Protobyte_iig001
//
//  Created by Ira on 11/10/12.
//
//

#ifndef Protobyte_iig001_SubDivSurf_h
#define Protobyte_iig001_SubDivSurf_h

#include "ProtoOrgBase.h"

namespace ijg {
    
    class SubDivSurf:public ProtoOrgBase {
        
    public:
        friend std::ostream& operator<<(std::ostream& output, const SubDivSurf& surf);
        
        SubDivSurf();
        SubDivSurf(ofVec3f vecs[3], const ofVec3f& loc = ofVec3f(0,0,0), const Dimension3D& dim = Dimension3D(1,1,1), int subdivLevel = 2);
        
        // overrides base class
        void calcVerts();
        void calcInds();
        
        
        // getters & setters
        void setSubdivLevel(int subdivLevel);
        int getSubdivLevel() const;
            
    private:
        int subdivLevel;
        ofVec3f v0, v1, v2;
        std::list<ofVec3f> tempVecs;
        list<ofVec3f>::iterator it;

    };

}

#endif
