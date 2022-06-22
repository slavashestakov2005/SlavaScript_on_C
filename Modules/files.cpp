// [[not imported module]]
#include "files.h"
#include "../Lib/functions.h"
#include "../Lib/variables.h"
#include "../Value/value.h"
#include "../Value/nullvalue.h"
#include "../Value/numbervalue.h"
#include "../Value/stringvalue.h"
#include "../Value/functionvalue.h"
#include "../Lib/classes.h"
#include "../Lib/moduleclass.h"
#include "../Lib/moduleobject.h"
#include "../Exception/argumentsmismatchexception.h"
#include "../Exception/unknownpropertyexception.h"
#include "../Run/path.h"
#include <fstream>
#include <sstream>

using namespace SlavaScript::lang;
using namespace SlavaScript::modules::files_f;
using SlavaScript::modules::Files;
using SlavaScript::exceptions::ArgumentsMismatchException;
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

    CLASS_METHOD(Close, File*)
        if (values.size()) throw new ArgumentsMismatchException("Zero arguments expected");
        instance -> file.close();
        return NullValue::NULL_;
    CME

    CLASS_METHOD(Read, File*)
        instance -> file.seekg(0, instance -> file.beg);
        std::stringstream str;
        str << instance -> file.rdbuf();
        SH_RET(StringValue, str.str());
    CME

    CLASS_METHOD(ReadLine, File*)
        if (values.size() != 0) throw new ArgumentsMismatchException("Zero arguments expected");
        std::string line;
        if (instance -> file) std::getline(instance -> file, line);
        SH_RET(StringValue, line);
    CME

    CLASS_METHOD(WriteLine, File*)
        if (values.size() != 1) throw new ArgumentsMismatchException("One arguments expected");
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
        if (bad) throw new TypeException("Cannot use DOT for not opened file");
        if (prop == "close") SH_RET(FunctionValue, new Close(this));
        if (prop == "read") SH_RET(FunctionValue, new Read(this));
        if (prop == "read_line") SH_RET(FunctionValue, new ReadLine(this));
        if (prop == "write_line") SH_RET(FunctionValue, new WriteLine(this));
        throw new UnknownPropertyException(prop);
    }
}

namespace SlavaScript::modules::files_f{
    CREATE_FUNCTION(open)
        if (values.size() != 1) throw new ArgumentsMismatchException("One arguments expected");
        std::shared_ptr<files_out::File> file = SHARE(files_out::File, values[0] -> asString());
        if (file -> bad) return NumberValue::M_ONE;
        return CAST(Value, file);
    FE

    DEF_CLASS_(files_out, File)
}

void Files::initFunctions(){
    UNARY_F(open)
}

void Files::initClasses(){
    SET_CLASS_(files_f, File)
}
