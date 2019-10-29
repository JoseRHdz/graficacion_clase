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
#include <vector>

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
    void startup(vector<string> shadersFiles);
    
    void use() throw();
    void addShader(const string& file, GLenum type);
    void removeShader(GLenum type, GLuint shader);
    void removeProgram();
    void shutdown();    
    GLuint getId() {return program;}
    
    void addUniform(const string &name);
    void setUniform(const string &name, float x, float y, float z);
    void setUniform(const string &name, const vec2 &v);
    void setUniform(const string &name, const vec3 &v);
    void setUniform(const string &name, const vec4 &v);
    void setUniform(const string &name, const mat4 &m);
    void setUniform(const string &name, const mat3 &m);
    void setUniform(const string &name, float val);
    void setUniform(const string &name, int val);
    void setUniform(const string &name, bool val);
    void setUniform(const string &name, GLuint val);     
    void addAttrib(const string &name);
    
private:
    GLuint compileShader(const string& source, GLenum type) throw();
    void link() throw();
    string readFile(string path);

private:
    GLuint program;
    map<GLenum, GLuint> shaders;
    map<string, GLuint> uniforms;
    map<string, GLuint> attribs;
};

#endif /* PROGRAMSHADER_H */

