/* 
 * File:   Triangle.cpp
 * Author: ulises
 * 
 * Created on 27 de agosto de 2019, 10:20
 */

#include "Triangle.h"

Triangle::Triangle()
{
    //ctor
}

Triangle::~Triangle()
{
    //dtor
}


void Triangle::create()
{
    glGenVertexArrays(1, &vao1);
    glGenBuffers(1, &vbo1);
    glGenBuffers(1, &cbo1);

    glBindBuffer(GL_ARRAY_BUFFER, vbo1);
    glBufferData(GL_ARRAY_BUFFER, vertex.size()*sizeof(vec3), &vertex[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, cbo1);
    glBufferData(GL_ARRAY_BUFFER, colors.size()*sizeof(vec3), &colors[0], GL_STATIC_DRAW);

    glBindVertexArray(vao1);
}

void Triangle::startup(vector<vec3> v, vector<vec3> c)
{
		vertex = v;
		colors = c;
    create();
    bindData();
}

void Triangle::bindData()
{
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, vbo1);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, cbo1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
}

void Triangle::draw()
{
    glBindVertexArray(vao1);
    glDrawArrays(GL_TRIANGLES, 0, vertex.size());

}

void Triangle::shutdown()
{
    glDeleteBuffers(1, &vbo1);
    glDeleteBuffers(1, &cbo1);
    glDeleteVertexArrays(1, &vao1);

}
