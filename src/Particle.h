//
//  Particle.h
//  animatingParticles
//
//  Created by Ira on 8/27/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef animatingParticles_Particle_h
#define animatingParticles_Particle_h

#include "ofMain.h"

// currently no heap allocation
class Particle {
    
public:
    
    // constructor - explicit keyword avoids single param implicit conversions
    explicit Particle(const ofVec2f& loc=ofVec2f(), const ofVec2f& spd=ofVec2f(), float mass=0.0f, float smoothness=0.0f);
    
    //function protoypes
    void move();
    void display();
    
    
    //setters/getters (inline)
    void setLoc(const ofVec2f& loc)
    {
        this->loc = loc;
    }
    
    ofVec2f getLoc() const
    {
        return loc;
    }
    
    void setSpd(const ofVec2f& spd)
    {
        this->spd = spd;
    }
    
    ofVec2f getSpd() const
    {
        return spd;
    }
    
    void setMass(float mass)
    {
        this->mass = mass;
    }
    
    float getMass() const
    {
        return mass;
    }
    
    void setSmoothness(float smoothness)
    {
        this->smoothness = smoothness;
    }
    
    float getSmoothness() const
    {
        return smoothness;
    }

    
private:
    
    ofVec2f loc;
    ofVec2f spd;
    float mass;
    float smoothness;
    

};

#endif
