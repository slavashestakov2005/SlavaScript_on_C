#include "path.h"
#include "../Value/stringvalue.h"
#include "../Lib/variables.h"
#include "../Lib/functions.h"
#include "../Lib/classdeclarations.h"
#include "../Cpp17/filesystem.h"

using namespace SlavaScript::lang;
using namespace SlavaScript::Cpp17;

std::vector<std::string> Path::pathes = {};
bool Path::import = true;
std::shared_ptr<ArrayValue> Path::arguments = nullptr;

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

void Path::initContainers(){
    Variables::init();
    Functions::init();
    ClassDeclarations::init();
}

void Path::setCommandArguments(std::vector<std::string> argv){
    arguments = SHARE(ArrayValue, argv.size());
    for(int i = 0; i < argv.size(); ++i) arguments -> set(i, SHARE(StringValue, argv[i]));
    FS::setApplicationPath(argv[0]);
}

std::shared_ptr<ArrayValue> Path::getCommandArguments(){
    return arguments;
}
