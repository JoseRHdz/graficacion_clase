/* 
 * File:   Square.cpp
 * Author: ulises
 * 
 * Created on 27 de agosto de 2019, 10:20
 */

#include "Square.h"

Square::Square()
{
    //ctor
}

Square::~Square()
{
    //dtor
}


void Square::create()
{
    glGenVertexArrays(1, &vao1);
    glGenBuffers(1, &vbo1);
    glGenBuffers(1, &cbo1);

		glGenBuffers(1,&ebo1);

    glBindBuffer(GL_ARRAY_BUFFER, vbo1);
    glBufferData(GL_ARRAY_BUFFER, vertex.size()*sizeof(vec3), &vertex[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, cbo1);
    glBufferData(GL_ARRAY_BUFFER, colors.size()*sizeof(vec3), &colors[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo1);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, index.size()*sizeof(GLuint), &index[0], GL_STATIC_DRAW);

    glBindVertexArray(vao1);
}

void Square::startup(vector<vec3> v, vector<vec3> c, vector<GLuint> i)
{
		vertex = v;
		colors = c;
		index=i;
    create();
    bindData();
}

void Square::bindData()
{
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, vbo1);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, cbo1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo1);
}

void Square::draw()
{
    glBindVertexArray(vao1);
    glDrawElements(GL_TRIANGLES, index.size(),GL_UNSIGNED_INT, nullptr);

}

void Square::shutdown()
{
    glDeleteBuffers(1, &vbo1);
    glDeleteBuffers(1, &cbo1);
    glDeleteBuffers(1, &ebo1);
    glDeleteVertexArrays(1, &vao1);

}
