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
    vertex.push_back(vec3(-0.5f, 0.5f,  0.0f));
    vertex.push_back(vec3(0.5f,  0.5f,  0.0f));

    vertex.push_back(vec3(0.5f,  0.5f,  0.0f));
    vertex.push_back(vec3(0.5f,  -0.5f,  0.0f));
    vertex.push_back(vec3(-0.5f,  -0.5f,  0.0f));

    colors.push_back(vec3(1.0f, 0.0f, 0.0f));
    colors.push_back(vec3(0.0f, 1.0f, 0.0f));
    colors.push_back(vec3(0.0f, 0.0f, 1.0f));
    
		colors.push_back(vec3(0.0f, 0.0f, 1.0f));
    colors.push_back(vec3(0.0f, 1.0f, 0.0f));
    colors.push_back(vec3(1.0f, 0.0f, 0.0f));

}

void Triangle::create()
{
    glGenVertexArrays(1, &vao1);
    glGenBuffers(1, &vbo1);
    glGenBuffers(1, &cbo1);

    glGenVertexArrays(1, &vao2);
    glGenBuffers(1, &vbo2);
    glGenBuffers(1, &cbo2);

    init();

    glBindBuffer(GL_ARRAY_BUFFER, vbo1);
    glBufferData(GL_ARRAY_BUFFER, (vertex.size()*sizeof(vec3))/2, &vertex[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vbo2);
    glBufferData(GL_ARRAY_BUFFER, (vertex.size()*sizeof(vec3))/2, &vertex[3], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, cbo1);
    glBufferData(GL_ARRAY_BUFFER, (colors.size()*sizeof(vec3))/2, &colors[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, cbo2);
    glBufferData(GL_ARRAY_BUFFER, (colors.size()*sizeof(vec3))/2, &colors[3], GL_STATIC_DRAW);

    glBindVertexArray(vao1);
    glBindVertexArray(vao2);
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

    glBindBuffer(GL_ARRAY_BUFFER, vbo1);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, vbo2);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, cbo1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, cbo2);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
}

void Triangle::draw()
{
    glBindVertexArray(vao1);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindVertexArray(vao2);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Triangle::shutdown()
{
    glDeleteBuffers(1, &vbo1);
    glDeleteBuffers(1, &cbo1);
    glDeleteVertexArrays(1, &vao1);

    glDeleteBuffers(1, &vbo2);
    glDeleteBuffers(1, &cbo2);
    glDeleteVertexArrays(1, &vao2);
}

