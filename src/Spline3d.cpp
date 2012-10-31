//
//  Spline3d.cpp
//  Protobyte Library V01
//
//  Created by Ira Greenberg on 8/2/11.
//  Copyright 2011 SMU. All rights reserved.
//

#include "Spline3d.h"
#include "Quaternion.h"
#include "Matrix3D.h"

#include <iostream>

using namespace ijg;
//Matrix3D m;;

/**
 * Spline cubic curve class, where curve goes through all points. Curve is
 * specified by 6 points, with a constant specifying tension.
 * <p>
 */


Spline3d::Spline3d(ofVec3f controlPt0, ofVec3f controlPt1, ofVec3f controlPt2, ofVec3f controlPt3, ofVec3f controlPt4, ofVec3f controlPt5, ofVec3f controlPt6, ofVec3f controlPt7, int interpDetail, bool isCurveClosed, float smoothness):
Curve3d(controlPt0, controlPt1, controlPt2, controlPt3, controlPt4,controlPt5, controlPt6, controlPt7, interpDetail), smoothness(smoothness)
{
    // init();
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
    vertRad = 5;
    
    // detect if curve should be closed
    if (isCurveClosed) {
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
        //std::cout <<"Inside isTerminalSmooth block" << std::endl;
        for (int i = 0; i < controlPts.size()-1; i++) {
            // ONLY add inital control point to vertex list
            if(i==0)  { tempVecs.push_back(controlPts[i]); }
            
            ofVec3f t1, t2;
            // equation to calculate spline tangents
            // Ti = a * ( Pi+1 - Pi-1 )
            
            // tangent 1 (i)
            // Pi+1
            if (i < controlPts.size()-1) {
                t1 = controlPts[i + 1];
            } else {
                //uses 1st CP to control curvature on last point
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
                //uses 1st CP to control curvature on last point
                t2 = controlPts[0];
            } else {
                //uses 2nd CP to control curvature on last point
                t2 = controlPts[1];
            }
            // Pi-1
            t2 -= controlPts[i];
            t2 *= smoothness;
            
            //std::cout << "control point "<< i << " = " << controlPts[i] << std::endl;
            // FIXED 8/9/10 to allow symmetry on curve
            // ADDED 10/15/12 "<=" was "<"  - creates interpolated
            // point at control point, allowing derivatives to be calculated
            // for Frenet Frame (not sure I really need this once I get
            // parralel transport implemented - oh well...
            for (int t = 1; t <= interpDetail+1; t++) { /*fixed*/
                // scale between 0.0-1.0
                double s = t / (double) (interpDetail+1 /*fixed*/);
                // std::cout <<"s = " << s << std::endl;
                // calculate basis functions
                // for controls
                double h1 = 2.0 * s * s * s - 3.0 * s * s + 1.0; // 2*s^3 - 3*s^2 + 1
                double h2 = -2.0 * s * s * s + 3.0 * s * s; // -2*s^3 + 3*s^2
                // for tangents
                double h3 = s * s * s - 2.0 * s * s + s; // s^3 - 2*s^2 + s
                double h4 = s * s * s - s * s; // s^3 - s^2
                
                // create temporary vector
                ofVec3f tempVec, tempVec2, T, B, N;
                tempVec = controlPts[i]; // p0
                tempVec *= h1;
                if (i<controlPts.size()-1){ // NOT at end of curve
                    tempVec += (controlPts[i + 1]*h2); // p3
                } else {
                    // end of curve
                    tempVec+= (controlPts[0] * h2); // p3
                }
                // tangent 1
                tempVec += (t1 * h3); // p1
                // tangent 2
                tempVec += (t2 * h4); // p2
                
                //std::cout << "tempVec "<< t << " = " << tempVec << std::endl;
                tempVecs.push_back(tempVec);
                
            }
        }
        // add last control point to tempVecs
        //tempVecs.push_back(controlPts[controlPts.size() - 1]);
        // curve smoothness terminates at end of path
        
    } else {
        /******************************************/
        /***********NOT WORKING BELOW HERE*********/
        /******************************************/
        std::cout << "in Spline3d catch all else" << std::endl;
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
                double h1 = 2.0 * s * s * s - 3.0 * s * s + 1.0; // 2*s^3-3*s^2 + 1
                double h2 = -2.0 * s * s * s + 3.0 * s * s; // -2*s^3-3*s^2
                // for tangents
                double h3 = s * s * s - 2.0 * s * s + s; // s^3-2*s^3
                double h4 = s * s * s - s * s; // s^3 - s^2
                
                // 1st derivative for Frenet frame
                double y1 = 6.0 * s * s - 6.0 * s; // 6*s^2-6*s
                double y2 = -4.0 * s * s + 6.0 * s; // -6*s^2+6*s
                // for tangents
                double y3 = 3 * s * s - 6.0 * s * s; // 3s^2-6*s^2
                double y4 = 3 * s * s - s; // 3s^2 - s
                
                // 2nd derivative for Frenet frame
                double yy1 = 12.0 * s - 6.0; // 12*s-6
                double yy2 = -8.0 * s + 6.0; // -8*s+6
                // for tangents
                double yy3 = 6 * s - 12.0 * s; // 6s-12
                double yy4 = 6 * s; // 6s
                
                // create temporary vector
                ofVec3f tempVec, tempVec2, T, B, N;
                
                // calculate vertex
                tempVec = controlPts[i]; // p0
                tempVec *= h1;
                tempVec += (controlPts[i + 1] * h2); // p3
                // tangent 1
                tempVec += (t1 * h3); // p1
                // tangent 2
                tempVec += (t2 * h4); // p2
                tempVecs.push_back(tempVec);
                
                
                /****************************
                 ** Calculate Frenet Frame **
                 ****************************/
                /*
                 // calculate binormal
                 // 1st derivative Vi
                 T = controlPts[i]; // b0
                 T *= y1;
                 T += (controlPts[i + 1] * y2); // b3
                 // tangent 1
                 T += (t1 * y3); // b1
                 // tangent 2
                 T += (t2 * y4); // b2
                 
                 
                 
                 if(tempVecs.size()>2){
                 ofVec3f test = tempVecs[i+1]-tempVecs[i-1];
                 std::cout << "test = " << (t2.cross(t1)).normalize() << std::endl;
                 std::cout << "testVec = " << tempVec.normalize() << std::endl;
                 }
                 
                 // 2nd derivative
                 tempVec2 = controlPts[i]; // b0
                 tempVec2 *= yy1;
                 tempVec2 += (controlPts[i + 1] * yy2); // b3
                 // tangent 1
                 tempVec2 += (t1 * yy3); // b1
                 // tangent 2
                 tempVec2 += (t2 * yy4); // b2
                 tempVec2.normalize();
                 
                 T.normalize();
                 B = T.cross(tempVec2);
                 N = B.cross(T);
                 
                 
                 //std::cout <<"here" << std::endl;
                 //frenetFrames.push_back(FrenetFrame(tempVec, T, B, N));
                 */
            }
        }
        
        // add last control point to tempVecs DOESN'T SEEM NECESSARY ANY MORE
        // tempVecs.push_back(controlPts[controlPts.size() - 1]); // not needed
        
    }
    // copy array vals to verts array - NOTE: not efficient to do this.
    //verts = new ofVec3f[tempVecs.size()];
    for (int i = 0; i < tempVecs.size(); i++) {
        verts.push_back(tempVecs[i]);
        if (i==0){  std::cout << "\n****VERTS****" << std::endl; }
        //std::cout <<"verts["<<i<<"] = " <<  verts[i] << std::endl;
    }
    
    /******* Create Frenet Frame for extrusion *****/
    createFrenetFrame4();
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
    glColor3f(1, 1, 0);
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
        if (i != 0) {
            glColor3f(1, 1, 1);  // enables ends points to be rendered differently
            //vertRad = 5;
        } else {
            glColor3f(1, 1, 0);
            //vertRad = 2.5;
        }
        glPushMatrix();
        glTranslatef(controlPts[i].x, controlPts[i].y, controlPts[i].z);
        glRectd(- vertRad,  -vertRad,  vertRad*2, vertRad*2);
        glPopMatrix();
    }
    
}

