#include "slurp_file.h"

void panic(bool condition, const char *file_path)
{
    if (condition)
    {
        fprintf(stderr, "ERROR:\tcould not read file `%s`: %s\n", file_path, strerror(errno));
        exit(1);
    }
}

char *slurp_file(const char *file_path)
{
    FILE *file = fopen(file_path, "r");
    panic(file == NULL, file_path);
    panic(fseek(file, 0, SEEK_END) < 0, file_path);

    long size = ftell(file);
    panic(size < 0, file_path);

    char *buffer = malloc(size + 1);
    panic(buffer == NULL, file_path);
    panic(fseek(file, 0, SEEK_SET) < 0, file_path);

    fread(buffer, 1, size, file);
    panic(ferror(file) < 0, file_path);

    buffer[size] = '\0';
    panic(fclose(file) < 0, file_path);

    return buffer;
}