#include "filesystem.h"
#include <filesystem>
#include <sstream>
#include <fstream>

namespace fs = std::filesystem;
using namespace SlavaScript::lang;

namespace{
    fs::path appPath;
    std::string strPath;

    std::string decode(std::string w){
        if (w.empty()) return w;
        std::string s;
        int i = 0;
        for(;i < w.size() - 1; ++i){
            int c = (unsigned char)w[i] * 256 + (unsigned char)w[i + 1];
            if (208 * 256 + 144 <= c && c <= 208 * 256 + 175) ++i, s += char(c - (208 * 256 + 144) - 64);
            else if (208 * 256 + 176 <= c && c <= 208 * 256 + 191) ++i, s += char(c - (208 * 256 + 176) - 32);
            else if (209 * 256 + 128 <= c && c <= 209 * 256 + 143) ++i, s += char(c - (209 * 256 + 128) - 16);
            else if (c == 208 * 256 + 129) ++i, s += char(-88);
            else if (c == 209 * 256 + 145) ++i, s += char(-72);
            else s += w[i];
        }
        if (i < w.size()) s += w[i];
        return s;
    }
}

std::string convert(std::wstring w){
    using convert_type = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_type, wchar_t> converter;
    return converter.to_bytes(w);
}

std::wstring convert(std::string s){
    using convert_type = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_type, wchar_t> converter;
    return converter.from_bytes(s);
}

void FS::setApplicationPath(std::string s){
    appPath = fs::path(s);
    appPath = appPath.parent_path();
    strPath = s;
    while(!strPath.empty() && strPath.back() != '/' && strPath.back() != '\\') strPath.pop_back();
}

void FS::writeToCache(std::string file, std::string data){
    fs::path path(file);
    path = appPath / "cache" / path;
    std::ofstream fout(path);
    fout << data;
    fout.close();
}

std::string FS::readFromCache(std::string file){
    fs::path path(file);
    path = appPath / "cache" / path;
    std::ifstream f(path);
    f.seekg(0, f.beg);
    std::stringstream ss;
    ss << f.rdbuf();
    return ss.str();
}

std::string FS::read(std::string file){
    fs::path path(file);
    std::ifstream f(path);
    std::stringstream ss;
    ss << f.rdbuf();
    return decode(ss.str());
}

void FS::cdCacheAndCall(std::string command){
    std::string s = "cd " + strPath + "cache && " + command;
    system(s.c_str());
}
