#ifndef SLURP_FILE_H_
#define SLURP_FILE_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>

/**
 * @brief Read content from a specified file and handle any error
 * 
 * @param file_path The target file path
 * @return The file's content
 */
char *slurp_file(const char *file_path);

#endif // SLURP_FILE_H