#include "utils.h"

namespace SlavaScript::lang{
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
}
