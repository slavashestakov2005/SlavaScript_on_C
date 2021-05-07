// [[not imported module]]
#include "modules.h"
#include "all.h"

using namespace SlavaScript::modules;

bool SlavaScript::modules::try_import_module(std::string name){
	if (name == "chemistry") Chemistry::init();
	else if (name == "draw") Draw::init();
	else if (name == "files") Files::init();
	else if (name == "functional") Functional::init();
	else if (name == "math") Math::init();
	else if (name == "std") Std::init();
	else if (name == "types") Types::init();
	else return false;
	return true;
}
