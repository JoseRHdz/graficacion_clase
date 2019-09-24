/* 
 * File:   Triangle.h
 * Author: ulises
 *
 * Created on 27 de agosto de 2019, 10:20
 */

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <iostream>
#include <vector>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <GL/glew.h>

using namespace std;
using namespace glm;

class Triangle
{
    public:
        Triangle();
        virtual ~Triangle();

        void startup();
        void shutdown();
        void draw();

    private:
        GLuint vao;
        GLuint vbo;
        GLuint cbo;

        vector<vec3> vertex;
        vector<vec3> colors;

        void init();
        void create();
        void bindData();
};


#endif /* TRIANGLE_H */

