#include "material.h"

void material_send_to_program(Material material, Program program)
{
    program_set_vec3fv(program, "material.ambient", material.ambient);
    program_set_vec3fv(program, "material.diffuse", material.diffuse);
    program_set_vec3fv(program, "material.specular", material.specular);

    program_set_1i(program, "material.diffuse_texture", material.diffuse_texture);
    program_set_1i(program, "material.specular_texture", material.specular_texture);
}