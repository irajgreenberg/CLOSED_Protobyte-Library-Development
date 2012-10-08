//
//  ExtrudeObj.cpp
//  Protobyte Library V01
//
//  Created by Ira Greenberg on 8/2/11.
//  Copyright 2011 SMU. All rights reserved.
//

#include "ExtrudeObj.h"
#include <iostream>




// delete eventually 
Vector3df vTemp();

ExtrudeObj::ExtrudeObj() {
    radius = .075;
}

ExtrudeObj::ExtrudeObj(Curve3d* path, int detail):
path(path), Geom3d(detail)
{
    radius = .075;
    init();
}

ExtrudeObj::ExtrudeObj(Curve3d* path,  float radius, int detail):
path(path), radius(radius), Geom3d(detail) 
{
    init();
}


ExtrudeObj::~ExtrudeObj() {
    delete [] unalignedVerts;
}



/*
 vertCount = detail * segs;
 triFaceCount = vertCount*2;
 
 indicesCount = triFaceCount*3;
 
 allocateMemory();
 createVertices();
 createIndices();
 createFaces();
 createVertexNormals();
 createCoords();
 */

// Need to implement - or become abstract
void ExtrudeObj::init() {
    unalignedVerts = new Vector3df[detail]; // used for cross-section alignment
    
    pathCount = (int)path->getVertices().size();
    vertCount = (pathCount)*detail;
    triFaceCount = (pathCount-1)*detail*2;
    indicesCount = triFaceCount*3;
    
    allocateMemory();
    createVertices();
    createIndices();
    createFaces();
    createVertexNormals();
    createCoords();
    
}

void ExtrudeObj::createVertices(){
    // switched from returned vector<Vector3df> to Vector3df* 8/29/11
    pathVerts = path->getVerts();
    //pathVertices = path->getVertices();
    float theta = 0.0;
    for (int i=0; i<pathCount; i++){
        Vector3df temp0,temp1;
        
        //*************************************************
        // step 1. Translate segment vector to origin
        //*************************************************
        temp1 = pathVerts[i];
        if (i>0){
            temp0 = pathVerts[i-1]; 
            temp1-=temp0;
        } else {
            temp1 = pathVerts[i+1];
            temp0 = pathVerts[0]; 
            temp1-=temp0;
        }
        
        Vector3df cp(0, 0, 0);
        temp1.cross(Vector3df(0, 0, 1), cp);
        //std::cout<< "temp1.cross(Vector3df(0, 0, 1)) "<< i<< " = " << cp << std::endl;
        //std::cout<< "temp1 "<< i<< " = " << temp1 << std::endl;
        
        // works for spirals arond z-axis
        /*if (cp.x>0){
         theta = M_PI;
         } else {
         theta = 0;
         }*/
        
        
        
        temp1.normalize(); 
        //*************************************************
        // step 2. rotate vector around x-axis to xz-plane 
        //*************************************************
        float d1 = sqrt(temp1.y*temp1.y + temp1.z*temp1.z);
        float c1 = temp1.z/d1;
        float s1 = temp1.y/d1;
        
        float y = temp1.y*c1 - temp1.z*s1;
        float z = temp1.y*s1 + temp1.z*c1;
        float x = temp1.x;
        
        temp1.x = x;
        temp1.y = y;
        temp1.z = z;
        
        
        //*************************************************
        // step 3. rotate around y-axis to align with z-axis 
        //*************************************************
        float d2 = sqrt(temp1.x* temp1.x +  temp1.y* temp1.y +  temp1.z* temp1.z);
        float c2 = d1/d2;
        float s2 =  temp1.x/d2;
        
        z = temp1.z*c2 + temp1.x*s2;
        x = - temp1.z*s2 + temp1.x*c2;
        y = temp1.y;
        
        temp1.x = x;
        temp1.y = y;
        temp1.z = z;
        
        //*************************************************
        // step 4. Create cross-section of vertices 
        //*************************************************
        
        
        for (int j=0; j<detail; j++){
            float myX = temp1.x + cos(theta)*radius;
            float myY = temp1.y + sin(theta)*radius;
            verts[i*detail+j] = Vector3df(myX, myY, 0);
            theta -= M_PI*2.0/detail;
            
            /* if (j==0){
             Vector3df cp(0,0,0);
             float d = verts[(i-1)*detail+j].dot(verts[i*detail+j]);
             d/=(verts[(i-1)*detail+j].mag()*verts[i*detail+j].mag());
             std::cout << acos(d)<<std::endl;;
             //std::cout<< "temp1.cross(Vector3df(0, 0, 1)) "<< i<< " = " << cp << std::endl;
             }*/
        }
        
        
        //*************************************************
        // step 5. (un)rotate verts around y-axis 
        //*************************************************
        for (int j=0; j<detail; j++){
            Vector3df* v = &verts[i*detail+j];
            z = v->z*c2 - v->x*s2;
            x = v->z*s2 + v->x*c2;
            y = v->y;
            
            v->x = x;
            v->y = y;
            v->z = z;
        }
        
        //*************************************************
        // step 6. (un)rotate verts around x-axis 
        //*************************************************
        for (int j=0; j<detail; j++){
            Vector3df* v = &verts[i*detail+j];
            y = v->y*c1 + v->z*s1;
            z = -v->y*s1 + v->z*c1;
            x = v->x;
            
            v->x = x;
            v->y = y;
            v->z = z;
        }
        
        //*************************************************
        // step 7. (un)translate from origin 
        //*************************************************
        // for ribbon, start M_PI/4.0;
        for (int j=0; j<detail; j++){
            
            // shift cross-section back to translated vector
            verts[i*detail+j].add(pathVerts[i]);
        }
    }
}




