//
//  Spline3d.h
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

#ifndef Protobyte_Library_V01_Spline3d_h
#define Protobyte_Library_V01_Spline3d_h

#include "Curve3d.h"


/**
 * Spline cubic curve class, where curve goes through all points. Curve is
 * specified by 6 points, with a constant specifying tension.
 * <p>
 */

class Spline3d: public Curve3d {
    
public:
    Spline3d();
    Spline3d(Vector3df* controlPts, int controlPtsLength, int interpDetail, double smoothness);	
	Spline3d(Vector3df* controlPts, int controlPtsLength, int interpDetail, double smoothness, bool isCurveClosed);  
    
    ~Spline3d();
    
    // copy constructor
    //Spline3d(Spline3d& spline3d_src);
    
    // overloaded assignment operator
    //Spline3d& operator=Spline3d& spline3d_src) 
    
    /**
	 * Set flag for Curve to be closed
	 * overrides
	 * @param isCurveClosed
	 *            boolean value
	 */
	void setCurveClosed(bool isCurveClosed);	
	
    /**
	 * Set flag for Curve at Terminals to be continuous
	 * 
	 * @param isTerminalSmooth
	 *            boolean value
	 */
	void setTerminalSmooth(bool isTerminalSmooth);
	
    /**
	 * Draw the curve.
	 * 
	 */
	void display();    
	
    /**
	 * Draw the control points.
	 * 
	 */
	void displayControlPts();    
	
    /**
	 * Draw the interpolated points.
	 * 
	 */
	void displayInterpPts();
    
    
private:
    /**
	 * Controls spline curve curvature.
	 */
    double smoothness;
    
    /**
     * allocate memory and initialize stuff.
     */
    void init();
    
};


#endif
