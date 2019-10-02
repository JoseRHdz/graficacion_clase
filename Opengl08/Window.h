#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>

#define GLEW_STATIC
using namespace std;

#include "../lib/ProgramShader.h"
#include "Geometry.h"


// Constantes de tamaño de la ventana
const GLuint window_w=800, window_h = 800;

// Función para procesar los eventos del teclado
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

class Window
{
    public:
        Window();
        virtual ~Window();
        void run();
        void startup(string title);
        void startup(string title, string pathShaderV, string pathShader, 
										 string pathObj);

        void shutdown();

    private:
        void initGLEW();
        void initGLFW();
        GLFWwindow *window;
        string title;
				mat4 model, view, projection;
				mat4 MVP;
				mat3 normalMatrix;
        ProgramShader program;
				Geometry geom;

};

#endif // WINDOW_H