/*void ExtrudeObj::createVertices(){
 static int lastAxis = 0;
 pathVertices = path->getVertices();
 
 for (int i=0; i<pathCount; i++){
 Vector3df temp0,temp1;
 temp1 = pathVertices[i];
 if (i>0){
 temp0 = pathVertices[i-1]; 
 temp1-=temp0;
 } else {
 temp1 = pathVertices[i+1];
 temp0 = pathVertices[0]; 
 temp1-=temp0;
 }
 
 temp1.normalize(); 
 
 //std::cout<< "angle between vector and x-axis = "<<acos(temp1.dot(Vector3df(1,0,0)))/M_PI*180.0 << std::endl;
 //std::cout<< "angle between vector and y-axis = "<<acos(temp1.dot(Vector3df(0,1,0)))/M_PI*180.0 << std::endl;
 //std::cout<< "angle between vector and z-axis = "<<acos(temp1.dot(Vector3df(0,0,1)))/M_PI*180.0 << std::endl;
 
 
 
 // find vector component with shortest magnitude
 // this creates a mess!!!
 int axis = 0;
 if (fabs(temp1.x) < fabs(temp1.y) ){
 if (fabs(temp1.x) < fabs(temp1.z) ){
 axis =  0;
 } else {
 axis =  2;
 }
 } else {
 if (fabs(temp1.y) < fabs(temp1.z)){
 axis =  1;
 } else {
 axis = 2;
 }
 
 }
 //axis = 0;// bypass axis check
 float theta = 0.0; // for ribbon, start M_PI/4.0;
 Vector3df perp;
 switch (axis){
 case 0:
 temp1.cross( Vector3df(1, 0, 0), perp );
 std::cout<<"x "<<i<< " == " <<temp1.x << std::endl;
 break;
 case 1:
 temp1.cross( Vector3df(0, 1, 0), perp );
 std::cout<<"y "<<i<< " == " <<temp1.y << std::endl;
 break;
 case 2:
 temp1.cross( Vector3df(0, 0, 1), perp );
 std::cout<<"z "<<i<< " == " <<temp1.z << std::endl;
 break;
 }
 //axis = 0; // bypass axis selection
 theta = 0;
 perp.normalize();
 perp.mult(radius);
 
 for (int j=0; j<detail; j++){
 verts[i*detail+j] = perp;
 }
 
 //double tempTheta = 0.0;
 // for (int j=0; j<detail; j++){
 // verts[i*detail+j] = Vector3df(cos(tempTheta)*radius, sin(tempTheta)*radius, 0);
 // tempTheta -= M_PI*2.0/detail;
 // verts[i*detail+j].add(pathVertices[i]);
 // }
 
 //float theta = 0.0; // for ribbon, start M_PI/4.0;
 for (int j=0; j<detail; j++){
 Matrix4d::rotateAroundAxis(verts[i*detail+j], temp1, theta);
 
 // shift cross-section back to translated vector
 verts[i*detail+j].add(pathVertices[i]);
 theta -= M_PI*2.0/detail;
 }
 }
 }
 */

