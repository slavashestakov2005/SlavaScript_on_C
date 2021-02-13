#ifndef CLASSDECLARATIONS_H_INCLUDED
#define CLASSDECLARATIONS_H_INCLUDED

#include <map>
#include "../Statement/classdeclarationsstatement.h"

namespace SlavaScript{ namespace lang{
    class ClassDeclarationsScope{
    private:
        std::map<std::string, ClassDeclarationsStatement*> declarations;
    public:
        void start();
        std::map<std::string, ClassDeclarationsStatement*> getScope();
        bool isExists(std::string key);
        /** @return  throw: UnknownClassException*. */
        ClassDeclarationsStatement* get(std::string key);
        void set(std::string key, ClassDeclarationsStatement* classDef);
    };

    class ClassDeclarations{
    private:
        static std::vector<ClassDeclarationsScope> scope;
    public:
        static void init();
        static void start();
        static std::map<std::string, ClassDeclarationsStatement*> getScope();
        static bool isExists(std::string key);
        static ClassDeclarationsStatement* get(std::string key);
        static void set(std::string key, ClassDeclarationsStatement* classDef);
        //static void print();
        static void pushScope();
        static void popScope();
        static void copyScope();
    };
}}

#endif // CLASSDECLARATIONS_H_INCLUDED
