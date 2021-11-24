#ifndef OBJ_LOADER_H_
#define OBJ_LOADER_H_

#include <GL/glew.h>
#include <string.h>

#include "slurp_file.h"
#include "primitive.h"

Primitive obj_load(const GLchar* file_path);

#endif // OBJ_LOADER_H_