PKGS=glfw3 gl glew cglm
CFLAGS=-Wall -Wextra -Werror -ggdb

main: src/main.c
	$(CC) $(CFLAGS) `pkg-config --cflags $(PKGS)` -o build/sco-op src/slurp_file.c src/shader.c src/material.c src/program.c src/texture.c src/primitive.c src/model.c src/mesh.c src/camera.c src/obj_loader.c src/game.c src/main.c `pkg-config --libs $(PKGS)` -lm