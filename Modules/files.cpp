// [[not imported module]]
#include "files.h"
#include "../Lib/functions.h"
#include "../Lib/variables.h"
#include "../Value/value.h"
#include "../Value/nullvalue.h"
#include "../Value/numbervalue.h"
#include "../Value/stringvalue.h"
#include "../Value/functionvalue.h"
#include "../Value/classmodulevalue.h"
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

namespace SlavaScript{ namespace modules{ namespace files_out{
    class FileValue : public ClassModuleValue{
    public:
        std::string name;
        std::fstream file;
        bool bad;
        FileValue(std::string name) : name(name){
            file.open(Path::getPath() + name);
            bad = !file;
        }
        std::shared_ptr<Value> copy(){
            return SHARE(FileValue, name);
        }
        operator std::string() { return "<file=\"" + name + "\">"; }
        ~FileValue(){}
        std::shared_ptr<Value> accessDot(std::shared_ptr<Value> property);
    };

    CLASS_MODULE_FUNCTION(Close, FileValue, file)
        if (values.size()) throw new ArgumentsMismatchException("Zero arguments expected");
        file -> file.close();
        return NullValue::NULL_;
    CMFE

    CLASS_MODULE_FUNCTION(Read, FileValue, file)
        file -> file.seekg(0, file -> file.beg);
        std::stringstream str;
        str << file -> file.rdbuf();
        SH_RET(StringValue, str.str());
    CMFE

    CLASS_MODULE_FUNCTION(ReadLine, FileValue, file)
        if (values.size() != 0) throw new ArgumentsMismatchException("Zero arguments expected");
        std::string line;
        if (file -> file) std::getline(file -> file, line);
        SH_RET(StringValue, line);
    CMFE

    CLASS_MODULE_FUNCTION(WriteLine, FileValue, file)
        if (values.size() != 1) throw new ArgumentsMismatchException("One arguments expected");
        if (file -> file && file -> file.tellg() < file -> file.end) file -> file << values[0] -> asString();
        else if (!file -> bad){
            file -> file.seekg(0, file -> file.beg);
            file -> file << values[0] -> asString();
        }
        else return NumberValue::M_ONE;
        return NumberValue::ZERO;
    CMFE

    std::shared_ptr<Value> FileValue::accessDot(std::shared_ptr<Value> property){
        std::string prop = property -> asString();
        if (bad) throw new TypeException("Cannot use DOT for not opened file");
        if (prop == "close") SH_RET(FunctionValue, new Close(this));
        if (prop == "read") SH_RET(FunctionValue, new Read(this));
        if (prop == "read_line") SH_RET(FunctionValue, new ReadLine(this));
        if (prop == "write_line") SH_RET(FunctionValue, new WriteLine(this));
        throw new UnknownPropertyException(prop);
    }
}}}

namespace SlavaScript{ namespace modules{ namespace files_f{
    CREATE_FUNCTION(open)
        if (values.size() != 1) throw new ArgumentsMismatchException("One arguments expected");
        std::shared_ptr<files_out::FileValue> file = SHARE(files_out::FileValue, values[0] -> asString());
        if (file -> bad) return NumberValue::M_ONE;
        return CAST(Value, file);
    FE
}}}

void Files::initFunctions(){
    UNARY_F(open)
}
