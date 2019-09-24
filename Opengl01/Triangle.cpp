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


void Triangle::init()
{
    vertex.push_back(vec3(-0.5f, -0.5f,  0.0f));
    vertex.push_back(vec3(0.5f, -0.5f,  0.0f));
    vertex.push_back(vec3(0.0f,  0.5f,  0.0f));

    colors.push_back(vec3(1.0f, 0.0f, 0.0f));
    colors.push_back(vec3(0.0f, 1.0f, 0.0f));
    colors.push_back(vec3(0.0f, 0.0f, 1.0f));

}

void Triangle::create()
{
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &cbo);

    init();

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertex.size()*sizeof(vec3), &vertex[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, cbo);
    glBufferData(GL_ARRAY_BUFFER, colors.size()*sizeof(vec3), &colors[0], GL_STATIC_DRAW);

    glBindVertexArray(vao);
}

void Triangle::startup()
{
    create();
    bindData();
}

void Triangle::bindData()
{
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, cbo);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
}

void Triangle::draw()
{
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Triangle::shutdown()
{
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &cbo);
    glDeleteVertexArrays(1, &vao);
}

