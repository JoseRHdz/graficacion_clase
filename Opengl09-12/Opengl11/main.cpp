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
	vector<string> textures;
	vector<string> shaders;
	string obj, title;
	string t="";
	title = string(argv[1]);
	int i=2;
	if( argc < 5){
		cout<< "hacen falta parámetros para iniciar el programa"<<endl;
	}
	while(i < argc){
		t = string(argv[i++]);				
		if(t =="-s"){			
			do{
				t = string(argv[i++]);
				if(t != "-t" && t != "-o"){
					shaders.push_back(t);									
				}
			}while(t != "-t" && t != "-o" && i < argc );
		}
		
		if(t =="-t"){			
			do{
				t = string(argv[i++]);
				if(t != "-s" && t != "-o"){
					textures.push_back(t);									
				}
			}while(t != "-s" && t != "-o" && i < argc );
		}
		
		if(t =="-o"){
			t = string(argv[i++]);			
			obj = t;
		}		
	}
    
    win.startup(title, obj, shaders, textures);    
    win.run();
    cout<<"End program"<<endl;
    return 0;
}

