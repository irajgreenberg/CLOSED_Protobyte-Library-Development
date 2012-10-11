//
//  Spline3d.cpp
//  Protobyte Library V01
//
//  Created by Ira Greenberg on 8/2/11.
//  Copyright 2011 SMU. All rights reserved.
//

#include "Spline3d.h"
#include <iostream>

using namespace ijg;

/**
 * Spline cubic curve class, where curve goes through all points. Curve is
 * specified by 6 points, with a constant specifying tension.
 * <p>
 */


Spline3d::Spline3d(ofVec3f controlPt0, ofVec3f controlPt1, ofVec3f controlPt2, ofVec3f controlPt3, ofVec3f controlPt4, ofVec3f controlPt5, ofVec3f controlPt6, ofVec3f controlPt7, int interpDetail, bool isCurveClosed, float smoothness):
Curve3d(controlPt0, controlPt1, controlPt2, controlPt3, controlPt4,controlPt5, controlPt6, controlPt7, interpDetail), smoothness(smoothness)
{
    
}

Spline3d::Spline3d(const std::vector<ofVec3f>& controlPts,int interpDetail, bool isCurveClosed, float smoothness):
Curve3d(controlPts, interpDetail, isCurveClosed), smoothness(smoothness){
    init();
}



/**
 * Calculate the interpolated curve points populating the uniqueVerts array.
 */
