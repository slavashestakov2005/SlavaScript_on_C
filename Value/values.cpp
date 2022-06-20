#include "values.h"

using namespace SlavaScript::lang;

namespace {
    std::string mas[] = {
        "Bool", "Number", "String", "Array", "Map", "Null", "Function", "Object", "Class", "Integration"
    };
}

namespace SlavaScript::lang{
    std::string getValueName(Values value){
        return mas[(int) value];
    }

    CMP(int){
        if (a < b) return -1;
        if (a > b) return 1;
        return 0;
    }

    CMP(std::string){
        CHECK(a.size(), b.size());
        int sz = a.size();
        for(int i = 0; i < sz; ++i) CHECK(a[i], b[i]);
        return 0;
    }

    CMP(Values){
        RCHECK(int(a), int(b));
    }
}
