/* 
 * File:   ShaderException.h
 * Author: ulises
 *
 * Created on 27 de agosto de 2019, 10:21
 */

#ifndef SHADEREXCEPTION_H
#define SHADEREXCEPTION_H

#include <iostream>
#include <string>

using namespace std;


class ShaderException : public runtime_error
{
    public:
        ShaderException(const string& msg);
        virtual ~ShaderException();
};

#endif /* SHADEREXCEPTION_H */

