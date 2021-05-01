#include "integrationvalue.h"
#include "../Exception/typeexception.h"
#include "functionvalue.h"
#include "stringvalue.h"
#include "nullvalue.h"
#include "../Exception/argumentsmismatchexception.h"
#include "../Exception/unknownpropertyexception.h"
#include <fstream>

using namespace SlavaScript::lang;
using SlavaScript::exceptions::TypeException;
using SlavaScript::exceptions::UnknownPropertyException;
using SlavaScript::exceptions::ArgumentsMismatchException;


namespace{
    std::string mas[] = {"0", "1", "2", "3", "4"};
    int COUNT = 0;
    class Get : public Function {
    private:
        std::string start, finish;
    public:
        Get(std::string start, std::string finish) : start(start), finish(finish) {}
        std::shared_ptr<Value> execute(std::vector<std::shared_ptr<Value>> values){
           if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
           if (values[0] -> type() != Values::STRING) throw new TypeException("String expected in first argument");
           std::string filename = start + "_" + mas[COUNT++] + "." + finish;
           std::ofstream fout(filename);
           fout << "import " << start << "\n";
           fout << "with open('out.txt', 'w') as f:\n";
           fout << "\tf.write(str(" << start << "." << values[0] -> asString() << "))\n";
           fout.close();
           system(("py " + filename).c_str());
           std::ifstream fin("out.txt");
           std::string answer;
           while(!fin.eof()){
                getline(fin, filename);
                answer += filename + "\n";
           }
           fin.close();
           return std::make_shared<StringValue>(answer);
           /// return new StringValue(str);
        }
    };
}



std::shared_ptr<Value> IntegrationValue::accessDot(std::shared_ptr<Value> property){
    std::string prop = property -> asString();
    if (prop == "get") return std::make_shared<FunctionValue>(new Get(fileNameBegin, fileNameEnd));
    throw new UnknownPropertyException(prop);
}

double IntegrationValue::asDouble(){
    throw new TypeException("Cannot cast integration to double");
}

std::string IntegrationValue::asString(){
    throw new TypeException("Cannot cast integration to string");
}

bool IntegrationValue::asBool(){
    throw new TypeException("Cannot cast integration to bool");
}

Bignum IntegrationValue::asBignum(){
    throw new TypeException("Cannot cast integration to number");
}

Values IntegrationValue::type() const{
    return Values::INTEGRATION;
}

IntegrationValue::operator std::string(){
    return "null";
}

bool SlavaScript::lang::operator==(IntegrationValue const& a, IntegrationValue const& b){
    return a.fileNameBegin == b.fileNameBegin;
}

bool SlavaScript::lang::operator!=(IntegrationValue const& a, IntegrationValue const& b){
    return !(a == b);
}

bool SlavaScript::lang::operator<(IntegrationValue const& a, IntegrationValue const& b){
    return a.fileNameBegin < b.fileNameBegin;
}

bool SlavaScript::lang::operator<=(IntegrationValue const& a, IntegrationValue const& b){
    return !(a > b);
}

bool SlavaScript::lang::operator>(IntegrationValue const& a, IntegrationValue const& b){
    return b < a;
}

bool SlavaScript::lang::operator>=(IntegrationValue const& a, IntegrationValue const& b){
    return !(a < b);
}
