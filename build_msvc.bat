@echo off
rem launch this from msvc-enabled console

set CFLAGS=/std:c11 /O2 /FC /W4 /WX /Zl /D_USE_MATH_DEFINES /wd4996 /nologo
set INCLUDES=/I build\Dependencies\GLFW\include
set LIBS=build\Dependencies\GLFW\lib\glfw3.lib opengl32.lib User32.lib Gdi32.lib Shell32.lib

cl.exe %CFLAGS% %INCLUDES% /Fe"build/sco-op.exe" ./src/main.c %LIBS% /link /NODEFAULTLIB:libcmt.lib
