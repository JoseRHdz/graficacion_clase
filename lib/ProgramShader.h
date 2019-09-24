/* 
 * File:   ProgramShader.h
 * Author: ulises
 *
 * Created on 27 de agosto de 2019, 10:18
 */

#ifndef PROGRAMSHADER_H
#define PROGRAMSHADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

#include <GL/glew.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include "ShaderException.h"

using namespace std;
using namespace glm;


class ProgramShader
{
    public:
        ProgramShader();
        virtual ~ProgramShader();
        void startup();
        void startup(string pathShaderV, string pathShaderF);
        GLuint compileShader(const string& source, GLenum type) throw();
        void link() throw();
        void use() throw();
        void addShader(const string& file, GLenum type);
        void removeShader(GLenum type, GLuint shader);
        void removeProgram();
        void shutdown();
        string readFile(string path);
				GLuint getId() {return program;}

    private:
        GLuint program;
        map<GLenum, GLuint> shaders;
};


#endif /* PROGRAMSHADER_H */

