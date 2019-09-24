/* 
 * File:   main.cpp
 * Author: ulises
 *
 * Created on 27 de agosto de 2019, 10:17
 */

#include <cstdlib>
#include "Window.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    Window win;
    win.startup("Hello Triangle");
    win.run();
    return 0;
}

