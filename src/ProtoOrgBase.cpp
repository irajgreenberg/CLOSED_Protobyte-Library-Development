//
//  ProtoOrgBase.cpp
//  Protobyte_iig001
//
//  Created by Ira on 9/5/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "ProtoOrgBase.h"



namespace ijg {
    
    std::ostream& operator<<(std::ostream& output, const ProtoOrgBase& protoBase)
    {
        output << "ProtoOrgBase obj: [ loc = "<<protoBase.loc<<" dim = "<<protoBase.dim<<" ]";
        return output;
    }
}

using namespace ijg;

ProtoOrgBase::ProtoOrgBase()
{
    //init();
}

ProtoOrgBase::ProtoOrgBase(const ofVec3f& loc, const Dimension3D& dim):
loc(loc), dim(dim)
{
    //init();
}

/*ProtoOrgBase::ProtoOrgBase(const ofVec3f& loc, const Dimension3D& dim, const ofColor& colr): // cster
loc(loc), dim(dim){
    
    
}*/

/*ProtoOrgBase::ProtoOrgBase(const ofVec3f& loc, const Dimension3D& dim, std::vector<ofColor> colrs): // cster
loc(loc), dim(dim), {
    
}*/

ProtoOrgBase::~ProtoOrgBase()
{
    
}

void ProtoOrgBase::clearAll()
{
    if(verts.size()>0){
        verts.clear();
    }
    if(inds.size()>0){
        inds.clear();
    }
    if(faces.size()>0){
        faces.clear();
    }
    if(norms.size()>0){
        norms.clear();
    }
    if(vertices.size()>0){
        vertices.clear();
    }
    if(indices.size()>0){
        indices.clear();
    }
    if(normals.size()>0){
        normals.clear();
    }
}

void ProtoOrgBase::init()
{
    /*clearAll();
     calcVerts();
     calcNorms();
     calcPrimitives();*/
    
    clearAll(); // ensure vectors are cleaned
    calcVerts();
    calcInds();
    calcFaces();
    calcNorms();
    calcPrimitives();
}

void ProtoOrgBase::calcVerts()
{
    // verts
    float theta = 0;
    for (int i=0; i<3; i++){
        verts.push_back(ofVec3f(cos(theta), sin(theta)));
        theta += PI*2/3;
        
    }
    // inds
    inds.push_back(Tuple3i(0, 1, 2));
    faces.push_back(Face3D(&verts[0], &verts[1], &verts[2]));
}

void ProtoOrgBase::calcInds()
{
}

void ProtoOrgBase::calcNorms()
{
    // get face normals
    for ( int i=0; i<faces.size(); i++){
        //norms.push_back(ofVec3f(faces[i].getNormal()));
    }
    
    // vertex normals
    for (int i=0; i<verts.size(); i++){
        ofVec3f temp;
        for (int j=0; j<faces.size(); j++){
            if(&verts[i] == faces[j].p_vecs[0]|| &verts[i] == faces[j].p_vecs[1] || &verts[i] == faces[j].p_vecs[2]){
                // std::cout << "in normals loop" << std::endl;
                temp += faces[j].getNormal();
            }
        }
        temp.normalize();
        norms.push_back(temp);
    }
}

void ProtoOrgBase::calcFaces()
{
    // calc faces
    for(int i=0; i<inds.size(); i++){
        faces.push_back( Face3D(&verts[inds[i].elem0], &verts[inds[i].elem1], &verts[inds[i].elem2]) );
        //std::cout<<"inds["<<i<<"].elem0 = " <<inds[i].elem0 <<std::endl;
        //std::cout<<"inds["<<i<<"].elem1 = " <<inds[i].elem1 <<std::endl;
        //std::cout<<"inds["<<i<<"].elem2 = " <<inds[i].elem2 <<std::endl;
    }
    
}

void ProtoOrgBase::calcPrimitives()
{
    // vertices
    for (int i=0; i<verts.size(); i++){
        vertices.push_back(verts[i].x);
        vertices.push_back(verts[i].y);
        vertices.push_back(verts[i].z);
        //std::cout << "verts =  " << verts[i] << std::endl;
    }
    // indices
    for (int i=0; i<inds.size(); i++){
        indices.push_back(inds[i].elem0);
        indices.push_back(inds[i].elem1);
        indices.push_back(inds[i].elem2);
    }
    
    // normals
    for (int i=0; i<norms.size(); i++){
        normals.push_back(norms[i].x);
        normals.push_back(norms[i].y);
        normals.push_back(norms[i].z);
    }
    
    // colors
    for (int i=0; i<verts.size(); i++){
//         colors.push_back(ofRandom(1.0));
//         colors.push_back(ofRandom(1.0));
//         colors.push_back(ofRandom(1.0));
//         colors.push_back(1.0);
        colors.push_back(.7);
        colors.push_back(.7);
        colors.push_back(.7);
        colors.push_back(1);
    }
    
    
}

