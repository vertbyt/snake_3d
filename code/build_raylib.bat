@echo off

set rl_src=c:/faruk/web_engine/code/rl50/

set add_inc=/I %rl_src%external/glfw/include
set cl_flags=-Zi -Od -MP -c -nologo -DPLATFORM_DESKTOP -DGRAPHICS_API_OPENGL_33 %add_inc%


cd ../build/raylib

cl %cl_flags% %rl_src%*.c
lib -nologo *.obj -out:raylib.lib

cd ../../code

