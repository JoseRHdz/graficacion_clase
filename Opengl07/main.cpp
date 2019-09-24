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
	if(argc<4)
	{
		cout<<"ERROR: Se necesitan 3 parámetros "<<endl;
		cout<<"ruta_a_vertex ruta_a_fragment ruta_a_obj"<<endl;

		return -1;
	}
    
		Window win;
    win.startup("Geometry",argv[1],argv[2],argv[3]);
   	win.run();
    return 0;
}

