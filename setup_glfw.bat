@echo off

curl -fsSL -o glfw-3.3.2.bin.WIN64.zip https://github.com/glfw/glfw/releases/download/3.3.2/glfw-3.3.2.bin.WIN64.zip
tar -xf glfw-3.3.2.bin.WIN64.zip
mkdir build\Dependencies\GLFW\lib\
move glfw-3.3.2.bin.WIN64\lib-vc2019\glfw3.lib build\Dependencies\GLFW\lib\glfw3.lib
mkdir build\Dependencies\GLFW\include\GLFW
move glfw-3.3.2.bin.WIN64\include\GLFW\glfw3.h build\Dependencies\GLFW\include\GLFW\glfw3.h
del glfw-3.3.2.bin.WIN64.zip
rmdir /s /q glfw-3.3.2.bin.WIN64
