/* 
 * File:   Texture.h
 * Author: ulises
 *
 * Created on 28 de septiembre de 2019, 23:45
 */

#ifndef TEXTURE_H
#define TEXTURE_H
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include <GL/glew.h>



class Texture {
public:
    Texture();        
    virtual ~Texture();

    void startup(vector<string> files);
    void active();
    void shutdown();
    GLuint getTid(GLuint i);
    
private:
    vector<GLuint> tids;
    GLuint create(string file) throw();
};

#endif /* TEXTURE_H */

