
/* 
 * File:   Geometry.h
 * Author: ulises
 *
 * Created on 27 de agosto de 2019, 10:20
 */

#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <iostream>
#include <vector>
#include <string>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <GL/glew.h>
#include "Texture.h"

using namespace std;
using namespace glm;

class VertexInfo{
public:
  vector<vec3> vertices;    
  vector<vec3> normals;
  vector<vec2> texCoords;
  vector<vec4> tangents;
  vector<GLuint> indices;
  
  void align(VertexInfo &other, vector<GLuint> vidx, vector<GLuint> nidx, vector<GLuint> tcidx);
  void indexing(VertexInfo &other);
  bool isSimilar(vec3 v, vec3 n, vec2 tc, vec3 v1, vec3 n1, vec2 tc1);
  void genTangents();
};

class GlInfo{
public:
    GLuint vao;
    GLuint vbo;
    GLuint nbo;
    GLuint tbo;
    GLuint tgbo;
    GLuint ebo;
};

class Geometry
{
public:
    Geometry();
    virtual ~Geometry();

    void startup(vector<vec3> v, vector<vec3>c, vector<GLuint> index);
	void startup(string a, string b);
	void startup(string pathObj, const vector<string> &textures);
	void shutdown();
    void draw();

private:
    GlInfo gl;
    VertexInfo info;
    Texture texture;
    void create(string pathTex);
    void create(const vector<string> &textures);
    void bindData();
	void readObj(string path);
    
};
#endif/* GEOMETRY_H */

