#include <cmath>
#include <map>

#include <Exception/exceptions.h>
#include <Lib/functions.h>
#include <Lib/utils.h>
#include <Modules/chemistry.h>
#include <Value/numbervalue.h>


using namespace SlavaScript::lang;
using namespace SlavaScript::modules::chemistry_f;
using SlavaScript::modules::Chemistry;
using SlavaScript::exceptions::LogicException;


namespace SlavaScript::modules::chemistry_out {
    struct Element {
        std::string name, russionRead, latinRead, electrons;
        double massa;
        int number, period, group;
        bool metal, mainGroup;
        Element(int number, std::string name, std::string russionRead, std::string latinRead, std::string electrons,
                 double massa, int period, int group, bool metal, bool mainGroup) : number(number), name(name), russionRead(russionRead),
                 latinRead(latinRead), electrons(electrons), massa(massa), period(period), group(group), metal(metal), mainGroup(mainGroup) {}
    };

    const int SizeOfTabel = 110;

    Element elements[SizeOfTabel] = {
        Element(1, "H", "водород", "аш", "1s1", 1.00797, 1, 1, false, true),
        Element(2, "He", "гелий", "гелий", "1s2", 4.0025, 1, 8, false, true),

        Element(3, "Li", "литий", "литий", "2s1", 6.939, 2, 1, true, true),
        Element(4, "Be", "берилий", "берилий", "2s2", 9.0122, 2, 2, true, true),
        Element(5, "B", "бор", "бор", "2s22p1", 10.811, 2, 3, false, true),
        Element(6, "C", "углерод", "цэ", "2s22p2", 12.01115, 2, 4, false, true),
        Element(7, "N", "азот", "эн", "2s22p3", 14.0067, 2, 5, false, true),
        Element(8, "O", "кислород", "о", "2s22p4", 15.9994, 2, 6, false, true),
        Element(9, "F", "фтор", "эф", "2s22p5", 18.9984, 2, 7, false, true),
        Element(10, "Ne", "неон", "неон", "2s22p6", 20.183, 2, 8, false, true),

        Element(11, "Na", "натрий", "натрий", "3s1", 22.9898, 3, 1, true, true),
        Element(12, "Mg", "магний", "магний", "3s2", 24.312, 3, 2, true, true),
        Element(13, "Al", "алюминий", "алюминий", "3s23p1", 25.9815, 3, 3, true, true),
        Element(14, "Si", "кремний", "силициум", "3s23p2", 28.086, 3, 4, false, true),
        Element(15, "P", "фосфор", "пэ", "3s23p3", 30.9738, 3, 5, false, true),
        Element(16, "S", "сера", "эс", "3s23p4", 32.064, 3, 6, false, true),
        Element(17, "Cl", "хлор", "хлор", "3s23p5", 35.453, 3, 7, false, true),
        Element(18, "Ar", "аргон", "аргон", "3s23p6", 39.948, 3, 8, false, true),

        Element(19, "K", "калий", "кэ", "4s1", 39.102, 4, 1, true, true),
        Element(20, "Ca", "кальций", "кальций", "4s2", 40.08, 4, 2, true, true),
        Element(21, "Sc", "скандий", "скандий", "3d14s2", 44.956, 4, 3, true, false),
        Element(22, "Ti", "титан", "титан", "3d24s2", 47.9, 4, 4, true, false),
        Element(23, "V", "ванадий", "ванадий", "3d34s2", 50.942, 4, 5, true, false),
        Element(24, "Cr", "хром", "хром", "3d54s1", 51.996, 4, 6, true, false),
        Element(25, "Mn", "марганец", "марганец", "3d54s2", 54.938, 4, 7, true, false),
        Element(26, "Fe", "железо", "ферум", "3d64s2", 55.847, 4, 8, true, false),
        Element(27, "Co", "кобальт", "кобальт", "3d74s2", 58.9332, 4, 8, true, false),
        Element(28, "Ni", "никель", "никель", "3d84s2", 58.71, 4, 8, true, false),

        Element(29, "Cu", "медь", "купрум", "3d104s1", 63.546, 4, 1, true, false),
        Element(30, "Zn", "цинк", "цинк", "3d104s2", 65.37, 4, 2, true, false),
        Element(31, "Ga", "галлий", "галлий", "4s24p1", 69.72, 4, 3, true, true),
        Element(32, "Ge", "германий", "германий", "4s24p2", 72.59, 4, 4, true, true),
        Element(33, "As", "мышьяк", "мышьяк", "4s24p3", 74.9216, 4, 5, false, true),
        Element(34, "Se", "селен", "селен", "4s24p4", 78.96, 4, 6, false, true),
        Element(35, "Br", "бром", "бром", "4s24p5", 79.904, 4, 7, false, true),
        Element(36, "Kr", "криптон", "криптон", "4s24p6", 83.8, 4, 8, false, true),

        Element(37, "Rb", "рубидий", "рубидий", "5s1", 85.47, 5, 1, true, true),
        Element(38, "Sr", "стронций", "стронций", "5s2", 87.62, 5, 2, true, true),
        Element(39, "Y", "иттрий", "иттрий", "4d15s2", 88.905, 5, 3, true, false),
        Element(40, "Zr", "цирконий", "йирконий", "4d25s2", 91.22, 5, 4, true, false),
        Element(41, "Nb", "ниобий", "ниобий", "4d45s1", 92.906, 5, 5, true, false),
        Element(42, "Mo", "молибден", "молибден", "4d55s1", 95.94, 5, 6, true, false),
        Element(43, "Tc", "технеций", "технеций", "4d55s2", 99, 5, 7, true, false),
        Element(44, "Ru", "рутений", "рутений", "4d75s1", 101.07, 5, 8, true, false),
        Element(45, "Rh", "родий", "родий", "4d85s1", 102.905, 5, 8, true, false),
        Element(46, "Pd", "палладий", "палладий", "4d105s0", 106.4, 5, 8, true, false),

        Element(47, "Ag", "серебро", "аргентум", "4d105s1", 107.868, 5, 1, true, false),
        Element(48, "Cd", "кадмий", "кадмий", "4d105s2", 112.4, 5, 2, true, false),
        Element(49, "In", "индий", "индий", "5s25p1", 114.82, 5, 3, true, true),
        Element(50, "Sn", "олово", "олово", "5s25p2", 118.69, 5, 4, true, true),
        Element(51, "Sb", "сурьма", "сурьма", "5s25p3", 121.75, 5, 5, true, true),
        Element(52, "Te", "теллур", "теллур", "5s25p4", 127.6, 5, 6, false, true),
        Element(53, "I", "иод", "иод", "5s25p5", 126.9044, 5, 7, false, true),
        Element(54, "Xe", "ксенон", "ксенон", "5s25p6", 131.3, 5, 8, false, true),

        Element(55, "Cs", "цезий", "цезий", "6s1", 132.905, 6, 1, true, true),
        Element(56, "Ba", "барий", "барий", "6s2", 137.34, 6, 2, true, true),
        Element(57, "La", "лантан", "лантан", "5d16s2", 138.81, 6, 3, true, false),
        /** лантаноиды **/
        Element(58, "Ce", "церий", "церий", "4f15d16s2", 140.12, 6, 3, true, false),
        Element(59, "Pr", "празеодим", "празеодим", "4f35d06s2", 140.907, 6, 3, true, false),
        Element(60, "Nd", "неодим", "неодим", "4f45d06s2", 144.24, 6, 3, true, false),
        Element(61, "Pm", "прометий", "прометий", "4f55d06s2", 145, 6, 3, true, false),
        Element(62, "Sm", "самарий", "самарий", "4f65d06s2", 150.35, 6, 3, true, false),
        Element(63, "Eu", "европий", "европий", "4f75d06s2", 151.96, 6, 3, true, false),
        Element(64, "Gd", "гадолиний", "гадолиний", "4f75d16s2", 157.25, 6, 3, true, false),
        Element(65, "Tb", "тербий", "тербий", "4f95d06s2", 158.924, 6, 3, true, false),
        Element(66, "Dy", "диспрозий", "диспрозий", "4f105d06s2", 162.50, 6, 3, true, false),
        Element(67, "Ho", "гольмий", "гольмий", "4f115d06s2", 164.930, 6, 3, true, false),
        Element(68, "Er", "эрбий", "эрбий", "4f125d06s2", 167.26, 6, 3, true, false),
        Element(69, "Tm", "тулий", "тулий", "4f135d06s2", 168.934, 6, 3, true, false),
        Element(70, "Yb", "иттербий", "иттербий", "4f145d06s2", 173.04, 6, 3, true, false),
        Element(71, "Lu", "лютеций", "лютеций", "4f145d16s2", 174.97, 6, 3, true, false),
        /** лантаноиды **/
        Element(72, "Hf", "гафний", "гафний", "4f145d26s2", 178.49, 6, 4, true, false),
        Element(73, "Ta", "тантал", "тантал", "4f145d36s2", 180.948, 6, 5, true, false),
        Element(74, "W", "вольфрам", "вольфрам", "4f145d46s2", 183.85, 6, 6, true, false),
        Element(75, "Re", "рений", "рений", "4f145d56s2", 186.2, 6, 7, true, false),
        Element(76, "Os", "осмий", "осмий", "4f145d66s2", 190.2, 6, 8, true, false),
        Element(77, "Ir", "иридий", "иридий", "4f145d76s2", 192.2, 6, 8, true, false),
        Element(78, "Pt", "платина", "платина", "5d96s1", 195.09, 6, 8, true, false),

        Element(79, "Au", "золото", "аурум", "5d106s1", 196.967, 6, 1, true, false),
        Element(80, "Hg", "ртуть", "гидраргирум", "5d106s2", 200.59, 6, 2, true, false),
        Element(81, "Tl", "таллий", "таллий", "6s26p1", 204.37, 6, 3, true, true),
        Element(82, "Pb", "свинец", "плюмбум", "6s26p2", 207.19, 6, 4, true, true),
        Element(83, "Bi", "висмут", "висмут", "6s26p3", 208.980, 6, 5, true, true),
        Element(84, "Po", "полоний", "полоний", "6s26p4", 210, 6, 6, true, true),
        Element(85, "At", "астат", "астат", "6s26p5", 210, 6, 7, false, true),
        Element(86, "Rn", "радон", "радон", "6s26p6", 222, 6, 8, false, true),

        Element(87, "Fr", "франций", "франций", "7s1", 223, 7, 1, true, true),
        Element(88, "Ra", "радий", "радий", "7s2", 226, 7, 2, true, true),
        Element(89, "Ac", "актиний", "актиний", "6d17s2", 227, 7, 3, true, false),
        /** актиноиды **/
        Element(90, "Th", "торий", "торий", "5f06d27s2", 232.038, 7, 3, true, false),
        Element(91, "Pa", "протактиний", "протактиний", "5f26d17s2", 231, 7, 3, true, false),
        Element(92, "U", "уран", "уран", "5f36d17s2", 238.03, 7, 3, true, false),
        Element(93, "Np", "нептуний", "нептуний", "5f46d17s2", 237, 7, 3, true, false),
        Element(94, "Pu", "плутоний", "плутоний", "5f66d07s2", 242, 7, 3, true, false),
        Element(95, "Am", "америций", "америций", "5f76d07s2", 243, 7, 3, true, false),
        Element(96, "Cm", "кюрий", "кюрий", "5f76d17s2", 247, 7, 3, true, false),
        Element(97, "Bk", "берклий", "берклий", "5f96d07s2", 247, 7, 3, true, false),
        Element(95, "Cf", "калифорний", "калифорний", "5f106d07s2", 249, 7, 3, true, false),
        Element(99, "Es", "эйнштейний", "эйнштейний", "5f116d07s2", 254, 7, 3, true, false),
        Element(100, "Fm", "фермий", "фермий", "5f126d07s2", 253, 7, 3, true, false),
        Element(101, "Md", "менделевий", "менделевий", "5f136d07s2", 256, 7, 3, true, false),
        Element(102, "No", "нобелий", "нобелий", "5f146d07s2", 255, 7, 3, true, false),
        Element(103, "Lr", "лоуренсий", "лоуренсий", "5f146d17s2", 257, 7, 3, true, false),
        /** актиноиды **/
        Element(104, "Rf", "разерфордий", "разерфордий", "5f146d27s2", 261, 7, 4, true, false),
        Element(105, "Db", "дубний", "дубний", "5f146d37s2", 262, 7, 5, true, false),
        Element(106, "Sg", "сиборгий", "сиборгий", "5f146d47s2", 263, 7, 6, true, false),
        Element(107, "Bh", "борий", "борий", "5f146d57s2", 262, 7, 7, true, false),
        Element(108, "Hs", "хассий", "хассий", "5f146d67s2", 265, 7, 8, true, false),
        Element(109, "Mt", "мейтнерий", "мейтнерий", "5f146d77s2", 266, 7, 8, true, false),
        Element(110, "Ds", "дармштадтий", "дармштадтий", "6d97s1", 271, 7, 8, true, false),
    };