void ProtoOrgBase::display()
{
    
    //std::cout << vertices.size()-1 << std::endl;
    //quickFaceSort(indices, vertices, normals, 0, vertices.size()-1);
    // sort face front to back
    
    //std::cout << "indices.size() = " << indices.size() << std::endl;
    
    glEnableClientState (GL_VERTEX_ARRAY);
	//glEnableClientState (GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
	
	//bind the ground texture
	//glBindTexture(GL_TEXTURE_2D, gltexture);
    
	//this is a pointer to the texture coords in the vertices array
	//char *evilPointer = (char *)vertexlist;
	//evilPointer+=sizeof(GL_FLOAT)*3;
	
	//set the pointers
    
    glColorPointer(4, GL_FLOAT, 0, &colors[0]);
    
	//glTexCoordPointer(2,GL_FLOAT,sizeof(GL_FLOAT) * 5,evilPointer);
	glVertexPointer (3, GL_FLOAT, 0, &vertices[0]);
	glNormalPointer(GL_FLOAT, 0, &normals[0]);
	
	glPushMatrix();
    glTranslatef(loc.x, loc.y, loc.z);
    glScalef(dim.w, dim.h, dim.d);
    //Draw Protobyte
	glDrawElements (GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, &indices[0]);
    glPopMatrix();
	
	//disable the client state and texture
	//glDisable(GL_TEXTURE_2D);
	glDisableClientState(GL_NORMAL_ARRAY);
	//glDisableClientState (GL_TEXTURE_COORD_ARRAY);
	glDisableClientState (GL_VERTEX_ARRAY);
    
}

// not really working
void ProtoOrgBase::quickFaceSort(vector <GLint>indices, vector <GLfloat>vertices,
                                 vector <GLfloat>normals, int left, int right)
{
    int i = left, j = right;
    
    GLfloat iTmpX, iTmpY, iTmpZ,
    vTmpX, vTmpY, vTmpZ,
    nTmpX, nTmpY, nTmpZ;
    
    int sub;
    
    if ( (left+right)/2 < 4){
        sub = 2;
    } else {
        
        if ( (left+right)/2 % 3 == 2 ){
            sub = (left+right)/2 % 3 ;
        } else if ( (left+right)/2 % 3 == 1 ){
            sub = (left+right)/2 % 3 + 1;
        } else if ( (left+right)/2 % 3 == 0 ){
            sub = (left+right)/2 % 3 + 2;
        }
    }
    
    
    
    int pivot = vertices[sub];
    
    
    // partition
    
    while (i <= j) {
        
        while (vertices[i] < pivot)
            
            i+=3;
        
        while (vertices[j] > pivot)
            
            j-=3;
        
        if (i <= j) {
            
            iTmpX = indices[i-2];
            iTmpY = indices[i-1];
            iTmpZ = indices[i];
            
            vTmpX = vertices[i-2];
            vTmpY = vertices[i-1];
            vTmpZ = vertices[i];
            
            nTmpX = normals[i-2];
            nTmpY = normals[i-1];
            nTmpZ = normals[i];
            
            indices[i] = indices[j];
            indices[i-1] = indices[j-1];
            indices[i-2] = indices[j-2];
            
            vertices[i] = vertices[j];
            vertices[i-1] = vertices[j-1];
            vertices[i-2] = vertices[j-2];
            
            normals[i] = normals[j];
            normals[i-1] = normals[j-1];
            normals[i-2] = normals[j-2];
            
            indices[j-2] = iTmpX;
            indices[j-1] = iTmpY;
            indices[j] = iTmpZ;
            
            normals[j-2] = nTmpX;
            normals[j-1] = nTmpY;
            normals[j] = nTmpZ;
            
            i+=3;
            
            j-=3;
            
        }
        
    }
    
    
    
    // recursion
    
    if (left < j) {
        
        //if (left >2 && j>2)
        // quickFaceSort(indices, vertices, normals, left, j);
    }
    
    if (i < right) {
        
        //quickFaceSort(indices, vertices, normals, i, right);
    }
    
}


void  ProtoOrgBase::displayNormals()
{
    for(int i=0; i<faces.size(); i++){
        faces[i].displayNormal();
    }
    
}

void ProtoOrgBase::move()
{
    
}

void ProtoOrgBase::exportSTL()
{
    if(mkdir("../exportData",0777)==-1)//creating a directory
    {
        //std::cout << "STL file Successfully Written" << std::endl;
        cerr<<"Error :  "<<strerror(errno)<<endl;
        //exit(1);
    }
    std::ofstream myfile;
    myfile.open ("../exportData/geomData.STL");
    
    myfile << "solid PROTOBYTE\n";
    for(int i=0; i<faces.size(); i++){
        myfile <<  scientific << setprecision (7) <<"\tfacet normal " <<
        faces[i].getNormal().x << " "<<faces[i].getNormal().y << " "<<faces[i].getNormal().z << "\n"<<
        "\t\touter loop\n"<<
        "\t\t\tvertex " << faces[i].p_vecs[0]->x << " "<<faces[i].p_vecs[0]->y << " "<<faces[i].p_vecs[0]->z << "\n"<<
        "\t\t\tvertex " << faces[i].p_vecs[1]->x << " "<<faces[i].p_vecs[1]->y << " "<<faces[i].p_vecs[1]->z << "\n"<<
        "\t\t\tvertex " << faces[i].p_vecs[2]->x << " "<<faces[i].p_vecs[2]->y << " "<<faces[i].p_vecs[2]->z << "\n"<<
        "\t\tendloop\n" <<
        "\tendfacet\n";
    }
    myfile << "endsolid PROTOBYTE\n";
    
    myfile.close();
    std::cout << "STL file Successfully Written" << std::endl;
}











