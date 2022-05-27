#ifndef FILESYSTEM_H_INCLUDED
#define FILESYSTEM_H_INCLUDED

#include <string>

namespace SlavaScript::lang::FS {
    void setApplicationPath(std::string);
    void writeToCache(std::string, std::string);
    std::string readFromCache(std::string);
    std::string read(std::string);
    void cdCacheAndCall(std::string);
}

#endif // FILESYSTEM_H_INCLUDED
