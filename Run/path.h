#ifndef PATH_H_INCLUDED
#define PATH_H_INCLUDED

#include <string>
#include <vector>
#include "../Value/arrayvalue.h"

namespace SlavaScript::lang{
    class Path{
    private:
        static std::vector<std::string> pathes;
        static bool import;
        static std::shared_ptr<ArrayValue> arguments;
    public:
        static void setPath(std::string path);
        static std::string getPath();
        static void popPath();
        static bool getImpoted();
        static void setImpoted(bool imp);
        static void initContainers();
        static void setCommandArguments(std::vector<std::string> argv);
        static std::shared_ptr<ArrayValue> getCommandArguments();
    };
}

#endif // PATH_H_INCLUDED
