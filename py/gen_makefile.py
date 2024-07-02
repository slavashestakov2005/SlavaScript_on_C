import glob
import os


abspath = os.path.abspath(__file__)
os.chdir(os.path.dirname(abspath))
os.chdir("../")
files = glob.glob('**/*.cpp', recursive=True)
files = [file.replace('\\', '/')[:-4] for file in files]
print(files)
with open('.vscode/Makefile', 'w', encoding='UTF-8') as f:
    f.write(r'''OBJ = build_cpp/obj
GPP = g++ -Wall -std=c++20
SFML_INCLUDE = -I C:\Users\Public\Plugins\SFML-2.5.1\include
SFML_LIB = -L C:\\Users\Public\Plugins\SFML-2.5.1\lib -lsfml-graphics -lsfml-window -lsfml-system

''')
    obj = ' '.join(['$(OBJ)/{0}.o'.format(file) for file in files]) + ' $(OBJ)/icon.res'
    f.write('run: {0}\n\t$(GPP) -o build_cpp/run {0} $(SFML_LIB)\n'.format(obj))
    compile_file = '$(OBJ)/{0}.o: {0}.cpp\n\t$(GPP) -c -o $(OBJ)/{0}.o {0}.cpp'
    for file in files:
        cmd = compile_file.format(file)
        if 'draw' in file:
            cmd += ' $(SFML_INCLUDE)'
        cmd += '\n'
        f.write(cmd)
    f.write('''$(OBJ)/icon.res: icon.ico icon.rc
	windres icon.rc -O coff -o $(OBJ)/icon.res
''')
