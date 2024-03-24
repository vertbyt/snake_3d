@echo off

if not exist "../build/raylib/" (
mkdir "../build/raylib"
call "build_raylib.bat"
)

set add_inc=/I C:/faruk/web_engine/code/rl50/
set cl_flags=-nologo -Zi -Od -MP -c -F4194304 %add_inc%

set link_flags=-nologo -debug -out:"snake_3d.exe" -subsystem:console -STACK:4194304

set libs_x64=raylib/raylib.lib user32.lib shell32.lib gdi32.lib winmm.lib msvcrt.lib

pushd "../build"

cl %cl_flags% ../code/all.cpp 
link %link_flags% all.obj %libs_x64%  

popd
