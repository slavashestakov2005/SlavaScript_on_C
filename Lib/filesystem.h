#pragma once

#include <string>


namespace SlavaScript::lang::FS {
    void setApplicationPath(std::string);
    void writeToCache(std::string, std::string);
    std::string readFromCache(std::string);
    std::string read(std::string);
    void cdCacheAndCall(std::string);
}
