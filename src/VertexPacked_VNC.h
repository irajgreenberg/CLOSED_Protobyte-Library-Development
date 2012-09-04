//
//  VertexPacked_VNC.h
//  Protobyte_iig001
//
//  Created by Ira on 9/3/12.
//
//

#ifndef Protobyte_iig001_VertexPack_VNC_h
#define Protobyte_iig001_VertexPack_VNC_h

#include "ofMain.h"

namespace ijg{
    
    class VertexPacked_VNC {
        
    public:
        
        
        float x, y, z, nx, ny, nz, r, g, b, a;
        
        ofVec3f vec, norm;
        float rgba[4];
        
        // cster
        explicit VertexPacked_VNC(float x=0, float y=0, float z=0,
                                float r=0, float g=0, float b=0, float a=0);
        VertexPacked_VNC(const ofVec3f& vec);
        VertexPacked_VNC(const ofVec3f& vec, float rgba[]);
        
        void init();
        void setNorm(const ofVec3f& norm);
        void setRGBA(float r, float g, float b, float a);
        void setRGBA(float rgba[]);
        float* getRGBA();
        float* getData();
        
        
    private:
        
        float data[10];
    };
}


#endif
