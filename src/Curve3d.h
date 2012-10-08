//
//  Curve3d.h
//  Protobyte Library V01
//
//  Created by Ira Greenberg on 8/2/11.
//  Copyright 2011 SMU. All rights reserved.
//
// Library Usage:
// This work is licensed under the Creative Commons 
// Attribution-NonCommercial-ShareAlike 3.0 Unported License. 
// To view a copy of this license, visit 
// http://creativecommons.org/licenses/by-nc-sa/3.0/ 
// or send a letter to Creative Commons, 
// 444 Castro Street, Suite 900, 
// Mountain View, California, 94041, USA.
//

#ifndef Protobyte_Library_V01_Curve3d_h
#define Protobyte_Library_V01_Curve3d_h


#include "ofMain.h"
#include "Dimension3d.h"
#include <vector>


class Curve3d {
    
protected:
    /**
	 * Control point 1 of curve.
	 */
    ofVec3f controlPt0;
    
	/**
	 * Control point 2 of curve.
	 */
	ofVec3f controlPt1;
    
	/**
	 * Control point 3 of curve.
	 */
	ofVec3f controlPt2;
    
	/**
	 * Control point 4 of curve.
	 */
	ofVec3f controlPt3;
	
	/**
	 * Control point 5 of curve.
	 */
	ofVec3f controlPt4;
	
	/**
	 * Control point 6 of curve.
	 */
	ofVec3f controlPt5;
	
	/**
	 * Control point 7 of curve.
	 */
	ofVec3f controlPt6;
	
	/**
	 * Control point 8 of curve.
	 */
	ofVec3f controlPt7;
    
	/**
	 * Array of control points.
	 */
	ofVec3f* controlPts;
    
    /**
	 * Length of Array of control points.
	 */
    int controlPtsLength;
	
	/**
	 * The number of interpolated points along the curve.
	 */
    int interpDetail;
	
	/**
	 * Array of interpolated points along curve.
	 */
	ofVec3f* interpPts;
	
	/**
	 * Array of all curve vertsBuff.
	 */
	ofVec3f* verts;
    
    /**
	 * Length of verts array.
	 */
    int vertsLength;
    
	/**
	 * Radius of rectangle used for rendering vertsBuff
	 */
	double vertRad;
    // orig val = .075;
    
	/**
	 * boolean to specify whether the path is closed
	 */
	bool isCurveClosed;
	
    /**
	 * boolean to specify the curvature at the path terminals 
	 */
	bool isTerminalSmooth;
    
    /**
	 * vector temporarily stores vertices during calculations in init(); 
	 */
    std::vector<ofVec3f> tempVecs;
    
    
public:
    // constructors
    Curve3d();
    
    Curve3d(ofVec3f controlPt0, ofVec3f controlPt1, ofVec3f controlPt2, ofVec3f controlPt3,int interpDetail);
    
	Curve3d(ofVec3f controlPt0, ofVec3f controlPt1, ofVec3f controlPt2, ofVec3f controlPt3, int interpDetail, bool isCurveClosed);	
	
    Curve3d(ofVec3f controlPt0, ofVec3f controlPt1, ofVec3f controlPt2, ofVec3f controlPt3, ofVec3f controlPt4, ofVec3f controlPt5, int interpDetail);	
	
    Curve3d(ofVec3f controlPt0, ofVec3f controlPt1, ofVec3f controlPt2, ofVec3f controlPt3, ofVec3f controlPt4, ofVec3f controlPt5, int interpDetail, bool isCurveClosed);
	
    Curve3d(ofVec3f controlPt0, ofVec3f controlPt1, ofVec3f controlPt2, ofVec3f controlPt3, ofVec3f controlPt4, ofVec3f controlPt5, ofVec3f controlPt6, ofVec3f controlPt7, int interpDetail);	
	
    Curve3d(ofVec3f controlPt0, ofVec3f controlPt1, ofVec3f controlPt2, ofVec3f controlPt3, ofVec3f controlPt4, ofVec3f controlPt5, ofVec3f controlPt6, ofVec3f controlPt7, int interpDetail, bool isCurveClosed);    
	
    Curve3d(ofVec3f* controlPts, int controlPtsLength, int interpDetail);
    
    Curve3d(ofVec3f* controlPts, int controlPtsLength, int interpDetail, bool isCurveClosed);	
    
    // copy Constructor
    //Curve3d(Curve3d& curve3d_src);
    
    // overloaded assignment operator
    //Curve3d& operator=(Curve3d& curve3d_src);
	
	// destructor
    virtual ~Curve3d();
    
	// pure virtual methods
    /**
	 * Calculate the interpolated curve points populating the vecs array.
	 */
	virtual void init() = 0;
    
	/**
	 * Draw the curve.
	 */
	virtual  void display() = 0;
    
	/**
	 * Draw the curve points.
	 */
	virtual void displayControlPts() = 0;
	
