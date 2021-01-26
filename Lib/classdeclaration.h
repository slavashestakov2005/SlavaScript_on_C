#ifndef CLASSDECLARATION_H_INCLUDED
#define CLASSDECLARATION_H_INCLUDED

#include <map>
#include "../Statement/classdeclarationsstatement.h"

namespace SlavaScript{ namespace lang{
    class ClassDeclaration{
    private:
        static std::map<std::string, ClassDeclarationsStatement*> declarations;
    public:
        static void clear();
        static bool isExists(std::string key);
        /** @return  throw: UnknownClassException*. */
        static ClassDeclarationsStatement* get(std::string key);
        static void set(std::string key, ClassDeclarationsStatement* classDef);
    };
}}

#endif // CLASSDECLARATION_H_INCLUDED