void Spline3d::init() {
    // std::cout<< "In Spline3d init method"<< std::endl;
    int len = 0;
    if(isCurveClosed){
        len = (controlPts.size())*interpDetail;
    } else {
        len =(controlPts.size()-1)*interpDetail;
    }
    // std::cout<< "controlPtsLength 2 = " << controlPtsLength << std::endl;
    // std::cout<< "interpDetail 2 = " << interpDetail << std::endl;
    // std::cout<< "len 2 = " << len << std::endl;
    
    //interpPts = newofVec3f[len]; NOT SURE IF I NEED THIS
   // vertsLength = len + controlPts.size();
   
    // std::cout<< "vertsLength 2 = " << vertsLength << std::endl;
    //verts = newofVec3f[vertsLength];
    vertRad = .01;
    
    // detect if curve should be closed
    if (isCurveClosed) {
        // std::cout << "in isCurveClosed" << std::endl;
        // std::cout << "len = " << len << std::endl;
        // tempVecs.push_back(controlPts[0]);
        for (int i = 0; i < controlPts.size(); i++) {
            //tempVecs.push_back(controlPts[i]);
            //std::cout<< "controlPts["<<i<<"] = " << controlPts[i] << std::endl;
           ofVec3f t1;
           ofVec3f t2;
            // equation to calculate spline tangents
            // Ti = tension * ( Pi+1 - Pi-1 )
            
            // tangent 1 (i)
            // Pi+1
            if (i < controlPts.size()-1) {
                t1 = controlPts[i + 1];
            } else {
                t1 = controlPts[0];
            }
            // Pi-1
            if (i > 0) {
                t1 -= controlPts[i - 1];
            } else {
                // if i==0, subtract last point as pi-i to form smooth curve back in
                t1 -= controlPts[controlPts.size() - 1];
            }
            t1 *= smoothness;
            
            
            // tangent 2 (i+1)
            // Pi+1
            if (i < controlPts.size() - 2) {
                t2 = controlPts[i + 2];
                //t2.sub(controlPts[i]);
            } else if (i == controlPts.size() - 2){
                t2 = controlPts[0];
            } else {
                t2 = controlPts[1];
            } 
            // Pi-1
            t2 -= controlPts[i];
            t2 *= smoothness;
            
            //std::cout <<"t1 = " << t1 << std::endl;
            //std::cout <<"t2 = " << t2 << std::endl;
            
            // 1st plot control points
            tempVecs.push_back(controlPts[i]);
            
            // 2nd plot interpolated points
            for (int t = 1; t < interpDetail + 1; t++) {
                // std::cout <<"interpDetail = " << interpDetail << std::endl;
                // scale between 0.0-1.0
                double s = t / (double) (interpDetail+1);
                //std::cout <<"s = " << s << std::endl;
                // calculate basis functions
                // for controls
                double h1 = 2.0 * s * s * s - 3.0 * s * s + 1.0; // y = 2s^3 - 3s^2 + 1, y' = 6s^2 - 6s
                double h2 = -2.0 * s * s * s + 3.0 * s * s; // y = -2s^3 - 3s^2, y' = -6s^2 - 6s
                // for tangents
                double h3 = s * s * s - 2.0 * s * s + s; // y = s^3 - 2s^3, y' = s^2 - 6s^2
                double h4 = s * s * s - s * s; // y = s^3 - s^2, y' = 3s^2 - 2s
                
                // create temporary vector
               ofVec3f tempVec;
                tempVec = controlPts[i]; // p0
                tempVec *= h1;
                if (i<controlPts.size()-1){
                    tempVec += (controlPts[i + 1] * h2); // p3
                } else {
                    // final node
                    tempVec += (controlPts[0] * h2); // p3
                }
                // tangent 1
                tempVec += (t1 * h3); // p1
                // tangent 2
                tempVec += (t2 * h4); // p2
                tempVecs.push_back(tempVec);
            }
        }
        // smooth curves at end of paths
    } else if (isTerminalSmooth) {
        // std::cout << "in isTerminalSmooth" << std::endl;
        //std::cout <<"Inside isTerminalSmooth block" << std::endl;
        for (int i = 0; i < controlPts.size()-1; i++) {
            tempVecs.push_back(controlPts[i]);
           ofVec3f t1;
           ofVec3f t2;
            // equation to calculate spline tangents
            // Ti = a * ( Pi+1 - Pi-1 )
            
            // tangent 1 (i)
            // Pi+1
            if (i < controlPts.size()-1) {
                t1 = controlPts[i + 1];
            } else {
                t1 = controlPts[0];
            }
            // Pi-1
            if (i > 0) {
                t1 -= controlPts[i - 1];
            } else {
                // if i==0, subtract last point as pi-i to form smooth curve back in
                t1 -= controlPts[controlPts.size() - 1];
            }
            t1 *= smoothness;
            
            // tangent 2 (i+1)
            // Pi+1
            if (i < controlPts.size() - 2) {
                t2 = controlPts[i + 2];
            } else if (i == controlPts.size() - 2){
                t2 = controlPts[0];
            } else {
                t2 = controlPts[1];
            } 
            // Pi-1
            t2 -= controlPts[i];
            t2 *= smoothness;
            
            // FIXED 8/9/10 to allow symmetry on curve
            for (int t = 1; t <interpDetail+1; t++) { /*fixed*/
                // scale between 0.0-1.0
                double s = t / (double) (interpDetail+1 /*fixed*/);
                // std::cout <<"s = " << s << std::endl;
                // calculate basis functions
                // for controls
                double h1 = 2.0 * s * s * s - 3.0 * s * s + 1.0;
                double h2 = -2.0 * s * s * s + 3.0 * s * s;
                // for tangents
                double h3 = s * s * s - 2.0 * s * s + s;
                double h4 = s * s * s - s * s;
                
                // create temporary vector
               ofVec3f tempVec;
                tempVec = controlPts[i]; // p0
                tempVec *= h1;
                if (i<controlPts.size()-1){
                    tempVec += (controlPts[i + 1]*h2); // p3
                    // std::cout <<" tempVec = " <<  tempVec << std::endl;
                } else {
                    // final node
                    tempVec+= (controlPts[0] * h2); // p3
                    // std::cout <<" tempVec = " <<  tempVec << std::endl;
                }
                // tangent 1
                tempVec += (t1 * h3); // p1
                // tangent 2
                tempVec += (t2 * h4); // p2
                tempVecs.push_back(tempVec);
                //std::cout <<" tempVec["<<t<<"] = " <<  tempVec << std::endl;
            }
        }
        // add last control point to tempVecs
        tempVecs.push_back(controlPts[controlPts.size() - 1]);
        // curve smoothness terminates at end of path
    } else {
        // std::cout << "in Spline3d catch all else" << std::endl;
        for (int i = 0; i < controlPts.size() - 1; i++) {
            tempVecs.push_back(controlPts[i]);
           ofVec3f t1;
           ofVec3f t2;
            // equation to calculate spline tangents
            // Ti = a * ( Pi+1 - Pi-1 )
            
            // tangent 1 (i)
            // Pi+1
            t1 = controlPts[i + 1];
            // Pi-1
            if (i > 0) {
                t1 -= controlPts[i - 1];
            } else {
                t1 -= controlPts[i];
            }
            t1 *= smoothness;
            
            // tangent 2 (i+1)
            // Pi+1
            if (i < controlPts.size() - 2) {
                t2 = controlPts[i + 2];
                
                // Pi-1
                t2 -= controlPts[i];
            } else {
                t2 = controlPts[i + 1];
                
                // Pi-1
                t2 -= controlPts[i];
            }
            
            t2 *= smoothness;
            
            for (int t = 1; t < interpDetail+1; t++) {
                // scale between 0.0-1.0
                double s = t / (double) (interpDetail+1);
                // calculate basis functions
                // for controls
                double h1 = 2.0 * s * s * s - 3.0 * s * s + 1.0;
                double h2 = -2.0 * s * s * s + 3.0 * s * s;
                // for tangents
                double h3 = s * s * s - 2.0 * s * s + s;
                double h4 = s * s * s - s * s;
                
                // create temporary vector
               ofVec3f tempVec;
                tempVec = controlPts[i]; // p0
                tempVec *= h1;
                tempVec += (controlPts[i + 1] * h2); // p3
                // tangent 1
                tempVec += (t1 * h3); // p1
                // tangent 2
                tempVec += (t2 * h4); // p2
                tempVecs.push_back(tempVec);
            }
        }
        //std::cout <<"here" << std::endl;
        // add last control point to tempVecs
        tempVecs.push_back(controlPts[controlPts.size() - 1]);
    }
    // copy array vals to verts array - NOTE: not efficient to do this.
    //verts = new ofVec3f[tempVecs.size()];
    for (int i = 0; i < tempVecs.size(); i++) {
        verts.push_back(tempVecs[i]);
        //std::cout <<" ONE:: verts["<<i<<"] = " <<  verts[i] << std::endl;
    }
}

