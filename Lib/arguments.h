#ifndef ARGUMENTS_H_INCLUDED
#define ARGUMENTS_H_INCLUDED

#include <vector>
#include "argument.h"

namespace SlavaScript{ namespace lang{
    class Arguments{
    private:
        std::vector<Argument> arguments;
        int requiredCount = 0;
        int arrayCount = 0;
    public:
        Arguments(){}
        void addRequired(std::string name);
        void addOptional(std::string name, Expression* expression);
        void addArrayArgument(std::string name);
        Argument get(int index);
        int getRequiredCount();
        int getArrayCount();
        int size();
        operator std::string();
    };
}}

#endif // ARGUMENTS_H_INCLUDED
