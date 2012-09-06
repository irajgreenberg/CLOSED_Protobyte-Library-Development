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
        
        explicit ProtoOrg002(int spines = 3, int spineDetail = 3, bool isClosed = false, float radius = 1, float height = 1);
        
        // overrides base class 
        void init();
        void calcVerts();
        void calcInds();
        void calcFaces();
        
        
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
