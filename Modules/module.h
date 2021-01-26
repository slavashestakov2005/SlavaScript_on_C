#ifndef MODULE_H_INCLUDED
#define MODULE_H_INCLUDED

#include "../Lib/function.h"
#include "../Lib/functionmodule.h"

class BaseModule{
public:
    virtual void constants() = 0;
    virtual void functions() = 0;
};

template<class ModuleName>
class Module : public BaseModule{
public:
    virtual void constants(){ ModuleName::initConstants(); }
    virtual void functions(){ ModuleName::initFunctions(); }
    static void init(){
        ModuleName::initConstants();
        ModuleName::initFunctions();
    }
};

#endif // MODULE_H_INCLUDED
