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
        ProtoEdge();
        ProtoEdge(ofVec3f* p_v0, ofVec3f* p_v1);
        ProtoEdge(const ofVec3f& v0, const ofVec3f& v1);
        
        //ProtoEdge(const ProtoEdge& edge); // don't implement
        //ProtoEdge& operator=(const ProtoEdge& edge); // don't implement
        
        void setP_v0(ofVec3f* p_v0);
        void setP_v1(ofVec3f* p_v1);
        void setP_midV(ofVec3f* p_midV);
        
        ofVec3f* getP_v0();
        ofVec3f* getP_v1();
        ofVec3f* getP_midV();
        
        void setV0(const ofVec3f& v0);
        void setV1(const ofVec3f& v1);
        void setMidV(const ofVec3f& midV);
        
        ofVec3f& getV0();
        ofVec3f& getV1();
        ofVec3f& getMidV();
        
  
        
    private:
        ofVec3f v0, v1, midV;
        ofVec3f* p_v0, * p_v1, * p_midV;
    };
    
}


#endif