/**
 * Set flag for Curve to be closed
 * overrides
 * @param isCurveClosed
 *            boolean value
 */
void Spline3d::setCurveClosed(bool isCurveClosed) {
    this->isCurveClosed = isCurveClosed;
    init();
}

/**
 * Set flag for Curve at Terminals to be continuous
 * 
 * @param isTerminalSmooth
 *            boolean value
 */
void Spline3d::setTerminalSmooth(bool isTerminalSmooth) {
    this->isTerminalSmooth = isTerminalSmooth;
    init();
}

/**
 * Draw the curve.
 * 
 */
void Spline3d::display() {
    // int len = vertsLength;
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0f, 10.0f, 0.0f);
    //glVertex3d(controlPts[0].getX(), controlPts[0].getY(), controlPts[0].getZ());
    //glVertex3d(tempVecs[0].getX(), tempVecs[0].getY(), tempVecs[0].getZ());
    // std::cout << "controlPts[0] = " <<  controlPts[0] << std::endl;
    for (int i = 0; i < verts.size(); i++) {
        //if (verts[i]) {
        // std::cout <<" temp Vecs["<<i<<"] = " <<  tempVecs[i] << std::endl;
        glVertex3d(verts[i].x, verts[i].y, verts[i].z);
        //glVertex3d(tempVecs[i].getX(), tempVecs[i].getY(), tempVecs[i].getZ());
        //  std::cout <<" TWO:: verts["<<i<<"] = " <<  verts[i] << std::endl;
        //}
        if (/*verts[i] != null && */isCurveClosed && i == verts.size()-1) {
            glVertex3d(verts[0].x, verts[0].y, verts[0].z);
        }
    }
    glEnd();
}

/**
 * Draw the control points.
 * 
 */
void Spline3d::displayControlPts() {
    // draw points
    for (int i = 0; i < controlPts.size(); i++) {
        if (i != 0 && i != controlPts.size() - 1) {
            glColor3f(.65f, .65f, .65f);
        } else {
            glColor3f(1.0f, 0.0f, .25f);
        }
        glPushMatrix();
        glTranslatef(controlPts[i].x, controlPts[i].y, controlPts[i].z);
        glRectd(- vertRad,  vertRad,  vertRad, -vertRad);
        glPopMatrix();
    }
    
}

/**
 * Draw the interpolated points.
 * 
 */
void Spline3d::displayInterpPts() {
    glColor3f(0.0f, 0.0f, 20.0f);
    
    // draw points
    for (int i = 0; i < verts.size(); i++) {
        //if (verts[i] != null) {
        glRectd(verts[i].x - vertRad,
                verts[i].y - vertRad, verts[i].x + vertRad,
                verts[i].z + vertRad);
        // }
    }
}

/**
 * Set the smoothenss value.
 * 
 */
void Spline3d::setSmoothness(float smoothness)
{
    this->smoothness = smoothness;
}

/**
 * get the smoothenss value.
 * 
 */
float Spline3d::getSmoothness(float smoothness) const
{
    return smoothness;
}


