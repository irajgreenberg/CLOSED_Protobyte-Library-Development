//
//  Dimension3D.h
//  Protobyte_iig001
//
//  Created by Ira on 10/6/12.
//
//

#ifndef Protobyte_iig001_Dimension3D_h
#define Protobyte_iig001_Dimension3D_h

#include <iostream>

namespace ijg {
    
    class Dimension3D {
    
    public:
        friend std::ostream& operator<<(std::ostream& output, const Dimension3D & dim);
        explicit Dimension3D(float w = 1, float h = 1, float d = 1);
        
        float w, h, d;
    };
    
}

#endif
