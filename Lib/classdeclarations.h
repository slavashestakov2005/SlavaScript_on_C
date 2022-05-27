#ifndef CLASSDECLARATIONS_H_INCLUDED
#define CLASSDECLARATIONS_H_INCLUDED

#include <map>
#include "../Statement/classdeclarationsstatement.h"

namespace SlavaScript::lang{
    struct NamedValue;

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
        void erase(std::string key);
        ClassDeclarationsStatement* save(std::string key);
        void restore(NamedValue named);
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
        static void erase(std::string key);
        //static void print();
        static ClassDeclarationsStatement* save(std::string key);
        static void restore(NamedValue named);
        static void pushScope();
        static void popScope();
        static void copyScope();
    };
}

#endif // CLASSDECLARATIONS_H_INCLUDED
