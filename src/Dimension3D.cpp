//
//  Dimension3D.cpp
//  Protobyte_iig001
//
//  Created by Ira on 10/6/12.
//
//

#include "Dimension3D.h"



namespace ijg {
    
std::ostream& operator<<(std::ostream& output, const Dimension3D & dim)
{
    output << "Dimenion3D obj: [ w = "<<dim.w<<" h = "<<dim.h<<" d = "<<dim.d<<" ]";
    return output;
}
}

using namespace ijg;

Dimension3D::Dimension3D(float w, float h, float d):
w(w), h(h), d(d){
}