#include <Lib/filesystem.h>
#include <Lib/names.h>
#include <Run/path.h>
#include <Value/stringvalue.h>


using namespace SlavaScript::lang;

std::vector<std::string> Path::pathes = {};
bool Path::import = true;
std::shared_ptr<ArrayValue> Path::arguments = nullptr;

void Path::setPath(std::string path) {
    pathes.push_back(path);
}

std::string Path::getPath() {
    return pathes.back();
}

void Path::popPath() {
    pathes.pop_back();
}

bool Path::getImpoted() {
    return import;
}

void Path::setImpoted(bool imp) {
    import = imp;
}

void Path::initContainers() {
    Names::init();
}

void Path::setCommandArguments(std::vector<std::string> argv) {
    arguments = SHARE(ArrayValue, argv.size());
    for (size_t i = 0; i < argv.size(); ++i) arguments -> set(i, SHARE(StringValue, argv[i]));
    FS::setApplicationPath(argv[0]);
}

std::shared_ptr<ArrayValue> Path::getCommandArguments() {
    return arguments;
}
