PKGS=glfw3 gl glew cglm
CFLAGS=-Wall -Wextra -ggdb

main: src/main.c
	$(CC) $(CFLAGS) `pkg-config --cflags $(PKGS)` -o build/sco-op src/slurp_file.c src/shaders.c src/game.c src/main.c `pkg-config --libs $(PKGS)` -lm