/*void ExtrudeObj::createVertices(){
 pathVertices = path->getVertices();
 
 for (int i=0; i<pathCount; i++){
 Vector3df temp0,temp1;
 temp1 = pathVertices[i];
 if (i>0){
 temp0 = pathVertices[i-1]; 
 temp1-=temp0;
 } else {
 temp1 = pathVertices[i+1];
 temp0 = pathVertices[0]; 
 temp1-=temp0;
 }
 
 temp1.normalize(); 
 
 // find vector component with shortest magnitude
 // this creates a mess!!!
 int axis = 0;
 if (fabs(temp1.x) < fabs(temp1.y) ){
 if (fabs(temp1.x) < fabs(temp1.z) ){
 axis =  0;
 } else {
 axis =  2;
 }
 } else {
 if (fabs(temp1.y) < fabs(temp1.z)){
 axis =  1;
 } else {
 axis = 2;
 }
 
 }
 axis = 0;// bypass axis check
 Vector3df perp;
 switch (axis){
 case 0:
 temp1.cross( Vector3df(1, 0, 0), perp );
 std::cout<<"x "<<i<< " == " <<temp1.x << std::endl;
 break;
 case 1:
 temp1.cross( Vector3df(0, 1, 0), perp );
 std::cout<<"y "<<i<< " == " <<temp1.y << std::endl;
 break;
 case 2:
 temp1.cross( Vector3df(0, 0, 1), perp );
 std::cout<<"z "<<i<< " == " <<temp1.z << std::endl;
 break;
 }
 
 perp.normalize();
 perp.mult(radius);
 for (int j=0; j<detail; j++){
 verts[i*detail+j] = perp;
 
 }
 
 float theta = 0.0; // for ribbon, start M_PI/4.0;
 for (int j=0; j<detail; j++){
 Matrix4d::rotateAroundAxis(verts[i*detail+j], temp1, theta);
 
 // shift cross-section back to translated vector
 verts[i*detail+j].add(pathVertices[i]);
 theta -= M_PI*2.0/detail;
 }
 }
 }*/


void ExtrudeObj::createIndices() {
    //int indicesCounter = 0;
    for (int i=0; i<pathCount-1; i++){
        for ( int j=0; j<detail; j++){
            if (j<detail-1){
                /*indices[indicesCounter++] = detail*i + j;
                 indices[indicesCounter++] = detail*(i+1) + j;
                 indices[indicesCounter++] = detail*(i+1) + j+1;*/
                inds.push_back(Tuple3d(detail*i + j, detail*(i+1) + j, detail*(i+1) + j+1));
                
                
                /*indices[indicesCounter++] = detail*i + j;
                 indices[indicesCounter++] = detail*(i+1) + j+1;
                 indices[indicesCounter++] = detail*i + j+1;*/
                inds.push_back(Tuple3d(detail*i + j, detail*(i+1) + j+1, detail*i + j+1));
            } else {
                /* indices[indicesCounter++] = detail*i + j;
                 indices[indicesCounter++] = detail*(i+1) + j;
                 indices[indicesCounter++] = detail*(i+1);*/
                inds.push_back(Tuple3d(detail*i + j, detail*(i+1) + j, detail*(i+1)));
                
                /*indices[indicesCounter++] = detail*i + j;
                 indices[indicesCounter++] = detail*(i+1);
                 indices[indicesCounter++] = detail*i;*/
                inds.push_back(Tuple3d(detail*i + j, detail*(i+1), detail*i));
            }
            
        }
    }
    
}

void  ExtrudeObj::checkIntersection(){
    
}


void ExtrudeObj::displayPath(){
    for (int i=0; i<pathVertices.size(); i++){
        for ( int j=0; j<detail; j++){
            if(i==0 && j==0){
                glBegin(GL_POINTS);
                glPointSize(15);
                glColor3f(1, 1, 1);
                glVertex3f(verts[i*detail+j].x, verts[i*detail+j].y, verts[i*detail+j].z);
                glEnd();
                
            } else if(j==0){
                glBegin(GL_POINTS);
                
                glColor3f(1, 0, 0);
                glVertex3f(verts[i*detail+j].x, verts[i*detail+j].y, verts[i*detail+j].z);
                glEnd();
            } else {
                glBegin(GL_POINTS);
                // glPointSize(2);
                glColor3f(.3, .3, .3);
                glVertex3f(verts[i*detail+j].x, verts[i*detail+j].y, verts[i*detail+j].z);
                glEnd();
            }
            //glVertex3f(verts[i*detail+j].x, verts[i*detail+j].y, verts[i*detail+j].z);
        }
    }
    
}


void ExtrudeObj::setRadius(float radius){
    this->radius = radius;
}
float ExtrudeObj::getRadius(){
    return radius;
}

