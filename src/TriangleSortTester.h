//
//  TriangleSortTester.h
//  Protobyte_iig001
//
//  Created by Ira on 9/9/12.
//
//

#ifndef Protobyte_iig001_TriangleSortTester_h
#define Protobyte_iig001_TriangleSortTester_h


#include "ProtoOrgBase.h"

namespace ijg {
    
    class TriangleSortTester: public  ProtoOrgBase {
        
    public:
        
        explicit TriangleSortTester();
        
        // overrides base class
        void init();
        void calcVerts();
        void calcInds();
        void calcFaces();
        
        
        // getters & setters
        
    private:
        float radius;
    };
    
}


#endif
