/* 
 * File:   Geometry.cpp
 * Author: ulises
 * 
 * Created on 27 de agosto de 2019, 10:20
 */

#include "Geometry.h"
#include <fstream>
#include <sstream>

Geometry::Geometry()
{
    //ctor
}

Geometry::~Geometry()
{
    //dtor
}


void Geometry::create()
{
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &cbo);
    glGenBuffers(1, &ebo);
    glGenBuffers(1, &tbo);
    glGenBuffers(1, &nbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, ver.vertices.size()*sizeof(vec3), &ver.vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, cbo);
    glBufferData(GL_ARRAY_BUFFER, ver.colors.size()*sizeof(vec3), &ver.colors[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, ver.indices.size()*sizeof(GLuint), &ver.indices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, tbo);
    glBufferData(GL_ARRAY_BUFFER, ver.texCoords.size()*sizeof(vec2), &ver.texCoords[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, nbo);
    glBufferData(GL_ARRAY_BUFFER, ver.normals.size()*sizeof(vec3), &ver.normals[0], GL_STATIC_DRAW);

    glBindVertexArray(vao);
}

void Geometry::startup(vector<vec3> v, vector<vec3> c, vector<GLuint> i)
{
  ver.vertices = v;
  ver.colors = c;
  ver.indices=i;
  create();
  bindData();
}

void Geometry::startup(string s){
  readObj(s);
  create();
  bindData();
}

void Geometry::bindData()
{
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, nbo);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
}

void Geometry::draw()
{
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, ver.indices.size(),GL_UNSIGNED_INT, nullptr);

}

void Geometry::shutdown()
{
  glDeleteBuffers(1, &tbo);
  glDeleteBuffers(1, &nbo);
  glDeleteBuffers(1, &vbo);
  glDeleteBuffers(1, &cbo);
  glDeleteBuffers(1, &ebo);
  glDeleteVertexArrays(1, &vao);

}

void Geometry::readObj(string path){
  fstream file;
  file.open(path.c_str());
  if(file.is_open()){
    string linea;
    stringstream slinea;
    while(!file.eof()){
      getline(file, linea);
      slinea = stringstream(linea);
      string head;
      slinea>>head;
      if(head == "v"){
	vec3 vertex;
	slinea>>vertex.x;
	slinea>>vertex.y;
	slinea>>vertex.z;
	ver.vertices.push_back(vertex);
      }else if(head == "vn"){
	vec3 normal;
	slinea>>normal.x;
	slinea>>normal.y;
	slinea>>normal.z;
	ver.normals.push_back(normal);
      }else if(head == "vt"){
	vec2 tex;
	slinea>>tex.x;
	slinea>>tex.y;
	ver.texCoords.push_back(tex);
      }else if(head == "f"){
	string tok;
	for(int i = 0; i < 3; i++){
	  slinea>>head;
	  stringstream data(head);
	  //for(int j = 0; j < 3; j++){
	    getline(data, tok, '/');
	    ver.indices.push_back(stoi(tok)-1);
	    //}
	}
      }
    }
  }
}
