#include <filesystem>
#include <fstream>

#include <Lib/filesystem.h>


namespace fs = std::filesystem;
using namespace SlavaScript::lang;


namespace {
    fs::path appPath;
    std::string strPath;
}


std::string convert(std::wstring w) {
    using convert_type = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_type, wchar_t> converter;
    return converter.to_bytes(w);
}

std::wstring convert(std::string s) {
    using convert_type = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_type, wchar_t> converter;
    return converter.from_bytes(s);
}

void FS::setApplicationPath(std::string s) {
    appPath = fs::path(s);
    appPath = appPath.parent_path();
    strPath = s;
    while (!strPath.empty() && strPath.back() != '/' && strPath.back() != '\\') strPath.pop_back();
}

void FS::writeToCache(std::string file, std::string data) {
    fs::path path(file);
    path = appPath / "cache" / path;
    std::ofstream fout(path);
    fout << data;
    fout.close();
}

std::string FS::readFromCache(std::string file) {
    fs::path path(file);
    path = appPath / "cache" / path;
    std::ifstream f(path);
    f.seekg(0, f.beg);
    std::stringstream ss;
    ss << f.rdbuf();
    return ss.str();
}

std::string FS::read(std::string file) {
    fs::path path(file);
    std::ifstream f(path);
    std::stringstream ss;
    ss << f.rdbuf();
    return ss.str();
}

void FS::cdCacheAndCall(std::string command) {
    std::string s = "cd " + strPath + "cache && " + command;
    system(s.c_str());
}
