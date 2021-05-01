// [[not imported module]]
#include "files.h"
#include "../Lib/functions.h"
#include "../Lib/variables.h"
#include "../Value/nullvalue.h"
#include "../Value/numbervalue.h"
#include "../Value/stringvalue.h"
#include "../Exception/argumentsmismatchexception.h"
#include <fstream>
#include <iostream>

using namespace SlavaScript::lang;
using namespace SlavaScript::modules::files_f;
using SlavaScript::modules::Files;
using SlavaScript::exceptions::ArgumentsMismatchException;

namespace SlavaScript{ namespace modules{ namespace files_out{
    std::fstream file;
    bool bad = true;
}}}

namespace SlavaScript{ namespace modules{ namespace files_f{
    CREATE_FUNCTION(fopen)
        if (values.size() != 1) throw new ArgumentsMismatchException("One arguments expected");
        files_out::file.open(values[0] -> asString());
        if (!files_out::file){
            files_out::bad = false;
            return NumberValue::M_ONE;
        }
        files_out::bad = false;
        return NumberValue::ZERO;
    });

    CREATE_FUNCTION(fclose)
        if (values.size() != 0) throw new ArgumentsMismatchException("Zero arguments expected");
        files_out::file.close();
        return NullValue::NULL_;
    });

    CREATE_FUNCTION(readline)
        if (values.size() != 0) throw new ArgumentsMismatchException("Zero arguments expected");
        std::string line;
        if (files_out::file) std::getline(files_out::file, line);
        SH_RET(StringValue, line);
    });

    CREATE_FUNCTION(writeline)
        if (values.size() != 1) throw new ArgumentsMismatchException("One arguments expected");
        if (files_out::file && files_out::file.tellg() < files_out::file.end) files_out::file << values[0] -> asString();
        else if (!files_out::bad){
            std::cout << "Here\n";
            files_out::file.seekg(0, files_out::file.beg);
            files_out::file << values[0] -> asString();
        }
        else return NumberValue::M_ONE;
        return NumberValue::ZERO;
    });
}}}

void Files::initFunctions(){
    Functions::set("fopen", files_f::fopen);
    Functions::set("fclose", files_f::fclose);
    Functions::set("readline", readline);
    Functions::set("writeline", writeline);
}

