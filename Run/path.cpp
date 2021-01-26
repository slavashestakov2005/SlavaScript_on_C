#include "path.h"
#include "../Value/stringvalue.h"

using namespace SlavaScript::lang;

std::vector<std::string> Path::pathes = {};
bool Path::import = true;
ArrayValue* Path::arguments = nullptr;

void Path::setPath(std::string path){
    pathes.push_back(path);
}

std::string Path::getPath(){
    return pathes.back();
}

void Path::popPath(){
    pathes.pop_back();
}

bool Path::getImpoted(){
    return import;
}

void Path::setImpoted(bool imp){
    import = imp;
}

void Path::setCommandArguments(std::vector<std::string> argv){
    arguments = new ArrayValue(argv.size());
    for(int i = 0; i < argv.size(); ++i) arguments -> set(i, new StringValue(argv[i]));
}

ArrayValue* Path::getCommandArguments(){
    return arguments;
}
