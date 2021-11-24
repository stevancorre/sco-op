#include "obj_loader.h"

#define SV_IMPLEMENTATION
#include "sv.h"

static float __sv_to_float(String_View sv)
{
    if (sv.count == 0)
    {
        return 0;
    }

    char *str = (char *)malloc(sv.count);
    sprintf(str, SV_Fmt, SV_Arg(sv));

    return atof(str);
}

static float __sv_read_float(String_View *source)
{
    return __sv_to_float(sv_chop_by_delim(source, ' '));
}

static vec2s __sv_read_vec2(String_View *source)
{
    // skip prefix
    sv_chop_by_delim(source, ' ');

    vec2s ret = (vec2s){
        .x = __sv_read_float(source),
        .y = __sv_read_float(source)};

    GLMS_VEC2_PRINTLN(ret);

    return ret;
}

static vec3s __sv_read_vec3(String_View *source)
{
    // skip prefix
    sv_chop_by_delim(source, ' ');

    return (vec3s){
        .x = __sv_read_float(source),
        .y = __sv_read_float(source),
        .z = __sv_read_float(source)};
}

// since my game is going to be low res, lot of cubes etc, i don't need lot of vertices
#define VERTEX_CAPACITY 512

Primitive obj_load(const GLchar *file_path)
{
    String_View raw_obj = sv_from_cstr(slurp_file(file_path));

    vec3s vertex_positions[VERTEX_CAPACITY];
    vec2s vertex_texcoords[VERTEX_CAPACITY];
    vec3s vertex_normals[VERTEX_CAPACITY];

    GLuint vertex_position_count = 0;
    GLuint vertex_texcoord_count = 0;
    GLuint vertex_normal_count = 0;

    String_View line;
    while (sv_try_chop_by_delim(&raw_obj, '\n', &line))
    {
        // vertex
        if (sv_starts_with(line, sv_from_cstr("v ")))
        {
            vertex_positions[vertex_position_count++] = __sv_read_vec3(&line);
        }
        else if (sv_starts_with(line, sv_from_cstr("vt ")))
        {
            vertex_texcoords[vertex_texcoord_count++] = __sv_read_vec2(&line);
        }
        else if (sv_starts_with(line, sv_from_cstr("vn ")))
        {
            vertex_normals[vertex_normal_count++] = __sv_read_vec3(&line);
        }
    }

    Primitive primitive = {
        .vertex_count = vertex_position_count,
        .vertices = (Vertex *)malloc(vertex_position_count * sizeof(Vertex)),
        .index_count = 0,
        .indices = 0};

    for (GLuint i = 0; i < primitive.vertex_count; i++)
    {
        primitive.vertices[i] = (Vertex){
            .color = GLMS_VEC3_ZERO,
            .position = vertex_positions[i],
            .texcoord = vertex_texcoords[i],
            .normal = vertex_normals[i]};
    }

    return primitive;
}