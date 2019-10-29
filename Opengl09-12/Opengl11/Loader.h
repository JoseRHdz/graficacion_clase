#ifndef LOADER_H
#define LOADER_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Geometry.h"

class Loader{
public:
    Loader();
    virtual ~Loader();
    void startup(const string &file, Geometry *geo)throw();
    
private:    
    void processData(const aiScene *scene, aiNode *node,Geometry *geo);
    void getGeometryData(const aiMesh *mesh,Geometry *geo);    
};

#endif //LOADER_H
