/* 
 * File:   Geometry.cpp
 * Author: ulises
 * 
 * Created on 27 de agosto de 2019, 10:20
 */

#include "Geometry.h"
#include <fstream>
#include <sstream>

Geometry::Geometry()
{
    //ctor
}

Geometry::~Geometry()
{
    //dtor
}


void Geometry::create(string pathTex)
{
    glGenVertexArrays(1, &gl.vao);
    glGenBuffers(1, &gl.vbo);
    glGenBuffers(1, &gl.nbo);
    glGenBuffers(1, &gl.tbo);
    glGenBuffers(1, &gl.ebo);
    vector<string> texs = {pathTex};
    texture.startup(texs);

    glBindBuffer(GL_ARRAY_BUFFER, gl.vbo);
    glBufferData(GL_ARRAY_BUFFER, info.vertices.size()*sizeof(vec3),  &info.vertices[0], GL_STATIC_DRAW);   

    glBindBuffer(GL_ARRAY_BUFFER, gl.nbo);
    glBufferData(GL_ARRAY_BUFFER, info.normals.size()*sizeof(vec3),   &info.normals[0], GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, gl.tbo);
    glBufferData(GL_ARRAY_BUFFER, info.texCoords.size()*sizeof(vec2), &info.texCoords[0], GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gl.ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, info.indices.size()*sizeof(GLuint), &info.indices[0], GL_STATIC_DRAW);
    
    texture.active();
    glBindVertexArray(gl.vao);
}


void Geometry::create(const vector<string> &textures)
{
    glGenVertexArrays(1, &gl.vao);
    glGenBuffers(1, &gl.vbo);
    glGenBuffers(1, &gl.nbo);
    glGenBuffers(1, &gl.tbo);
    glGenBuffers(1, &gl.tgbo);
    glGenBuffers(1, &gl.ebo);
    
    texture.startup(textures);

    glBindBuffer(GL_ARRAY_BUFFER, gl.vbo);
    glBufferData(GL_ARRAY_BUFFER, info.vertices.size()*sizeof(vec3),  &info.vertices[0], GL_STATIC_DRAW);   

    glBindBuffer(GL_ARRAY_BUFFER, gl.nbo);
    glBufferData(GL_ARRAY_BUFFER, info.normals.size()*sizeof(vec3),   &info.normals[0], GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, gl.tbo);
    glBufferData(GL_ARRAY_BUFFER, info.texCoords.size()*sizeof(vec2), &info.texCoords[0], GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, gl.tgbo);
    glBufferData(GL_ARRAY_BUFFER, info.tangents.size()*sizeof(vec4), &info.tangents[0], GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gl.ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, info.indices.size()*sizeof(GLuint), &info.indices[0], GL_STATIC_DRAW);
    
    texture.active();
    glBindVertexArray(gl.vao);
}

void Geometry::startup(vector<vec3> v, vector<vec3> c, vector<GLuint> i)
{
  info.vertices = v;  
  info.indices=i;
  create("tex");
  bindData();
}

void Geometry::startup(string s,string pathTex){
  readObj(s);
  create(pathTex);
  bindData();
}

void Geometry::startup(string pathObj, const vector<string> &textures)
{
	readObj(pathObj);
	create(textures);
	bindData();
}

void Geometry::bindData()
{
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);

    glBindBuffer(GL_ARRAY_BUFFER, gl.vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, gl.nbo);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    
    glBindBuffer(GL_ARRAY_BUFFER, gl.tbo);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    
    glBindBuffer(GL_ARRAY_BUFFER, gl.tgbo);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gl.ebo);
}

void Geometry::draw()
{    
    glBindVertexArray(gl.vao);
    glDrawElements(GL_TRIANGLES, info.indices.size(),GL_UNSIGNED_INT, nullptr);
}

void Geometry::shutdown()
{
  texture.shutdown();
  glDeleteBuffers(1, &gl.nbo);
  glDeleteBuffers(1, &gl.tbo);
  glDeleteBuffers(1, &gl.tgbo);
  glDeleteBuffers(1, &gl.vbo);  
  glDeleteBuffers(1, &gl.ebo);
  texture.shutdown();
  glDeleteVertexArrays(1, &gl.vao);
}

