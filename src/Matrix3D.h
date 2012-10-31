//
//  Matrix3D.h
//  Protobyte_iig001
//
//  Created by Ira on 10/26/12.
//
//

#ifndef Protobyte_iig001_Matrix3D_h
#define Protobyte_iig001_Matrix3D_h

#include "ofMain.h"

namespace ijg {
    
    class Matrix3D{
    
    public:
        Matrix3D();
        void rotate(float theta, const ofVec3f& axis, ofVec3f& v);
        ofVec3f getRotate(float theta, const ofVec3f& axis, const ofVec3f& vec);
        void inverse();
        void determinent();
        void mult(const Matrix3D& m1);
        ofVec3f mult(const ofVec3f& vec);
        void add();
        
        
    private:
        float r0c0, r0c1, r0c2,
        r1c0, r1c1, r1c2,
        r2c0, r2c1, r2c2;
        
        
    };
}

#endif
