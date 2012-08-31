//
//  Particle.cpp
//  animatingParticles
//
//  Created by Ira on 8/27/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Particle.h"

// constructor - explicit keyword avoids single param implicit conversions
Particle::Particle(const ofVec2f& loc, const ofVec2f& spd, float mass, float smoothness): loc(loc), spd(spd), mass(mass), smoothness(smoothness)
{
    
}

//function protoypes
void Particle::move()
{
    loc += spd;
}

void Particle::display()
{
    ofPushMatrix();
    ofTranslate(loc.x, loc.y);
    //ofScale(dim.x, loc.y);
    ofCircle(0,0,1);
    ofPopMatrix();
    
}

