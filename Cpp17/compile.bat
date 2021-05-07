cls

set F=C:\Users\Слава\Desktop\Презентации\Информатика и Информационные технологии\Языки программирования\CodeBlocks\S++\second\Cpp17

cd C:\MinGW-9.2.0\bin

g++.exe -Wall -DBUILD_DLL -g -std=c++17 -c "%F%\filesystem.cpp" -o "%F%\obj\Debug\filesystem.o"
g++.exe -shared -Wl,--output-def="%F%\bin\Debug\libCpp17.def" -Wl,--out-implib="%F%\bin\Debug\libCpp17.a" -Wl,--dll "%F%\obj\Debug\filesystem.o" -o "%F%\bin\Debug\Cpp17.dll" -static-libstdc++ -static-libgcc  -luser32

cd %F%
cd ..

copy Cpp17\bin\Debug\Cpp17.dll Cpp17.dll
copy Cpp17\bin\Debug\Cpp17.dll dlls\Cpp17.dll
copy Cpp17\bin\Debug\libCpp17.a dlls\libCpp17.a
copy Cpp17\bin\Debug\Cpp17.dll bin\Debug\Cpp17.dll

cd Cpp17