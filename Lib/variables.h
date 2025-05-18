#pragma once

#include <map>
#include <vector>

#include <Value/value.h>


namespace SlavaScript::lang {
    struct NamedValue;

    class VariablesScope {
    private:
        std::map<std::string, std::shared_ptr<Value>> variables;
        std::vector<std::map<std::string, std::shared_ptr<Value>>> vec;
    public:
        void start();
        void push();
        void pop();
        std::map<std::string, std::shared_ptr<Value>> getScope();
        bool isExists(std::string key);
        std::shared_ptr<Value> get(std::string key);
        void set(std::string key, std::shared_ptr<Value> value);
        void erase(std::string key);
        void print();
        std::shared_ptr<Value> save(std::string key);
        void restore(NamedValue named);
    };

    class Variables {
    private:
        static std::vector<VariablesScope> scope;
    public:
        static void init();
        static void start();
        static void push();
        static void pop();
        static std::map<std::string, std::shared_ptr<Value>> getScope();
        static bool isExists(std::string key);
        static std::shared_ptr<Value> get(std::string key);
        static void set(std::string key, std::shared_ptr<Value> value);
        static void erase(std::string key);
        static void print();
        static std::shared_ptr<Value> save(std::string key);
        static void restore(NamedValue named);
        static void pushScope();
        static void popScope();
        static void copyScope();
    };
}
