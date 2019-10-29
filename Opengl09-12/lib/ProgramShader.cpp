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
    addShader("vertex.glsl", GL_VERTEX_SHADER);
    addShader("fragment.glsl", GL_FRAGMENT_SHADER);
    link();
}

void ProgramShader::startup(string pathShaderV, string pathShaderF)
{    
    addShader(pathShaderV, GL_VERTEX_SHADER);
    addShader(pathShaderF, GL_FRAGMENT_SHADER);
    link();
}

void ProgramShader::startup(vector<string> shaderFiles) {
    GLenum types[] = {GL_VERTEX_SHADER, GL_FRAGMENT_SHADER, GL_GEOMETRY_SHADER, 
                      GL_COMPUTE_SHADER,GL_TESS_EVALUATION_SHADER, GL_TESS_CONTROL_SHADER};
    
    for(GLuint i = 0; i < shaderFiles.size(); i++){
		//cout<<"abriendo "<< shaderFiles[i]<<endl;
        addShader(shaderFiles[i], types[i]);
    }    
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

void ProgramShader::addUniform(const string& name){
    uniforms[name]= glGetUniformLocation(program, name.c_str());
}

void ProgramShader::setUniform(const string &name, float x, float y, float z) {
    glUniform3f(uniforms[name], x, y, z);
}

void ProgramShader::setUniform(const string &name, const glm::vec2 &v) {
    glUniform2f(uniforms[name], v.x, v.y);
}

void ProgramShader::setUniform(const string &name, const glm::vec3 &v) {
    glUniform3f(uniforms[name], v.x, v.y, v.z);
}

void ProgramShader::setUniform(const string &name, const glm::vec4 &v) {
    glUniform4f(uniforms[name], v.x, v.y, v.z, v.w);
}

void ProgramShader::setUniform(const string &name, const glm::mat4 &m) {
    glUniformMatrix4fv(uniforms[name], 1, GL_FALSE, &m[0][0]);
}

void ProgramShader::setUniform(const string &name, const glm::mat3 &m) {
    glUniformMatrix3fv(uniforms[name],1, GL_FALSE, &m[0][0]);
}

void ProgramShader::setUniform(const string &name, float val) {
    glUniform1f(uniforms[name], val);
}

void ProgramShader::setUniform(const string &name, int val) {
    glUniform1i(uniforms[name], val);
}

void ProgramShader::setUniform(const string &name, bool val) {
    glUniform1i(uniforms[name], val);
}

void ProgramShader::setUniform(const string &name, GLuint val) {
    glUniform1ui(uniforms[name], val);
}

void ProgramShader::addAttrib(const string &name){
    attribs[name] = glGetAttribLocation(program, name.c_str());
}
