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
    //triangle.startup();
		vector<vec3> v, c;
		vector<GLuint> i;

		//Plano xy
		v.push_back(vec3(-0.5f,-0.5f,0.5f));
		v.push_back(vec3(-0.5f,0.5f,0.5f));
		v.push_back(vec3(0.5f,0.5f,0.5f));
		v.push_back(vec3(0.5f,-0.5f,0.5f));

		//Plano xz
		v.push_back(vec3(-0.5f,-0.5f,-0.5f));
		v.push_back(vec3(-0.5f,0.5f,-0.5f));

		//Plano yz
		v.push_back(vec3(0.5f,0.5f,-0.5f));
		v.push_back(vec3(0.5f,-0.5f,-0.5f));

		c.push_back(vec3(0.0f,0.0f,0.0f));
		c.push_back(vec3(0.0f,1.0f,0.0f));
		c.push_back(vec3(0.0f,0.0f,0.0f));
		c.push_back(vec3(0.0f,1.0f,0.0f));
		c.push_back(vec3(0.0f,0.0f,0.0f));
		c.push_back(vec3(0.0f,1.0f,0.0f));
		c.push_back(vec3(0.0f,0.0f,0.0f));
		c.push_back(vec3(0.0f,1.0f,0.0f));

		//Cara inferior
		i.push_back(0);
		i.push_back(1);
		i.push_back(2);

		i.push_back(0);
		i.push_back(2);
		i.push_back(3);

		//Cara izquierda
		i.push_back(4);
		i.push_back(5);
		i.push_back(1);

		i.push_back(4);
		i.push_back(1);
		i.push_back(0);

		//Cara trasera
		i.push_back(4);
		i.push_back(5);
		i.push_back(6);

		i.push_back(4);
		i.push_back(6);
		i.push_back(7);

		//Cara derecha
		i.push_back(3);
		i.push_back(2);
		i.push_back(6);

		i.push_back(3);
		i.push_back(6);
		i.push_back(7);

		//Cara delantera
		i.push_back(0);
		i.push_back(4);
		i.push_back(7);

		i.push_back(0);
		i.push_back(7);
		i.push_back(3);

		//Cara superior
		i.push_back(1);
		i.push_back(5);
		i.push_back(6);

		i.push_back(1);
		i.push_back(6);
		i.push_back(2);

		sq.startup(v,c,i);
}

void Window::shutdown()
{
    //triangle.shutdown();
		sq.shutdown();
    program.shutdown();
    glfwTerminate();
}

void Window::run()
{
		glEnable(GL_DEPTH_TEST);
		model = mat4(1.0);
		view = glm::lookAt(vec3 (4,3,-3),
											 vec3 (0,0,0),
											 vec3 (0,1.0f,0));

		projection = glm::perspective(45.0f, 4.0f/3.0f, 0.1f, 100.0f);
		//projection = mat4(1.0);

    do{
        glClearColor(0.3f, 0.5f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
        program.use();

				MVP = projection*view*model;
				GLint loc = glGetUniformLocation(program.getId(), "MVP");
				glUniformMatrix4fv(loc, 1 , GL_FALSE, &MVP[0][0]);

        sq.draw();
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