    int get_element(std::string name) {
        for (int i = 0; i < SizeOfTabel; ++i) {
            if (elements[i].name == name) return i;
        }
        return -1;
    }

    std::map<std::string, int> correct(std::string str) {
        int pos = 0, index = 0, koeff = 0;
        std::string element;
        std::map<std::string, int> el;
        std::vector<std::string> inBracket;
        bool openParen = false;
        while (pos < str.size() && str[pos] >= '0' && str[pos] <= '9') {
            koeff *= 10;
            koeff += str[pos] - '0';
            ++pos;
        }
        if (!koeff) koeff = 1;
        if (koeff < 0) throw LogicException("Minus koefficient");
        el["_"] = koeff;
        while (pos < str.size()) {
            if (str[pos] >= '0' && str[pos] <= '9') {
                if (element == "") throw LogicException("Empty element");
                index *= 10;
                index += str[pos] - '0';
            } else if (str[pos] >= 'A' && str[pos] <= 'Z') {
                if (element != "") {
                    int finded = get_element(element);
                    if (finded == -1) throw LogicException("Bad element");
                    if (index == 0) index = 1;
                    el[element] += index;
                    if (openParen) inBracket.push_back(element);
                    index = 0;
                    element = "";
                }
                element += str[pos];
            } else if (str[pos] >= 'a' && str[pos] <= 'z') {
                if (element == "") throw LogicException("Bad element");
                element += str[pos];
            } else if (str[pos] == '(') {
                if (openParen) throw LogicException("Two open paren");
                openParen = true;
                if (element != "") {
                    int finded = get_element(element);
                    if (finded == -1) throw LogicException("Bad element");
                    if (index == 0) index = 1;
                    el[element] += index;
                    index = 0;
                    element = "";
                }
            } else if (str[pos] == ')') {
                if (!openParen) throw LogicException("Missing open paren");
                int finded = get_element(element);
                if (finded == -1) throw LogicException("Bad element");
                if (index == 0) index = 1;
                el[element] += index;
                inBracket.push_back(element);
                element = "";
                index = 0;
                ++pos;
                while (pos < str.size() && str[pos] >= '0' && str[pos] <= '9') { index *= 10; index += str[pos] - '0'; ++pos; }
                if (!index) index = 1;
                for (size_t i = 0; i < inBracket.size(); ++i) {
                    el[inBracket[i]] *= index;
                }
                index = 0;
                inBracket.clear();
            } else throw LogicException("Bad symbol");
            ++pos;
        }
        if (element != "") {
            int finded = get_element(element);
            if (finded == -1) throw LogicException("Bad element");
            if (index == 0) index = 1;
            el[element] += index;
        }
        return el;
    }