void Geometry::readObj(string path){
    
    ifstream file;
    file.open(path.c_str());
    VertexInfo temp;
    VertexInfo out;
    vector<GLuint> vidx, nidx, tcidx;

    if (file.is_open()) {
        string line, token;
        stringstream sline;
        while (!file.eof()) {
            getline(file, line);
            sline = stringstream(line);
            sline>>token;
            if (token == "v") {
                vec3 vertex;
                sline >> vertex.x >> vertex.y >> vertex.z;
                temp.vertices.push_back(vertex);
            } else if (token == "vn") {
                vec3 normal;
                sline >> normal.x >> normal.y >> normal.z;
                temp.normals.push_back(normal);
            } else if (token == "vt") {
                vec2 tex;
                sline >> tex.x >> tex.y;
                temp.texCoords.push_back(tex);
            } else if (token == "f") {
                string v[3];
                sline >> v[0] >> v[1] >> v[2];
                string tok;
                for (int i = 0; i < 3; i++) {
                    stringstream data(v[i]);

                    getline(data, tok, '/');
                    vidx.push_back(stoi(tok) - 1);

                    getline(data, tok, '/');                    
                    tcidx.push_back(stoi(tok) - 1);

                    getline(data, tok, '/');
                    nidx.push_back(stoi(tok) - 1);

                }
            }
            token = "";
        }
        
        out.align(temp, vidx, nidx, tcidx);
        

        info.indexing(out);
        info.genTangents();
        file.close();

    } else {
        throw runtime_error("Error al abrir el archivo obj");
    }
}

void VertexInfo::align(VertexInfo &other, vector<GLuint> vidx, vector<GLuint> nidx, vector<GLuint> tcidx){
    for(GLuint i = 0; i < vidx.size(); i++){
        vertices.push_back(other.vertices[vidx[i]]);
        normals.push_back(other.normals[nidx[i]]);
        texCoords.push_back(other.texCoords[tcidx[i]]);        
    }
}

void VertexInfo::indexing(VertexInfo &other){
    GLuint index = 0;
    bool isTrue;
    for(GLuint i = 0; i < other.vertices.size(); i++){
        isTrue=false;
        for(GLuint j = 0; j < vertices.size(); j++){
            if(isSimilar(other.vertices[i],other.normals[i], other.texCoords[i], vertices[j], normals[j], texCoords[j])){
                indices.push_back(j);
                isTrue=true;                
                break;
            }            
        }
        if(!isTrue){
            vertices.push_back(other.vertices[i]);
            normals.push_back(other.normals[i]);
            texCoords.push_back(other.texCoords[i]);            
            indices.push_back(index++);
        }        
    }
}

bool VertexInfo::isSimilar(vec3 v, vec3 n, vec2 tc, vec3 v1, vec3 n1, vec2 tc1){    
    GLfloat vx, vy, vz, nx, ny, nz, tcx, tcy;
    vx = fabs(v.x -v1.x);
    vy = fabs(v.y -v1.y);
    vz = fabs(v.z -v1.z);
    nx = fabs(n.x -n1.x);
    ny = fabs(n.y -n1.y);
    nz = fabs(n.z -n1.z);
    tcx = fabs(tc.x -tc1.x);
    tcy = fabs(tc.y -tc1.y);
    float r = 0.01f;
    return vx <r && vy < r && vz <r && nx < r && ny < r && nz < r && tcx <r && tcy <r;
}

void VertexInfo::genTangents(){
    
    vector<vec3> tanAccum1(vertices.size());
    vector<vec3> tanAccum2(vertices.size());
    tangents.resize(vertices.size());
    
    for(GLuint i = 0; i < indices.size(); i+=3){
        
        const vec3 &p1 = vertices[indices[i]];
        const vec3 &p2 = vertices[indices[i+1]];
        const vec3 &p3 = vertices[indices[i+2]];
        
        
        const vec2 &tc1 = texCoords[indices[i]];
        const vec2 &tc2 = texCoords[indices[i+1]];
        const vec2 &tc3 = texCoords[indices[i+2]];
        
        
        vec3 q1 = p2 -p1;
        vec3 q2 = p3 -p1;
        
        float s1 = tc2.x - tc1.x;
        float s2 = tc3.x - tc1.x;
        float t1 = tc2.y - tc1.y;
        float t2 = tc3.y - tc1.y;
        
        float r = 1.0f/(s1 *t2 - s2 *t1);
        
        vec3 tan1((t2*q1.x -t1*q2.x)*r,
                  (t2*q1.y -t1*q2.y)*r,
                  (t2*q1.z -t1*q2.z)*r);
        vec3 tan2((s1*q2.x -s2*q1.x)*r,
                  (s1*q2.y -s2*q1.y)*r,
                  (s1*q2.z -s2*q1.z)*r);
        
        tanAccum1[indices[i]]   += tan1;
        tanAccum1[indices[i+1]] += tan1;
        tanAccum1[indices[i+2]] += tan1;
        tanAccum2[indices[i]]   += tan2;
        tanAccum2[indices[i+1]] += tan2;
        tanAccum2[indices[i+2]] += tan2;
    }
    
    
    for(GLuint i = 0; i < vertices.size(); i++){
        
        const vec3 &n = normals[i];
        vec3 &t1 = tanAccum1[i];
        vec3 &t2 = tanAccum2[i];
        
        tangents[i] = vec4(normalize(t1 - (dot(n,t1)*n)), 0.0f);
        tangents[i].w = (dot(cross(n, t1), t2) < 0.0f) ? -1.0f : 1.0f;
    }
}

