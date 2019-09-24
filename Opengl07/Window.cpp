/* 
 * File:   Window.cpp
 * Author: ulises
 * 
 * Created on 27 de agosto de 2019, 10:17
 */

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/transform.hpp>
#include "Window.h"

Window::Window()
{
    //ctor
}

Window::~Window()
{
    //dtor
}


void Window::initGLEW()
{
    glewExperimental = GL_TRUE;
    glewInit();
}


void Window::initGLFW()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    window = glfwCreateWindow(window_w, window_h, title.c_str(), nullptr, nullptr);

    if(!window)
    {
        cout<<"Failed to crate GLFW window"<<endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
}

void Window::startup(string title)
{
    this->title = title;
    initGLFW();
    initGLEW();

    program.startup();
    vector<vec3> v, c;
    vector<GLuint> i;
    
    geom.startup("torus.obj");
}

void Window::startup(string title, string pathShaderV, string pathShaderF,
             string pathObj)
{
    this->title = title;
    initGLFW();
    initGLEW();
    program.startup(pathShaderV,pathShaderF);
    vector<vec3> v, c;
    vector<GLuint> i;
    
    geom.startup(pathObj);
}

void Window::shutdown()
{
    //triangle.shutdown();
		geom.shutdown();
    program.shutdown();
    glfwTerminate();
}

void Window::run()
{
	mat3 view3;
  glEnable(GL_DEPTH_TEST);
  model = mat4(1.0);
  view = glm::lookAt(vec3 (4,3,-3),
		     vec3 (0,0,0),
		     vec3 (0,1.0f,0));
	view3 = mat3(view);
  normalMatrix = glm::inverse(glm::transpose(mat3(view3)));

  projection = glm::perspective(45.0f, 4.0f/3.0f, 0.1f, 100.0f);
  //projection = mat4(1.0);

    do{
        glClearColor(0.3f, 0.5f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
        program.use();

	MVP = projection*view*model;
	GLint loc = glGetUniformLocation(program.getId(), "MVP");
	glUniformMatrix4fv(loc, 1 , GL_FALSE, &MVP[0][0]);

	GLint loc1 = glGetUniformLocation(program.getId(), "NM");
	glUniformMatrix3fv(loc1, 1 , GL_FALSE, &normalMatrix[0][0]);

	GLint loc2 = glGetUniformLocation(program.getId(), "kd");
	glUniform3f(loc2, 0.9f, 0.5f, 0.3f);

	GLint loc3 = glGetUniformLocation(program.getId(), "ld");
	glUniform3f(loc3, 1.f, 1.f, 1.f);

	loc2 = glGetUniformLocation(program.getId(), "ka");
	glUniform3f(loc2, 0.9f, 0.5f, 0.3f);

	loc3 = glGetUniformLocation(program.getId(), "la");
	glUniform3f(loc3, 0.4f, 0.4f, 0.4f);

	loc2 = glGetUniformLocation(program.getId(), "ks");
	glUniform3f(loc2, 0.8f, 0.8f, 0.8f);

	loc3 = glGetUniformLocation(program.getId(), "ls");
	glUniform3f(loc3, 1.f, 1.f, 1.f);

	loc3 = glGetUniformLocation(program.getId(), "shininess");
	glUniform1f(loc3, 100.f);

	GLint loc4 = glGetUniformLocation(program.getId(), "MV");
	glUniformMatrix4fv(loc4, 1 , GL_FALSE, &view[0][0]);

	GLint loc5 = glGetUniformLocation(program.getId(), "lightpos");
	glUniform4f(loc5, 5.f, 5.f, 5.f, 1.f);
	
        geom.draw();
        glfwSwapBuffers(window);
        glfwPollEvents();
    } while(!glfwWindowShouldClose(window));
    shutdown();
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(action== GLFW_PRESS)
    {
        switch(key)
        {
            case GLFW_KEY_ESCAPE:
                glfwSetWindowShouldClose(window, GL_TRUE);
                break;
        }
    }
}

