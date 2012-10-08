//
//  Curve3d.cpp
//  Protobyte Library V01
//
//  Created by Ira Greenberg on 8/2/11.
//  Copyright 2011 SMU. All rights reserved.
//

#include "Curve3d.h"
#include <iostream>

Curve3d::Curve3d(){
}

Curve3d::Curve3d(ofVec3f controlPt0, ofVec3f controlPt1, ofVec3f controlPt2, ofVec3f controlPt3, int interpDetail): 
controlPt0(controlPt0), controlPt1(controlPt1), controlPt2(controlPt2), controlPt3(controlPt3), interpDetail(interpDetail) {
    controlPtsLength = 4;
    controlPts = new ofVec3f[controlPtsLength];
    controlPts[0] = controlPt0; controlPts[1] = controlPt1; controlPts[2] = controlPt2; controlPts[3] = controlPt3;
}

Curve3d::Curve3d(ofVec3f controlPt0, ofVec3f controlPt1, ofVec3f controlPt2, ofVec3f controlPt3,int interpDetail, bool isCurveClosed): 
controlPt0(controlPt0), controlPt1(controlPt1), controlPt2(controlPt2), controlPt3(controlPt3), interpDetail(interpDetail), isCurveClosed(isCurveClosed) {
    controlPtsLength = 4;
    controlPts = new ofVec3f[controlPtsLength];
    controlPts[0] = controlPt0; controlPts[1] = controlPt1; controlPts[2] = controlPt2; controlPts[3] = controlPt3;
}

Curve3d::Curve3d(ofVec3f controlPt0, ofVec3f controlPt1, ofVec3f controlPt2, ofVec3f controlPt3, ofVec3f controlPt4, ofVec3f controlPt5, int interpDetail): 
controlPt0(controlPt0), controlPt1(controlPt1), controlPt2(controlPt2), controlPt3(controlPt3), controlPt4(controlPt4), controlPt5(controlPt5), interpDetail(interpDetail) {
    controlPtsLength = 6;
    controlPts = new ofVec3f[controlPtsLength];
    controlPts[0] = controlPt0; controlPts[1] = controlPt1; controlPts[2] = controlPt2; controlPts[3] = controlPt3; controlPts[4] = controlPt4; controlPts[5] = controlPt5;
}

Curve3d::Curve3d(ofVec3f controlPt0, ofVec3f controlPt1, ofVec3f controlPt2, ofVec3f controlPt3, ofVec3f controlPt4, ofVec3f controlPt5, int interpDetail, bool isCurveClosed): 
controlPt0(controlPt0), controlPt1(controlPt1), controlPt2(controlPt2), controlPt3(controlPt3), controlPt4(controlPt4), controlPt5(controlPt5), interpDetail(interpDetail), isCurveClosed(isCurveClosed) {
    controlPtsLength = 6;
    controlPts = new ofVec3f[controlPtsLength];
    controlPts[0] = controlPt0; controlPts[1] = controlPt1; controlPts[2] = controlPt2; controlPts[3] = controlPt3; controlPts[4] = controlPt4; controlPts[5] = controlPt5;
}

Curve3d::Curve3d(ofVec3f controlPt0, ofVec3f controlPt1, ofVec3f controlPt2, ofVec3f controlPt3, ofVec3f controlPt4, ofVec3f controlPt5, ofVec3f controlPt6, ofVec3f controlPt7, int interpDetail): 
controlPt0(controlPt0), controlPt1(controlPt1), controlPt2(controlPt2), controlPt3(controlPt3), controlPt4(controlPt4), controlPt5(controlPt5), controlPt6(controlPt6), controlPt7(controlPt7), interpDetail(interpDetail) {
    controlPtsLength = 8;
    controlPts = new ofVec3f[controlPtsLength];
    controlPts[0] = controlPt0; controlPts[1] = controlPt1; controlPts[2] = controlPt2; controlPts[3] = controlPt3; controlPts[4] = controlPt4; controlPts[5] = controlPt5; controlPts[6] = controlPt6; controlPts[7] = controlPt7;
}

