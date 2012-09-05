//
//  Tuple3i.h
//  Protobyte_iig001
//
//  Created by Ira on 9/5/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Protobyte_iig001_Tuple3i_h
#define Protobyte_iig001_Tuple3i_h

namespace ijg {
    
    class Tuple3i {
        
    public:
        int elem0, elem1, elem2;
        int elems[3];
        
        explicit Tuple3i(int elem0 = 0, int elem1 = 0, int elem2 = 0);
        
    };
}
#endif
