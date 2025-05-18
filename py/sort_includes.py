import glob
import os


def get_files():
    abspath = os.path.abspath(__file__)
    os.chdir(os.path.dirname(abspath))
    os.chdir("../")
    cpp = glob.glob('**/*.cpp', recursive=True)
    h = glob.glob('**/*.h', recursive=True)
    files = cpp + h
    files = [file.replace('\\', '/') for file in files]
    return files


def is_system(include):
    if include == '<windows.h>':
        return True
    if include.startswith('<SFML/'):
        return True
    if '.h' not in include:
        return True
    return False


def get_includes(lines):
    includes_system = []
    includes_own = []
    ending = []
    heading = True
    for line in lines:
        if heading:
            text = line.strip()
            if len(text) == 0:
                continue
            elif text.startswith('//'):
                continue
            elif text == '#pragma once':
                continue
            elif text.startswith('#include'):
                include = text.split('#include')[-1].strip()
                if is_system(include):
                    includes_system.append(include)
                else:
                    includes_own.append(include)
            else:
                heading = False
        if not heading:
            ending.append(line)
    while len(ending) and len(ending[-1].strip()) == 0:
        ending.pop()
    return includes_system, includes_own, ending


files = get_files()
for file in files:
    with open(file, 'r', encoding='utf-8') as f:
        lines = f.readlines()
    includes_system, includes_own, ending = get_includes(lines)
    includes_system.sort()
    includes_own.sort()
    output = ''
    if file.endswith('.h'):
        output += '#pragma once\n\n'
    for include in includes_system:
        output += '#include {}\n'.format(include)
    if len(includes_system) and len(includes_own):
        output += '\n'
    for include in includes_own:
        output += '#include {}\n'.format(include)
    if len(ending):
        if len(includes_system) + len(includes_own) == 0:
            if file.endswith('.h'):
                output += '\n'
        else:
            if output.endswith('\n\n'):
                output += '\n'
            else:
                output += '\n\n'
        for line in ending:
            output += line
    with open(file, 'w', encoding='utf-8') as f:
        f.write(output)
