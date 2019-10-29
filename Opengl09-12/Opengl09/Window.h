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

struct Matrix{
    mat4 model;
    mat4 view;
    mat4 projection;
    mat3 normal;
    mat4 MVP;
};

class Window
{
    public:
        Window();
        virtual ~Window();
        void run();
        void startup(string title);
        void startup(string title, string pathShaderV, string pathShader, string pathObj, string pathTex);

        void shutdown();

    private:
        void initGLEW();
        void initGLFW();
        GLFWwindow *window;
        string title;
		Matrix matrix;
        ProgramShader program;
        Geometry geom;
};

#endif // WINDOW_H
