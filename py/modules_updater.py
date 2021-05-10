import glob
import sys


sys.stdout = open('../Modules/modules.cpp', 'w')
pattern = "// [[not imported module]]"
print(pattern)
files = glob.glob("../Modules/*.cpp")
result = []
print("#include \"modules.h\"")
print("#include \"all.h\"")
print()
print("using namespace SlavaScript::modules;")
print()
print("bool SlavaScript::modules::try_import_module(std::string name){")
for file in files:
	with open(file, 'r') as fd:
		text = fd.read()
	if text[0:26] != pattern:
		result.append(file)
for i in range(len(result)):
	name = result[i][11:-4].lower()
	module_name = name[0].upper() + name[1:]
	if module_name == 'Modules':
		continue
	start = "else if"
	if i == 0:
		start = "if"
	print("\t" + start + " (name == \"" + name + "\") " + module_name + "::init();")
print("\telse return false;")
print("\treturn true;")
print("}")
input()
