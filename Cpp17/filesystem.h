#ifndef __FILESYSTEM_H__
#define __FILESYSTEM_H__

#include <string>
#define DLL  __declspec(dllexport)

namespace SlavaScript{ namespace Cpp17{ namespace FS{
    void DLL setApplicationPath(std::string);
    void DLL writeToCache(std::string, std::string);
    std::string DLL readFromCache(std::string);
    std::string DLL read(std::string);
    void DLL cdCacheAndCall(std::string);
}}}

#endif // __FILESYSTEM_H__
