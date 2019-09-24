/* 
 * File:   Triangle.h
 * Author: ulises
 *
 * Created on 27 de agosto de 2019, 10:20
 */

#ifndef SQUARE_H
#define SQUARE_H

#include <iostream>
#include <vector>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <GL/glew.h>
#include "Triangle.h"

using namespace std;
using namespace glm;

class Square
{
    public:
        Square();
        ~Square();

        void startup();
        void shutdown();
        void draw();

    private:
        Triangle t1;
        Triangle t2;

};


#endif /* TRIANGLE_H */

