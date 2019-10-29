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
    geom.startup("torus.obj", "tex.jpg");
}

void Window::startup(string title, string pathObj, const vector<string> &shaders, const vector<string> &textures)
{
    this->title = title;
    initGLFW();
    initGLEW();    
    program.startup(shaders);
    loader.startup(pathObj, &geom); 
    cout<<"se cargo geo"<<endl;
    geom.startup(textures);
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
    glEnable(GL_DEPTH_TEST);
    matrix.model = mat4(1.0);
    //matrix.model = rotate(matrix.model, 90.0f, vec3(0.0f, 0.0f, 1.0f));
    //matrix.model = rotate(matrix.model, -30.0f, vec3(1.0f, 1.0f, 0.0f));
    //matrix.model = scale(matrix.model, vec3(0.7f));
    mat4 mv = matrix.view * matrix.model;
    matrix.view = glm::lookAt(vec3 (3,3,-4),
                       vec3 (0,0,0),
                       vec3 (0,1.0f,0));    
    matrix.normal = mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2]));
    matrix.projection = glm::perspective(45.0f, 4.0f/3.0f, 0.1f, 100.0f);
    //projection = mat4(1.0);
    matrix.MVP = matrix.projection*matrix.view*matrix.model;
    program.addUniform("MVP");
    program.addUniform("NM");
    program.addUniform("MV");
    program.addUniform("L");
    program.addUniform("La");    
    program.addUniform("Ks");
    program.addUniform("shininess");
    program.addUniform("colorTex");
    program.addUniform("normalTex");
    program.addUniform("heightTex");
    program.addUniform("LightPos");
    vec4 lightPos = vec4(2,2,4,1);
    mat4 transform = mat4(1.0);
    transform = rotate(transform, radians(1.0f), vec3(0.0f, 1.0f, 0.0f));
    
    do{
        glClearColor(0.3f, 0.5f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
        program.use();
        
        program.setUniform("MVP", matrix.MVP);
        program.setUniform("NM", matrix.normal); 
        program.setUniform("MV", mv);        
        
        lightPos = transform *lightPos;
        
        program.setUniform("LightPos",mv*lightPos);
        program.setUniform("L", vec3(1.0f));
        program.setUniform("La", vec3(0.5f));
        program.setUniform("Ks", 0.05f, 0.05f, 0.05);
        program.setUniform("shininess", 1.0f);
        program.setUniform("colorTex",0);
        program.setUniform("normalTex",1);
        program.setUniform("heightTex",2);
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

