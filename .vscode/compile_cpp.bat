set FileName=%1
if not exist .build_cpp (
    mkdir .build_cpp
    cd .build_cpp
    cmake -G "MinGW Makefiles" ..
) else (
    cd .build_cpp
)

make run
cd ..
start cmd /k ".build_cpp\run -f Examples\\example.s++"
