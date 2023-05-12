#include "integrationvalue.h"
#include "../Exception/exceptions.h"
#include "../Lib/filesystem.h"
#include "../Lib/function.h"
#include "../Lib/utils.h"

using namespace SlavaScript::lang;
using SlavaScript::exceptions::CastException;
using SlavaScript::exceptions::UnknownPropertyException;


namespace{
    std::string mas[] = {"0", "1", "2", "3", "4"};
    int COUNT = 0;
    class Get : public Function {
    private:
        std::string start, finish;
    public:
        Get(std::string start, std::string finish) : start(start), finish(finish) {}
        std::shared_ptr<Value> execute(std::vector<std::shared_ptr<Value>> values){
            argsCount(1, values.size());
            argType(Values::STRING, values[0]);
            std::string filename = start + "_" + mas[COUNT++] + "." + finish;
            FS::writeToCache(filename, "import " + start + "\n"
                                 "with open('out.txt', 'w') as f:\n"
                                 "\tf.write(str(" + start + "." + values[0] -> asString() + "))\n");
            FS::cdCacheAndCall("py \"" + filename + "\"");
            std::string answer = FS::readFromCache("out.txt");
            SH_RET(StringValue, answer);
        }
    };
}


IntegrationValue::IntegrationValue(std::string fileNameBegin, std::string fileNameEnd) : fileNameBegin(fileNameBegin), fileNameEnd(fileNameEnd) {}


std::shared_ptr<Value> IntegrationValue::copy(){
    return SHARE_2(IntegrationValue, fileNameBegin, fileNameEnd);
}

double IntegrationValue::asDouble(){
    throw CastException(Values::INTEGRATION, Values::NUMBER);
}

std::string IntegrationValue::asString(){
    throw CastException(Values::INTEGRATION, Values::STRING);
}

bool IntegrationValue::asBool(){
    throw CastException(Values::INTEGRATION, Values::BOOL);
}

Bignum IntegrationValue::asBignum(){
    throw CastException(Values::INTEGRATION, Values::NUMBER);
}

Values IntegrationValue::type() const{
    return Values::INTEGRATION;
}

IntegrationValue::operator std::string(){
    return "null";
}

std::shared_ptr<Value> IntegrationValue::getDot(std::shared_ptr<Value> property){
    std::string prop = property -> asString();
    if (prop == "get") SH_RET(FunctionValue, SHARE_2(Get, fileNameBegin, fileNameEnd));
    throw UnknownPropertyException(prop);
}


namespace SlavaScript::lang{
    CMP(IntegrationValue){
        RCHECK(a.fileNameBegin, b.fileNameBegin);
    }

    DEF_EQ(IntegrationValue)
}
