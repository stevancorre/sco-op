PKGS=glfw3 gl
CFLAGS=-Wall -Wextra -ggdb

main: src/main.c
	$(CC) $(CFLAGS) `pkg-config --cflags $(PKGS)` -o build/sco-op src/main.c `pkg-config --libs $(PKGS)` -lm