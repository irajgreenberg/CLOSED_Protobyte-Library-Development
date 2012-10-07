//
//  ProtoOrg002.h
//  Protobyte_iig001
//
//  Created by Ira on 9/5/12.
//
//

#ifndef Protobyte_iig001_ProtoOrg002_h
#define Protobyte_iig001_ProtoOrg002_h

#include "ProtoOrgBase.h"

namespace ijg {
    
    class ProtoOrg002: public  ProtoOrgBase {
        
    public:
        
        explicit ProtoOrg002(const ofVec3f& loc = ofVec3f(), const Dimension3D& dim = Dimension3D(1, 1, 1), int spines = 3, int spineDetail = 3, bool isClosed = false);
        
        // overrides base class 
        void calcVerts();
        void calcInds();
        
        
        // getters & setters
        void setSpines(int spines);
        int getSpines();
        
        void setSpineDetail(int spineDetail);
        int getSpineDetail();
        
        void setIsClosed(bool isClosed);
        bool getIsClosed();
    
    private:
        int spines, spineDetail;
        bool isClosed;
        float radius, height;
    };
    
}

#endif
