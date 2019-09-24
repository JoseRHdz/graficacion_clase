
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

using namespace std;
using namespace glm;

struct vertexInfo{
  vector<vec3> vertices;
  vector<vec3> colors;
  vector<GLuint> indices;
  vector<vec3> normals;
  vector<vec2> texCoords;
};

class Geometry
{
    public:
        Geometry();
        virtual ~Geometry();

        void startup(vector<vec3> v, vector<vec3>c, vector<GLuint> index);
				void startup(string a);
				void shutdown();
        void draw();

    private:
        GLuint vao;
        GLuint vbo;
        GLuint cbo;
        GLuint ebo;
				GLuint nbo;
				GLuint tbo;
				vertexInfo ver;
        void create();
        void bindData();
				void readObj(string path);
};




#endif /* GEOMETRY_H */