/**
 * Draw the interpolated points.
 *
 */
void Spline3d::displayInterpPts()
{
    glColor3f(0, 1, 1);
    
    // draw points
    for (int i = 0; i < verts.size(); i++) {
        glPushMatrix();
        glTranslatef(verts[i].x, verts[i].y, verts[i].z);
        glRectd(- vertRad*.5,  -vertRad*.5,  vertRad, vertRad);
        glPopMatrix();
    }
}

/**
 * Draw the Frenet Frames.
 *
 */
void Spline3d::displayFrenetFrames(float len)
{
    for (int i = 0; i <verts.size(); i++) {
        frenetFrames[i].display(len);
    }
}

/**
 * Draw cross-section extruded along the spline path.
 * Default cross-section is an ellipse
 */
void Spline3d::drawCrossSections(){
    for (int i = 0; i <frenetFrames.size(); i++) {
        // draw cross-section ellipse
        glColor3f(1, 1, 1);
        glBegin(GL_POLYGON);
        float th = 0;
        for(int j=0; j<6; j++){
            float x = cos(th)*10;
            float y = sin(th)*10;
            float z = 0;
            float px = verts[i+1].x + x*frenetFrames[i].getN().x + y*frenetFrames[i].getB().x;
            float py = verts[i+1].y + x*frenetFrames[i].getN().y + y*frenetFrames[i].getB().y;
            float pz = verts[i+1].z + x*frenetFrames[i].getN().z + y*frenetFrames[i].getB().z;
            glVertex3f(px, py, pz);
            th += PI*2/6;
        }
        glEnd();
    }
    
    glPointSize(4);
    for (int i = 0; i <frenetFrames.size(); i++) {
        // draw cross-section ellipse
        glBegin(GL_POINTS);
        float th = 0;
        for(int j=0; j<6; j++){
            float x = cos(th)*10;
            float y = sin(th)*10;
            float z = 0;
            float px = verts[i+1].x + x*frenetFrames[i].getN().x + y*frenetFrames[i].getB().x;
            float py = verts[i+1].y + x*frenetFrames[i].getN().y + y*frenetFrames[i].getB().y;
            float pz = verts[i+1].z + x*frenetFrames[i].getN().z + y*frenetFrames[i].getB().z;
            glColor3f(0, 1-1/(j+1), 1/(j+1));
            glVertex3f(px, py, pz);
            th += PI*2/6;
        }
        glEnd();
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

/**
 * Calculate a Frenet frame for extrusion (tubes/tendrils).
 * - private access
 */
void Spline3d::createFrenetFrame()
{
    ofVec3f t0, t1, t2, initT, initB, initN, newT, newB, newN, axis;
    for (int i = 1; i <verts.size(); i++) {
        
        t0 = verts[i-1];
        t1 = verts[i];
        t2 = verts[i+1];
        
        initT = t2-t0;
        initT.normalize();
        
        initB = t1;
        initB.cross(t2);
        initB.normalize();
        
        initN = initB;
        initN.cross(initT);
        initN.normalize();
        std::cout << "initT("<<i<<") = " << initT <<std::endl;
        std::cout << "initB("<<i<<") = " << initB <<std::endl;
        std::cout << "initN("<<i<<") = " << initN <<std::endl;
        
        
        frenetFrames.push_back(FrenetFrame(verts[i], initT, initB, initN));
        
        
    }
    
}


void Spline3d::createFrenetFrame4()
{
    std::vector<ofVec3f> tans;
    float theta;
    ofVec3f cp0, cp1, cp2;
    ofVec3f tan, biNorm, norm, nextTan, nextBiNorm, nextNorm;
    for (int i = 1; i <verts.size(); i++) {
        
        cp0 = verts[i-1];
        cp1 = verts[i];
        cp2 = verts[i+1];
        
        tan = cp2 - cp0;
        tan.normalize();
        tans.push_back(tan);
            
        if (i==1){
            
            biNorm = cp1;
            biNorm.cross(cp2);
            biNorm.normalize();
            
            norm = biNorm;
            norm.cross(tan);
            norm.normalize();
        }
              // std::cout << "tan = " << tan <<std::endl;
               // std::cout << "biNorm = " << biNorm <<std::endl;
               // std::cout << "norm = " << norm <<std::endl;
    }
    // rotate frame
    for (int i = 0; i <tans.size()-1; i++) {
        
         //std::cout<<"tans = "<<tans.at(i)<<std::endl;
        if (biNorm.length() == 0) {
            nextNorm = norm;
        } else {
            theta = acos(tans.at(i).dot(tans.at(i+1)));
            //theta = ofRandom(PI);
            
            //std::cout << "theta = " << theta*180/PI << std::endl;
            Quaternion q(biNorm, theta);
         
            //Matrix3D m;
            //nextNorm = m.getRotate(theta, biNorm, norm);
            std::cout << "norm before = " << norm << std::endl;
            nextNorm = q.getRotate(norm);
            //nextNorm = norm;
            std::cout << "norm after = " << nextNorm << std::endl;
            nextBiNorm = tans.at(i+1);
            nextBiNorm.cross(nextNorm);

            
        }
        frenetFrames.push_back(FrenetFrame(verts[i], tans.at(i), biNorm.normalize(), norm.normalize()));
        norm = nextNorm;
        biNorm = nextBiNorm;
    }
    
}
void Spline3d::createFrenetFrame3()
{
    std::vector<ofVec3f> tans, biNorms, norms;
    float theta;
    ofVec3f t0, t1, t2, initT, initB, initN, newT, newB, newN, axis;
    for (int i = 1; i <verts.size(); i++) {
        
        t0 = verts[i-1];
        t1 = verts[i];
        t2 = verts[i+1];
        
        initT = t2-t0;
        initT.normalize();
        tans.push_back(initT);
        
        initB = t1;
        initB.cross(t2);
        initB.normalize();
        biNorms.push_back(initB);
        
        initN = initB;
        initN.cross(initT);
        initN.normalize();
        norms.push_back(initN);
        //        std::cout << "initT("<<i<<") = " << initT <<std::endl;
        //        std::cout << "initB("<<i<<") = " << initB <<std::endl;
        //        std::cout << "initN("<<i<<") = " << initN <<std::endl;
    }
    // rotate
    
    for (int i = 1; i <tans.size()-2; i++) {
        std::cout<<"biNorms.at(i) = " << biNorms.at(i)<<std::endl;
        if (biNorms.at(i).length() == 0){
            norms.at(i) = norms.at(i-1);
        } else {
            theta = acos(tans.at(i-1).dot(tans.at(i)));
            Quaternion q(biNorms.at(i-1), theta);
            norms.at(i) = q.getRotate(norms.at(i-1));
            //biNorms.at(i+1) = q.getRotate(biNorms.at(i));
            //tans.at(i+1) = q.getRotate(tans.at(i));
            biNorms.at(i) = tans.at(i).cross(norms.at(i));
        }
        frenetFrames.push_back(FrenetFrame(verts[i], tans.at(i-1), biNorms.at(i-1), norms.at(i-1)));
    }
    
}



/**
 * Calculate a Frenet frame for extrusion (tubes/tendrils).
 * - private access
 */
void Spline3d::createFrenetFrame2()
{
    // 1st capture all tangent vectors
    std::vector<ofVec3f> tans, biNorms, norms;
    std::vector<float> biNormLens;
    ofVec3f temp;
    float theta;
    float biNormalLen;
    
    
    // tangents along spline
    for (int i = 2; i <verts.size(); i++) {
        ofVec3f temp = verts.at(i)-verts.at(i-2);
        temp.normalize();
        tans.push_back(temp);
        //std::cout << "tans.at("<<i-2<<") = " << tans.at(i-2) <<std::endl;
    }
    
    // Frenet frame biNorms and norms
    for (int i = 0; i <tans.size()-1; i++) {
        //binorm
        temp = tans.at(i).cross(tans.at(i+1));
        biNormLens.push_back(temp.length());
        temp.normalize();
        biNorms.push_back(temp);
        //std::cout << "biNorms.at(" << i << ") = " << biNorms.at(i) << std::endl;
        
        //norms
        temp = biNorms.at(i).cross(tans.at(i));
        temp.normalize();
        norms.push_back(temp);
        std::cout << "norms.at(" << i << ") = " << norms.at(i) << std::endl;
    }
    
    // rotate
    for (int i = 0; i <tans.size()-2; i++) {
        if (biNormLens.at(i) == 0){
            norms.at(i+1) = norms.at(i);
        } else {
            theta = acos(tans.at(i).dot(tans.at(i+1)));
            Quaternion q(biNorms.at(i), theta);
            norms.at(i+1) = q.getRotate(norms.at(i));
            //biNorms.at(i+1) = tans.at(i+1).cross(norms.at(i+1));
            
            
        }
        frenetFrames.push_back(FrenetFrame(verts[i+1], tans.at(i), biNorms.at(i), norms.at(i)));
    }
    
    
    
}



