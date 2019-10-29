#include "Loader.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
using namespace glm;

Loader::Loader()
{
}

Loader::~Loader()
{
}

void Loader::startup(const string &file, Geometry *geo) throw()
{
    Assimp::Importer imp;
    const aiScene* scene = imp.ReadFile(file, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);    
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        throw runtime_error(imp.GetErrorString());
    }    
    processData(scene, scene->mRootNode, geo);
    cout<<"Se creo correctamente la geo"<<endl;
}

void Loader::processData(const aiScene *scene, aiNode *node, Geometry *geo)
{ 
    if(node->mNumMeshes >0){
        aiMesh *mesh = scene->mMeshes[node->mMeshes[0]]; 
        getGeometryData(mesh, geo);
        cout<<"retornando la maya"<<endl;
        return;
    }
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processData(scene, node->mChildren[i], geo);
    }
    
}

void  Loader::getGeometryData(const aiMesh *mesh, Geometry *geo)
{    
    for(GLuint i= 0; i < mesh->mNumVertices; i++)
    {
        vec3 vertex;
        vertex.x = mesh->mVertices[i].x;
        vertex.y = mesh->mVertices[i].y;
        vertex.z = mesh->mVertices[i].z;
        geo->info.vertices.push_back(vertex);
        
        vertex.x = mesh->mNormals[i].x;
        vertex.y = mesh->mNormals[i].y;
        vertex.z = mesh->mNormals[i].z;
        geo->info.normals.push_back(vertex);
        
        if( mesh->mTextureCoords[0])
        {
            vec2 tcoord;
            tcoord.x = mesh->mTextureCoords[0][i].x;
            tcoord.y = mesh->mTextureCoords[0][i].y;
            geo->info.texCoords.push_back(tcoord);
        }else 
            geo->info.texCoords.push_back(vec2(0.0f, 0.0f));
        
        vertex.x = mesh->mTangents[i].x;
        vertex.y = mesh->mTangents[i].y;
        vertex.z = mesh->mTangents[i].z;
        geo->info.tangents.push_back(vertex);
        
        vertex.x = mesh->mBitangents[i].x;
        vertex.y = mesh->mBitangents[i].y;
        vertex.z = mesh->mBitangents[i].z;
        geo->info.binormals.push_back(vertex);
    }
    
    for(GLuint i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for(GLuint j = 0; j < face.mNumIndices; j++)
            geo->info.indices.push_back(face.mIndices[j]);
    }
    
    cout<<"Indices "<< geo->info.indices.size()<<endl;
    
            
}
