//
//  ProtoToroid.h
//  Protobyte_iig001
//
//  Created by Ira on 10/6/12.
//
//

#ifndef Protobyte_iig001_ProtoToroid_h
#define Protobyte_iig001_ProtoToroid_h

#include "ProtoOrgBase.h"
#include "Dimension3D.h"

namespace ijg {
    
    class ProtoToroid: public  ProtoOrgBase {
        
    public:
        friend std::ostream& operator<<(std::ostream& output, const ProtoToroid& toroid);
        
        explicit ProtoToroid(const ofVec3f& loc = ofVec3f(0,0,0), const Dimension3D& dim = Dimension3D(1,1,1), int ringCount = 12, int ringDetail = 20, float ringRadius = .2);
        
        // overrides base class
        void calcVerts();
        void calcInds();
        
        
        // getters & setters
        int getRingCount() const;
        void setRingCount(int ringCount);
        int getRingDetail() const;
        void setRingDetail(int ringDetail);
        float getRingRadius() const;
        void setRingRadius(float ringRadius);
        
    private:
        int ringCount;
        int ringDetail;
        float ringRadius;
    };
    
}


#endif
