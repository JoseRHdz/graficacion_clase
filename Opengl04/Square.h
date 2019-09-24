
/* 
 * File:   Square.h
 * Author: ulises
 *
 * Created on 27 de agosto de 2019, 10:20
 */

#ifndef SQUARE2_H
#define SQUARE2_H

#include <iostream>
#include <vector>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <GL/glew.h>

using namespace std;
using namespace glm;

class Square
{
    public:
        Square();
        virtual ~Square();

        void startup(vector<vec3> v, vector<vec3>c, vector<GLuint> index);
        void shutdown();
        void draw();

    private:
        GLuint vao1;
        GLuint vbo1;
        GLuint cbo1;
        GLuint ebo1;

        vector<vec3> vertex;
        vector<vec3> colors;
        vector<GLuint> index;

        //void init();
        void create();
        void bindData();
};


#endif /* TRIANGLE_H */

