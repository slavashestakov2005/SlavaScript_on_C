#include <sstream>

#include <Lib/utils.h>


using namespace SlavaScript::lang;
using SlavaScript::exceptions::ArgumentsMismatchException;
using SlavaScript::exceptions::TypeException;


namespace SlavaScript::lang {
    CMP(std::string) {
        CHECK(a.size(), b.size());
        int sz = a.size();
        for (int i = 0; i < sz; ++i) CHECK(a[i], b[i]);
        return std::strong_ordering::equal;
    }

    void argsCount(std::vector<int> expected, int got) {
        bool ok = false;
        for (int val : expected) if (val == got) { ok = true; break; }
        if (!ok) {
            int sz = expected.size();
            std::ostringstream os;
            for (int i = 0; i < sz - 1; ++i) os << expected[i] << ", ";
            os << expected.back();
            throw ArgumentsMismatchException(os.str(), got);
        }
    }

    void argsCount(int a, int got) {
        argsCount(std::vector{a}, got);
    }

    void argsCount(int a, int b, int got) {
        argsCount(std::vector{a, b}, got);
    }

    void argsCountLtEq(int expected, int got) {
        if (got < expected) {
            std::ostringstream os;
            os << ">= " << expected;
            throw ArgumentsMismatchException(os.str(), got);
        }
    }

    void argType(std::vector<Values> expected, std::shared_ptr<Value> got, std::string info) {
        Values type = got -> type();
        bool ok = false;
        for (Values val : expected) if (val == type) { ok = true; break; }
        if (!ok) {
            int sz = expected.size();
            std::ostringstream os;
            for (int i = 0; i < sz - 1; ++i) os << getValueName(expected[i]) << ", ";
            os << getValueName(expected.back());
            throw TypeException(os.str(), getValueName(type), info);
        }
    }

    void argType(Values a, std::shared_ptr<Value> got, std::string info) {
        argType(std::vector{a}, got);
    }

    void argType(Values a, Values b, std::shared_ptr<Value> got, std::string info) {
        argType(std::vector{a, b}, got);
    }
}