    double mr(std::string str) {
        std::map<std::string, int> element = correct(str);
        double m = 0;
        for (auto x : element) {
            int finded = get_element(x.first);
            m += elements[finded].massa * x.second;
        }
        return m * element["_"];
    }

    double omega(std::string substance, std::string el) {
        std::map<std::string, int> element = correct(substance);
        int index = 0;
        for (auto x : element) {
            if (x.first == el) {
                index = x.second;
                break;
            }
        }
        if (!index) throw LogicException(substance + " not contain a " + el);
        for (int i = 0; i < SizeOfTabel; ++i) {
            if (elements[i].name == el) return index * elements[i].massa / mr(substance);
        }
        return -1;
    }
}

namespace SlavaScript::modules::chemistry_f {
    CREATE_FUNCTION(electron)
        argsCount(1, values.size());
        argType(Values::STRING, values[0]);
        std::string str1 = CAST(StringValue, values[0]) -> asString();
        int finded = chemistry_out::get_element(str1);
        if (finded == -1) throw LogicException("First argument not element");
        SH_RET(NumberValue, chemistry_out::elements[finded].number);
    FE

    CREATE_FUNCTION(latin_read)
        argsCount(1, values.size());
        argType(Values::STRING, values[0]);
        std::string str1 = CAST(StringValue, values[0]) -> asString();
        int finded = chemistry_out::get_element(str1);
        if (finded == -1) throw LogicException("First argument not element");
        SH_RET(StringValue, chemistry_out::elements[finded].latinRead);
    FE