Curve3d::Curve3d(ofVec3f controlPt0, ofVec3f controlPt1, ofVec3f controlPt2, ofVec3f controlPt3, ofVec3f controlPt4, ofVec3f controlPt5, ofVec3f controlPt6, ofVec3f controlPt7, int interpDetail, bool isCurveClosed): 
controlPt0(controlPt0), controlPt1(controlPt1), controlPt2(controlPt2), controlPt3(controlPt3), controlPt4(controlPt4), controlPt5(controlPt5), controlPt6(controlPt6), controlPt7(controlPt7), interpDetail(interpDetail),isCurveClosed(isCurveClosed) {
    controlPtsLength = 8;
    controlPts = new ofVec3f[controlPtsLength];
    controlPts[0] = controlPt0; controlPts[1] = controlPt1; controlPts[2] = controlPt2; controlPts[3] = controlPt3; controlPts[4] = controlPt4; controlPts[5] = controlPt5; controlPts[6] = controlPt6; controlPts[7] = controlPt7;
}

Curve3d::Curve3d(ofVec3f* controlPts, int controlPtsLength, int interpDetail): 
controlPts(controlPts), controlPtsLength(controlPtsLength), interpDetail(interpDetail) {
}

Curve3d::Curve3d(ofVec3f* controlPts, int controlPtsLength, int interpDetail, bool isCurveClosed): 
controlPts(controlPts), controlPtsLength(controlPtsLength), interpDetail(interpDetail), isCurveClosed(isCurveClosed) {
}

Curve3d::~Curve3d(){}

// copy Constructor
/*
 Curve3d::Curve3d(Curve3d& curve3d_src){
 }
 */

// overloaded assignment operator
/*
 Curve3d& Curve3d::operator=(Curve3d& curve3d_src) {
 return *this;
 }
 */



/**
 * Get the first control point.
 * 
 * @return ofVec3f object
 */
ofVec3f Curve3d::getControlPt0() const {
    return controlPt0;
}

/**
 * Set the first control point.
 * 
 * @param controlPt0
 *            ofVec3f object
 */
void Curve3d::setControlPt0(ofVec3f controlPt0) {
    this->controlPt0 = controlPt0;
}

/**
 * Get the second control point.
 * 
 * @return ofVec3f object
 */
ofVec3f Curve3d::getControlPt1() const  {
    return controlPt1;
}

/**
 * Set the second control point.
 * 
 * @param controlPt1
 *            ofVec3f object
 */
void Curve3d::setControlPt1(ofVec3f controlPt1) {
    this->controlPt1 = controlPt1;
}

/**
 * Get the third control point.
 * 
 * @return ofVec3f object
 */
ofVec3f Curve3d::getControlPt2() const  {
    return controlPt2;
}

/**
 * Set the third control point.
 * 
 * @param controlPt2
 *            ofVec3f object
 */
void Curve3d::setControlPt2(ofVec3f controlPt2) {
    this->controlPt2 = controlPt2;
}

/**
 * Get the fourth control point.
 * 
 * @return ofVec3f object
 */
ofVec3f Curve3d::getControlPt3() const  {
    return controlPt3;
}

/**
 * Set the fourth control point.
 * 
 * @param controlPt3
 *            ofVec3f object
 */
void Curve3d::setControlPt3(ofVec3f controlPt3) {
    this->controlPt3 = controlPt3;
}

/**
 * Get the fifth control point.
 * 
 * @return ofVec3f object
 */
ofVec3f Curve3d::getControlPt4() const  {
    return controlPt4;
}

/**
 * Set the fifth control point.
 * 
 * @param controlPt4
 *            ofVec3f object
 */
void Curve3d::setControlPt4(ofVec3f controlPt4) {
    this->controlPt4 = controlPt4;
}

/**
 * Get the sixth control point.
 * 
 * @return ofVec3f object
 */
ofVec3f Curve3d::getControlPt5() const  {
    return controlPt5;
}

/**
 * Set the sixth control point.
 * 
 * @param controlPt5
 *            ofVec3f object
 */
void Curve3d::setControlPt5(ofVec3f controlPt5) {
    this->controlPt5 = controlPt5;
}

/**
 * Get the seventh control point.
 * 
 * @return ofVec3f object
 */
ofVec3f Curve3d::getControlPt6() const  {
    return controlPt6;
}

/**
 * Set the seventh control point.
 * 
 * @param controlPt6
 *            ofVec3f object
 */
