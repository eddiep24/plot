#ifndef _UTILS_H
#define _UTILS_H


#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <cmath>

#include "math_utils.h"
#include "shader_utils.h"
#include "logs.h"


std::string readFile(const char* filePath);
bool loadShaderProgram(const bool erase_if_program_registered);
#endif