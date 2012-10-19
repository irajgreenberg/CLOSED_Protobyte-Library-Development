//
//  Tube.h
//  Protobyte_iig001
//
//  Created by Ira on 10/17/12.
//
//

#ifndef Protobyte_iig001_Tube_h
#define Protobyte_iig001_Tube_h

#include <iostream>
#include "ofMain.h"
#include "Spline3d.h"
#include "ProtoOrgBase.h"

namespace ijg {

    class Tube: public ProtoOrgBase{
        
    public:
        
        friend std::ostream& operator<<(std::ostream& out, const Tube& tube);
        Tube();
        Tube(const ofVec3f& loc, const Dimension3D& dim, const Spline3d& path, float radii[]); // varied thickness
        Tube(const ofVec3f& loc, const Dimension3D& dim, const Spline3d& path, float radius);
        
        // overrides base class
        void calcVerts();
        void calcInds();
        
        const Spline3d& getPath() const;

   
    private:
        Spline3d path;
        float radius;
        float* radii;
    };
}


#endif