	/**
	 * Draw the curve points.
	 */
	virtual void displayInterpPts() = 0;
    
	/**
	 * Returns length of the control points array.
	 */
    int getControlPtsLength();
    
    /**
	 * Returns length of the points between control points.
	 */
    int getInterpDetail();
    
    /**
	 * Get the first control point.
	 * 
	 * @return ofVec3f object
	 */
	ofVec3f getControlPt0() const;  
    
	/**
	 * Set the first control point.
	 * 
	 * @param controlPt0
	 *            ofVec3f object
	 */
	void setControlPt0(ofVec3f controlPt0);
    
	/**
	 * Get the second control point.
	 * 
	 * @return ofVec3f object
	 */
	ofVec3f getControlPt1() const;
    
	/**
	 * Set the second control point.
	 * 
	 * @param controlPt1
	 *            ofVec3f object
	 */
	void setControlPt1(ofVec3f controlPt1);
    
	/**
	 * Get the third control point.
	 * 
	 * @return ofVec3f object
	 */
	ofVec3f getControlPt2() const;
    
	/**
	 * Set the third control point.
	 * 
	 * @param controlPt2
	 *            ofVec3f object
	 */
	void setControlPt2(ofVec3f controlPt2);
    
	/**
	 * Get the fourth control point.
	 * 
	 * @return ofVec3f object
	 */
	ofVec3f getControlPt3() const;
    
	/**
	 * Set the fourth control point.
	 * 
	 * @param controlPt3
	 *            ofVec3f object
	 */
	void setControlPt3(ofVec3f controlPt3);
	
    /**
	 * Get the fifth control point.
	 * 
	 * @return ofVec3f object
	 */
	ofVec3f getControlPt4() const;
    
	/**
	 * Set the fifth control point.
	 * 
	 * @param controlPt4
	 *            ofVec3f object
	 */
	void setControlPt4(ofVec3f controlPt4);
	
    /**
	 * Get the sixth control point.
	 * 
	 * @return ofVec3f object
	 */
	ofVec3f getControlPt5() const;
    
	/**
	 * Set the sixth control point.
	 * 
	 * @param controlPt5
	 *            ofVec3f object
	 */
	void setControlPt5(ofVec3f controlPt5);
	
    /**
	 * Get the seventh control point.
	 * 
	 * @return ofVec3f object
	 */
	ofVec3f getControlPt6() const;
    
	/**
	 * Set the seventh control point.
	 * 
	 * @param controlPt6
	 *            ofVec3f object
	 */
	void setControlPt6(ofVec3f controlPt6);
    
    /**
	 * Get the eighth control point.
	 * 
	 * @return ofVec3f object
	 */
	ofVec3f getControlPt7() const;
    
	/**
	 * Set the eighth control point.
	 * 
	 * @param controlPt7
	 *            ofVec3f object
	 */
	void setControlPt7(ofVec3f controlPt7);
	
	
	/**
	 * Set the control points, with side effects
	 */
	void setControlPts(ofVec3f* controlPts);
    
    /**
	 * get a pointer to the  control points array, with side effects
	 */
	ofVec3f* getControlPts();
	
	/**
	 * Get the curve vertsBuff' length.
	 * 
	 * @return int
	 */
	int getVertsLength() const;
    
	/**
	 * Set all the curve points
	 * 
	 * @param uniqueVerts
	 *            Vector array
	 */
	void setVerts(ofVec3f* verts);
    
    /**
	 * Get pointer all the curve points
	 * 
	 * @param uniqueVerts
	 *            Vector array
	 */
	ofVec3f* getVerts();
    
    /**
	 * Get vector of all vertices
	 */
    std::vector<ofVec3f> getVertices();
    
	/**
	 * Get Curve3d object dimensions.
	 * 
	 * @return Dimension3D object
	 */
	Dimension3d getDimension() const;    
	
    /**
	 * Get vertex radius.
	 * 
	 * @return double value
	 */
	double getVertRad() const;
    
	/**
	 * Set vertex radius
	 * 
	 * @param vertRad
	 *            double value
	 */
	void setVertRad(double vertRad);
    
	/**
	 * Get flag value telling if curve is closed
	 * 
	 * @return boolean value
	 */
	bool getIsCurveClosed() const;
    
	/**
	 * Set flag for Curve to be closed
	 * 
	 * @param isCurveClosed
	 *            boolean value
	 */
	void setIsCurveClosed(bool isCurveClosed);
	
	/**
	 * Get flag value telling if curve at Terminals is continuous
	 * 
	 * @return boolean value
	 */
	bool getIsTerminalSmooth() const;
    
	/**
	 * Set flag for Curve at Terminals to be continuous
	 * 
	 * @param isTerminalSmooth
	 *            boolean value
	 */
	void setIsTerminalSmooth(bool isTerminalSmooth);
    
};

#endif
