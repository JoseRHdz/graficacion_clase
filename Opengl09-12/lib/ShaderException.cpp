/* 
 * File:   ShaderException.cpp
 * Author: ulises
 * 
 * Created on 27 de agosto de 2019, 10:21
 */

#include "ShaderException.h"

ShaderException::ShaderException(const string& msg): runtime_error(msg)
{
    //ctor
}

ShaderException::~ShaderException()
{
    //dtor
}

