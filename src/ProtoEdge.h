//
//  ProtoEdge.h
//  Protobyte_iig001
//
//  Created by Ira on 11/10/12.
//
//

#ifndef Protobyte_iig001_ProtoEdge_h
#define Protobyte_iig001_ProtoEdge_h

#include "ofMain.h"

namespace ijg{
    class ProtoEdge {
        
    public:
        ProtoEdge(ofVec3f* p_v0, ofVec3f* p_v1);
        
        //ProtoEdge(const ProtoEdge& edge); // don't implement
        //ProtoEdge& operator=(const ProtoEdge& edge); // don't implement
        
        void setV0(ofVec3f* p_v0);
        void setV1(ofVec3f* p_v1);
        
        ofVec3f* getV0();
        ofVec3f* getV1();
        
    private:
        ofVec3f* p_v0;
        ofVec3f* p_v1;
    };
    
}


#endif