void Curve3d::setControlPt6(ofVec3f controlPt6) {
    this->controlPt6 = controlPt6;
}

/**
 * Get the eighth control point.
 * 
 * @return ofVec3f object
 */
ofVec3f Curve3d::getControlPt7() const  {
    return controlPt7;
}

/**
 * Set the eighth control point.
 * 
 * @param controlPt7
 *            ofVec3f object
 */
void Curve3d::setControlPt7(ofVec3f controlPt7) {
    this->controlPt7 = controlPt7;
}


/**
 * Set the control points.
 * with side effects
 */
void Curve3d::setControlPts(ofVec3f* controlPts) {
    this->controlPts = controlPts;
}

/**
 * Gets control points array length.
 */
int Curve3d::getControlPtsLength() {
    return controlPtsLength;
}

/**
 * Gets point count between control points.
 */
int Curve3d::getInterpDetail(){
    return interpDetail;
}

/**
 * Get a pointer to the control points array.
 * with side effects
 */
ofVec3f* Curve3d::getControlPts() {
    return controlPts;
}


/**
 * Get the curve vertsBuff' length.
 * 
 * @return int
 */
int Curve3d::getVertsLength() const  {
    return vertsLength;
}

/**
 * Set all the curve points
 * 
 * @param uniqueVerts
 *            Vector[] array
 */
void Curve3d::setVerts(ofVec3f* verts) {
    this->verts = verts;
    //std::cout<<"I'm in here dude!!!"<<std::endl;
}

/**
 * Get pointer all the curve points
 * 
 * @param uniqueVerts
 *            Vector array
 */
ofVec3f* Curve3d::getVerts() {
    return verts;
}


/**
 * Get a pointer to a
 * vector of all the vertices
 **** To DO NOTE - switch all verts to vector eventually ****
 */
std::vector<ofVec3f> Curve3d::getVertices(){
    return tempVecs;
    //return verts;

}

/**
 * Get Curve3d object dimensions.
 * 
 * @return Dimension3D object
 */
Dimension3d Curve3d::getDimension() const  {
    double minX=0, maxX=0, minY=0, maxY=0, minZ=0, maxZ=0.0;
    minX = verts[0].getX();
    maxX = verts[vertsLength-1].getX();
    minY = verts[0].getY();
    maxY = verts[vertsLength-1].getY();
    minZ = verts[0].getZ();
    maxZ = verts[vertsLength-1].getZ();
    
    for(int i=1; i<vertsLength; i++){
        minX = minX < verts[i].getX() ? minX : verts[i].getX();
        maxX = maxX > verts[i].getX() ? maxX : verts[i].getX();
        
        minY = minY < verts[i].getY() ? minY : verts[i].getY();
        maxY = maxY > verts[i].getY() ? maxY : verts[i].getY();
        
        minZ = minZ < verts[i].getZ() ? minZ : verts[i].getZ();
        maxZ = maxZ > verts[i].getZ() ? maxZ : verts[i].getZ();
    }
    Dimension3d dim3d(maxX-minX, maxY-minY, maxZ-minZ);
    return dim3d;
}

/**
 * Get vertex radius.
 * 
 * @return double value
 */

double Curve3d::getVertRad() const  {
    return vertRad;
}

/**
 * Set vertex radius
 * 
 * @param vertRad
 *            double value
 */
void Curve3d::setVertRad(double vertRad) {
    this->vertRad = vertRad;
}


/**
 * Get flag value telling if curve is closed
 * 
 * @return bool value
 */
bool Curve3d::getIsCurveClosed() const  {
    return isCurveClosed;
}

/**
 * Set flag for Curve to be closed
 * 
 * @param isCurveClosed
 *            bool value
 */
void Curve3d::setIsCurveClosed(bool isCurveClosed) {
    this->isCurveClosed = isCurveClosed;
}

/**
 * Get flag value telling if curve at Terminals is continuous
 * 
 * @return bool value
 */
bool Curve3d::getIsTerminalSmooth() const  {
    return isTerminalSmooth;
}

/**
 * Set flag for Curve at Terminals to be continuous
 * 
 * @param isTerminalSmooth
 *            bool value
 */
void Curve3d::setIsTerminalSmooth(bool isTerminalSmooth) {
    this->isTerminalSmooth = isTerminalSmooth;
}