    CREATE_FUNCTION(mr)
        argsCount(1, values.size());
        argType(Values::STRING, values[0]);
        std::string str = CAST(StringValue, values[0]) -> asString();
        SH_RET(NumberValue, chemistry_out::mr(str));
    FE

    CREATE_FUNCTION(neutron)
        argsCount(1, values.size());
        argType(Values::STRING, values[0]);
        std::string str1 = CAST(StringValue, values[0]) -> asString();
        int finded = chemistry_out::get_element(str1);
        if (finded == -1) throw LogicException("First argument not element");
        SH_RET(NumberValue, round(chemistry_out::elements[finded].massa) - chemistry_out::elements[finded].number);
    FE

    CREATE_FUNCTION(omega)
        argsCount(2, values.size());
        argType(Values::STRING, values[0]);
        argType(Values::STRING, values[1]);
        std::string str1 = CAST(StringValue, values[0]) -> asString(), str2 = CAST(StringValue, values[1]) -> asString();
        int finded = chemistry_out::get_element(str1);
        if (finded == -1) throw LogicException("First argument not element");
        if (chemistry_out::mr(str2) == 0) throw LogicException("Bad second argument");
        SH_RET(NumberValue, chemistry_out::omega(str2, str1));
    FE

    CREATE_FUNCTION(russian_read)
        argsCount(1, values.size());
        argType(Values::STRING, values[0]);
        std::string str1 = CAST(StringValue, values[0]) -> asString();
        int finded = chemistry_out::get_element(str1);
        if (finded == -1) throw LogicException("First argument not element");
        SH_RET(StringValue, chemistry_out::elements[finded].russionRead);
    FE

    CREATE_FUNCTION(write)
        argsCount(1, values.size());
        argType(Values::STRING, values[0]);
        std::string str = CAST(StringValue, values[0]) -> asString();
        int finded = -1;
        for (int i = 0; i < chemistry_out::SizeOfTabel; ++i) {
            if (chemistry_out::elements[i].russionRead == str) finded = i;
        }
        if (finded == -1) throw LogicException("First argument not element");
        SH_RET(StringValue, chemistry_out::elements[finded].name);
    FE

    std::shared_ptr<Function> proton = electron;
}

void Chemistry::initFunctions() {
    MFUNC_UNARY(electron)
    MFUNC_UNARY(latin_read)
    MFUNC_UNARY(mr)
    MFUNC_UNARY(neutron)
    MFUNC_BINARY(omega)
    MFUNC_UNARY(proton)
    MFUNC_UNARY(russian_read)
    MFUNC_UNARY(write)
}
