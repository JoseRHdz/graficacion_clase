/* 
 * File:   Texture.cpp
 * Author: ulises
 * 
 * Created on 28 de septiembre de 2019, 23:45
 */

#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


Texture::Texture() {
    
}

Texture::~Texture() {
    
}

void Texture::startup(vector<string> files)
{
	for(GLuint i =0; i < files.size(); i++){
		tids.push_back(create(files[i]));
	}    
}

GLuint Texture::create(string file) throw(){
    unsigned char* data;
    int width, height, nrChannels;
    GLuint tid;
    
    data = stbi_load(file.c_str(), &width, &height, &nrChannels, 0);
    
    if(data){
        
        glGenTextures(1, &tid);
        glBindTexture(GL_TEXTURE_2D, tid);
        
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        GLint channels= 0;
        if(nrChannels==0) channels = GL_RED;
        else if(nrChannels==1) channels = GL_GREEN;
        else if(nrChannels==2) channels = GL_BLUE;
        else if(nrChannels==3) channels = GL_RGB;
        else if(nrChannels ==4) channels = GL_RGBA;
        glTexImage2D(GL_TEXTURE_2D, 0, channels, width, height, 0, channels, GL_UNSIGNED_BYTE, data);        
        glGenerateMipmap(GL_TEXTURE_2D);        
        stbi_image_free(data);
        return tid;
        
    }else{
        throw runtime_error("No se pudo cargar la textura "+ file);
    }
}


void Texture::active(){
	for(GLuint i = 0; i < tids.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0+i);
		glBindTexture(GL_TEXTURE_2D, tids[i]);   
	}
}


GLuint Texture::getTid(GLuint i)
{
    return tids[i];
}

void Texture::shutdown()
{
	for(GLuint i = 0; i < tids.size(); i++)
	{
		glDeleteTextures(1, &tids[i]);
	}
	tids.clear();    
}
