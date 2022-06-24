#ifndef CLASSES_H_INCLUDED
#define CLASSES_H_INCLUDED

#include "../Value/classvalue.h"
#include <map>

namespace SlavaScript::lang{
    struct NamedValue;

    class ClassesScope{
    private:
        std::map<std::string, std::shared_ptr<ClassValue>> declarations;
    public:
        void start();
        std::map<std::string, std::shared_ptr<ClassValue>> getScope();
        bool isExists(std::string key);
        /** @return  throw: UnknownClassException*. */
        std::shared_ptr<ClassValue> get(std::string key);
        void set(std::string key, std::shared_ptr<ClassValue> classDef);
        void erase(std::string key);
        std::shared_ptr<ClassValue> save(std::string key);
        void restore(NamedValue named);
    };

    class Classes{
    private:
        static std::vector<ClassesScope> scope;
    public:
        static void init();
        static void start();
        static std::map<std::string, std::shared_ptr<ClassValue>> getScope();
        static bool isExists(std::string key);
        static std::shared_ptr<ClassValue> get(std::string key);
        static void set(std::string key, std::shared_ptr<ClassValue> classDef);
        static void erase(std::string key);
        //static void print();
        static std::shared_ptr<ClassValue> save(std::string key);
        static void restore(NamedValue named);
        static void pushScope();
        static void popScope();
        static void copyScope();
    };
}

#endif // CLASSES_H_INCLUDED
