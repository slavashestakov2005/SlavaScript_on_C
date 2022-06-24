// [[not imported module]]
#include "files.h"
#include "../Exception/exceptions.h"
#include "../Lib/classes.h"
#include "../Lib/classmethod.h"
#include "../Lib/moduleclass.h"
#include "../Lib/moduleobject.h"
#include "../Lib/utils.h"
#include "../Run/path.h"
#include "../Value/numbervalue.h"
#include <fstream>
#include <sstream>

using namespace SlavaScript::lang;
using namespace SlavaScript::modules::files_f;
using SlavaScript::modules::Files;
using SlavaScript::exceptions::UnknownOperationException;
using SlavaScript::exceptions::UnknownPropertyException;


namespace SlavaScript::modules::files_out{
    CLASS_IN_MODULE_1(File)
        std::string name;
        std::fstream file;
        bool bad;

        File(std::string name) : name(name){
            file.open(Path::getPath() + name);
            bad = !file;
        }

        std::shared_ptr<Value> copy() override{
            return SHARE(File, name);
        }
        operator std::string() override{ return "<file=\"" + name + "\">"; }
        std::shared_ptr<Value> getDot(std::shared_ptr<Value> property) override;
        ~File(){}
    CLASS_IN_MODULE_2(File)

    CLASS_METHOD_PTR(Close, File)
        argsCount(0, values.size());
        instance -> file.close();
        return NullValue::NULL_;
    CME

    CLASS_METHOD_PTR(Read, File)
        instance -> file.seekg(0, instance -> file.beg);
        std::stringstream str;
        str << instance -> file.rdbuf();
        SH_RET(StringValue, str.str());
    CME

    CLASS_METHOD_PTR(ReadLine, File)
        argsCount(0, values.size());
        std::string line;
        if (instance -> file) std::getline(instance -> file, line);
        SH_RET(StringValue, line);
    CME

    CLASS_METHOD_PTR(WriteLine, File)
        argsCount(1, values.size());
        if (instance -> file && instance -> file.tellg() < instance -> file.end) instance -> file << values[0] -> asString();
        else if (!instance -> bad){
            instance -> file.seekg(0, instance -> file.beg);
            instance -> file << values[0] -> asString();
        }
        else return NumberValue::M_ONE;
        return NumberValue::ZERO;
    CME

    std::shared_ptr<Value> File::getDot(std::shared_ptr<Value> property){
        std::string prop = property -> asString();
        if (bad) throw UnknownOperationException(".", shared_from_this());
        ADD_METHOD_PTR("close", Close);
        ADD_METHOD_PTR("read", Read);
        ADD_METHOD_PTR("read_line", ReadLine);
        ADD_METHOD_PTR("write_line", WriteLine);
        throw UnknownPropertyException(prop);
    }
}

namespace SlavaScript::modules::files_f{
    CREATE_FUNCTION(open)
        argsCount(1, values.size());
        std::shared_ptr<files_out::File> file = SHARE(files_out::File, values[0] -> asString());
        if (file -> bad) return NumberValue::M_ONE;
        return CAST(Value, file);
    FE

    DEF_CLASS(files_out, File)
}

void Files::initFunctions(){
    UNARY_F(open)
}

void Files::initClasses(){
    SET_CLASS(files_f, File)
}
