/* 
 * File:   ProgramShader.cpp
 * Author: ulises
 * 
 * Created on 27 de agosto de 2019, 10:18
 */

#include "ProgramShader.h"

ProgramShader::ProgramShader()
{
    //ctor
}

ProgramShader::~ProgramShader()
{
    //dtor
}
void ProgramShader::startup()
{
    cout<<"startup ProgramShader"<<endl;
    addShader("vertex.glsl", GL_VERTEX_SHADER);
    addShader("fragment.glsl", GL_FRAGMENT_SHADER);
    link();
}

void ProgramShader::startup(string pathShaderV, string pathShaderF)
{
    cout<<"startup ProgramShader"<<endl;
    addShader(pathShaderV, GL_VERTEX_SHADER);
    addShader(pathShaderF, GL_FRAGMENT_SHADER);
    link();
}

GLuint ProgramShader::compileShader(const string& source, GLenum type) throw()
{
    GLuint shader = glCreateShader(type);

    if(!shader)
    {
        throw ShaderException("Error al crear el shader");
    }

    const GLchar *sourceptr = source.c_str();
    glShaderSource(shader,1, &sourceptr, nullptr);
    glCompileShader(shader);

    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

    if(status== GL_FALSE)
    {
        GLint leng;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &leng);
        GLchar *info = new GLchar[leng];
        GLint written =0;
        glGetShaderInfoLog(shader, leng, &written, info);
        string infolog = info;
        delete[] info;
        throw ShaderException(infolog);
    }
    return shader;
}

void ProgramShader::link() throw()
{
    program = glCreateProgram();

    if(!program)
    {
        throw ShaderException("Error al crear el ProgramShader glsl");
    }

    for(map<GLenum, GLuint>::iterator it = shaders.begin(); it!=shaders.end(); it++)
    {
        glAttachShader(program, it->second);
    }
    glLinkProgram(program);

    GLint status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);

    if(status== GL_FALSE)
    {
        GLint leng;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &leng);
        GLchar* info = new GLchar[leng];
        GLint written = 0;
        glGetProgramInfoLog(program, leng, &written, info);
        string infolog = info;
        delete[] info;
        throw ShaderException(infolog);
    }

}

void ProgramShader::use() throw()
{
    glUseProgram(program);
}

void ProgramShader::addShader(const string& file, GLenum type)
{
    string source = readFile(file);
    shaders[type] = compileShader(source, type);
}

void ProgramShader::removeShader(GLenum type, GLuint shader)
{
    glDeleteShader(shader);
    shaders.erase(type);
}

void ProgramShader::removeProgram()
{
    glDeleteProgram(program);
}


void ProgramShader::shutdown()
{
    for(std::map<GLenum, GLuint>::iterator it = shaders.begin(); it != shaders.end(); it++)
    {
        glDetachShader(program, it->second);
        removeShader(it->first, it->second);
    }
    glDeleteProgram(program);
}

string ProgramShader::readFile(string path)
{
    ifstream file;
    file.exceptions(ifstream::badbit|ifstream::failbit);
    stringstream filestream;
    string source;

    try
    {
        file.open(path.c_str());

        filestream<<file.rdbuf();

        file.close();

        source = filestream.str();
    }catch(ifstream::failure &e)
    {
        cout<<"ERROR::SHADER: FILE NOT SUCCESSFULLY READ"<<endl;
    }
    return source;
}
