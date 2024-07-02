#include <iostream>
#include <vector>
#include "Run/start.h"
#include "Run/repl.h"
#include "Run/path.h"
#include "Compiler/compiler.h"

using namespace std;
using namespace SlavaScript::lang;

/**
    1.  ��� import ���������� ����� �������� ��������������
    2.  ��� ���������� ��������������� ��������� ��� ������� ������������� ����������
**/

namespace{
    const int N = 14;
    string mas[N] = {
        "-f", "--file",
        "-r", "--repl",
        "-a", "--showast",
        "-t", "--showtokens",
        "-h", "--history",
        "-m", "--showtime",
        "-c", "--compile",
    };
}

int main(int argc, char* arg[]){
    setlocale(LC_CTYPE, "rus");
    vector<string> argv;
    for(int i = 0; i < argc; ++i) argv.push_back(arg[i]);
    cout << "SlavaScript version 1.2.0" << endl;
    Path::setCommandArguments(argv);
    //for(int i = 0; i < argc; ++i) cout << "\"" << argv[i] << "\"" << endl;
    if (argc == 1){
        cout << "Usage: slavascript [options]" << endl;
        cout << "  options:" << endl;
        cout << "    -f, --file [input]     Run program file. Required." << endl;
        cout << "    -r, --repl             Enter to a REPL mode" << endl;
        //cout << "    -l, --lint             Find bugs in code" << endl;
        //cout << "    -o N, --optimize N     Perform optimization with N passes" << endl;
        //cout << "    -b, --beautify         Beautify source code" << endl;
        cout << "    -a, --showast          Show AST of program" << endl;
        cout << "    -t, --showtokens       Show lexical tokens" << endl;
        cout << "    -h, --history          Show SlavaScript's history" << endl;
        cout << "    -m, --showtime         Show elapsed time of parsing and execution" << endl;
        cout << "    -c, --compile [input]  Compile program file. Required." << endl;
    }
    else if (argc == 3 && (argv[1] == "-c" || argv[1] == "--compile")) SlavaScript::compiler::Compiler::create_compiler(argv[2]);
    else{
        bool repl = false;
        bool his = false;
        for(int i = 1; (!repl || !his) && i < argc; ++i){
            if (argv[i] == "-r" || argv[i] == "--repl") repl = true;
            if (argv[i] == "-h" || argv[i] == "--history") his = true;
        }
        if (repl){
            if (argc != 2) cout << "����������� ��������� ��� ����� � ������������ �����" << endl;
            else Repl::start();
        }
        else if(his){
            if (argc != 2) cout << "����������� ��������� ��� ����� � ����� �������" << endl;
            else{
                cout << endl << endl;
                cout << "�� ����� � ����� ������� ����� SlavaScript" << endl;
                cout << "    � ������ � 30 ������� 2019 �� 11 ������ 2020 SlavaScript ��������� ����������" << endl;
                cout << "    ���������� �� � ������� �������� �������..." << endl;
                cout << "    �������� SlavaScript ��������� ��� Notepad++" << endl;
                cout << "    5 ������:" << endl;
                cout << "\t1. ����� ��������� ������� �������� ������� ������ ������� ���� ����������" << endl;
                cout << "\t2. SlavaScript ����� �������� � ������" << endl;
                cout << "    �������� ������������� ����� � ����..." << endl;
                cout << "\t1. ��� �������������� ���� ����� ��������" << endl;
                cout << "\t2. ��-���� ���� ��������� ������ � ���������" << endl;
                cout << "\t3. ���� ��������� �������" << endl;
                cout << "\t4. ��� ������ ������ �������������� Visitor" << endl;
                cout << "\t5. ��������� ������ std, draw � math" << endl;
                cout << "    11 ������:" << endl;
                cout << "\t1. ����� ���� ����������" << endl;
                cout << "\t2. � ���������� ��������� ������" << endl;
                cout << "\t3. ���������� ������ ��������� s++ �����" << endl;
                cout << "\t4. ���� ������� ������ 1.0.0" << endl;
                cout << "    12 ������:" << endl;
                cout << "\t1. ��������� function � map ��� �������� � ����������" << endl;
                cout << "\t2. ��� ������ return ����� ������������ =" << endl;
                cout << "\t3. �������� �������� ����� �������" << endl;
                cout << "\t4. ���� ������� ������ 1.1.0" << endl;
                cout << "    14 ������:" << endl;
                cout << "\t1. � ������ std �������� foreach" << endl;
                cout << "    16 ������:" << endl;
                cout << "\t1. ��������� �� ����������� - ����� ��������� )" << endl;
                cout << "    17 ������:" << endl;
                cout << "\t1. �������� foreach �� array � map" << endl;
                cout << "\t2. �������� ������ types" << endl;
                cout << "    22 ������:" << endl;
                cout << "\t1. ���������� ������ ����������" << endl;
                cout << "\t2. ��������� ������� len � ������ std" << endl;
                cout << "\t3. ���� �� ��������� map-� �� ������" << endl;
                cout << "    29 ������:" << endl;
                cout << "\t1. ���������� ������ map, � ������ ��� ��������" << endl;
                cout << "\t2. �������� println" << endl;
                cout << "    31 ������:" << endl;
                cout << "\t1. �������� ������ functional" << endl;
                cout << "\t2. ������������ �������� ������ � map ����� �����, �� �� ��� �� ��������" << endl;
                cout << "\t3. ���� ������� �������� ����� �������� array ��� map, �� ���������" << endl;
                cout << "    1 �������:" << endl;
                cout << "\t1. � ������ functional ��������� ������� flatmap" << endl;
                cout << "\t2. ���� ������� ������� ��������� ������. � ����� ����� �����." << endl;
                cout << "    2 �������:" << endl;
                cout << "\t1. �������� ������ chemistry" << endl;
                cout << "\t2. ��������� std::sort � functional::sortby" << endl;
                cout << "\t3. ��������� ������� ��� ������ �� ��������" << endl;
                cout << "\t4. SlavaScript ���� ��������� ������ - � ��� �������� input()" << endl;
                cout << "    3 �������:" << endl;
                cout << "\t1. ������ ������ ��� ����������, � ���� �� ��� ������ ������ 3 �� 5" << endl;
                cout << "\t2. ���� ������ ��������� ������������ �� �����" << endl;
                cout << "    9 �������:" << endl;
                cout << "\t1. ������� ������� �������� ��������� ������� �� ���������" << endl;
                cout << "    11 �������:" << endl;
                cout << "\t1. ������������ ������ ����� expression" << endl;
                cout << "\t2. ���� ��� ���������� excepted �� expected" << endl;
                cout << "\t3. �������� ����� ���� ��������� ������" << endl;
                cout << "    13 �������:" << endl;
                cout << "\t1. ������� �������� ����������� ������. ������� ���������� ����������)" << endl;
                cout << "\t   ���� ������������ ��� ������� ������ swap � ������ ����������, �� ������ ��� 10000 ��������� - 1215 ��,\n\t      ����� 11,7 ��. � ���������� ������� ���� ��� ������ 1666 ��" << endl;
                cout << "\t   ��� �������, ��� ����� ������ ���������� �������� � array - ������������. ��� ����� �� �������." << endl;
                cout << "    15 �������:" << endl;
                cout << "\t1. ��� Double ��� �����. ������ ������ ���� ������������ Bignum" << endl;
                cout << "\t2. ������ ����� ���������� � ������� ����� ���� �������� � � ���������" << endl;
                cout << "\t3. � ������� ���������� 2 ������ ����� �������� ��������������� ����������" << endl;
                cout << "\t4. �������� ����� ������� ������ ���������" << endl;
                cout << "\t5. ��������� ����������� ������ � �������� ����� ���� � �����" << endl;
                cout << "    16 �������:" << endl;
                cout << "\t1. ����� ������� �� �������� �������" << endl;
                cout << "\t2. ��������� �� ��������� �����������" << endl;
                cout << "    17 �������:" << endl;
                cout << "\t1. ������ ������� �� 10 ������" << endl;
                cout << "    21 �������:" << endl;
                cout << "\t1. ��������� ��������" << endl;
                cout << "\t2. �������� ++ � -- � ����� ������� ��� ���� ����� ������" << endl;
                cout << "\t3. ������������ ������ ������ math" << endl;
                cout << "    22 �������:" << endl;
                cout << "\t1. ��������� � ��������������� �������� map ���������� 0" << endl;
                cout << "\t2. �������� ������ files, �� �� ������" << endl;
                cout << "\t3. �������� REPL" << endl;
                cout << "\t4. �������� functional::chain()" << endl;
                cout << "\t5. std::try � ���� �������, ������� ����� ���, ���� = ������������, ���������� �� ��� ������������ � �� �������� ����� ��" << endl;
                cout << "    23 �������:" << endl;
                cout << "\t1. �������� ��� ������ Null" << endl;
                cout << "    26 �������:" << endl;
                cout << "\t1. ���������� ����-���� ������" << endl;
                cout << "    27 �������:" << endl;
                cout << "\t1. ���� ����� ������ ������ draw, ��� ���� �� ��������" << endl;
                cout << "    29 �������:" << endl;
                cout << "\t1. ��������� try, catch, throw" << endl;
                cout << "    2 �����:" << endl;
                cout << "\t1. ��������� vars, funcs, source, help � REPL" << endl;
                cout << "    26 ������ 2021:" << endl;
                cout << "\t1. ������ ����� ����������� �� GitHub";
                cout << "   ����� �������� :" << endl;
                cout << "\t1.   +\t����� ������� �� �������� �������" << endl;
                cout << "\t2.   +\t��������� �� ��������� �����������" << endl;
                cout << "\t3.   -\t����� �������� ��� ������������ ��������� statement � expression" << endl;
                cout << "\t4.   -\t�������� �������� ����� ��������� (����������������� ������������)" << endl;
                cout << "\t5. ����� ����������� ������ (date, files)" << endl;
                cout << "\t6. �� ������ ACMP ����� Bignum ����������� �����" << endl;
                cout << "\t7. �������� ������ files, ������ � �������" << endl;
                cout << "\t8.   +\t������� ��� ������ � array" << endl;
                cout << "\t9.   +\t���������� ������. �������� ++" << endl;
                cout << "\t10. �������� ���-�� ��� �������" << endl;
                cout << "\t11.  +\t���������� �������� � map ����� =" << endl;
                cout << "\t12. �������� beautify" << endl;
                cout << "\t12. �������� help in modules (name.__doc__ ? )" << endl;
                cout << "\t12. ������ math ������ ��������� ��� ������� � ���������� (������� atan2)" << endl;
                cout << "\t13. ���� ����� �� ��������� �� SFML, �� ����� �������� ��� �������" << endl;
                cout << "\t14.  +\t�������� REPL" << endl;
                cout << "\t15. �������� ������� � ������ �������� ���������" << endl;
                cout << "\t16. ����������� �������" << endl;
                cout << "    ������� ������, ��� ���� � ���������� ����� �����������" << endl;
            }
        }
        else{
            bool a = false, t = false, time = false;
            std::string path;
            for(int i = 1; i < argc; ++i){
                if (argv[i] == "-a" || argv[i] == "--ahowast"){
                    if (a){
                        cout << "����� ������ ���� ��� ������ AST" << endl;
                        return 0;
                    }
                    a = true;
                }
                else if (argv[i] == "-t" || argv[i] == "--ahowtokens"){
                    if (t){
                        cout << "����� ������ ���� ��� ������ �������" << endl;
                        return 0;
                    }
                    t = true;
                }
                else if (argv[i] == "-f" || argv[i] == "--file"){
                    if (i == argc - 1){
                        cout << "��� �������� �����" << endl;
                        return 0;
                    }
                    bool found = false;
                    ++i;
                    for(int j = 0; !found && j < N; ++j){
                        if (mas[j] == argv[i]) found = true;
                    }
                    if (found){
                        cout << "��� ����� ����� ����������� ���" << endl;
                        return 0;
                    }
                    else if (path != ""){
                        cout << "������ ������ �������� �����";
                        return 0;
                    }
                    path = argv[i];
                }
                else if (argv[i] == "-m" || argv[i] == "--showtime"){
                    if (time){
                        cout << "����� ������ ���� ��� ������ ������� ������" << endl;
                        return 0;
                    }
                    time = true;
                }
                else if (i == 1) path = argv[i];
                else{
                    cout << "����������� ���������";
                    return 0;
                }
            }
            try{
                Path::initContainers();
                Start start(path);
                start.start();
                if (a) start.printAST();
                if (t) start.printTokens();
                if (time) start.printWorkTime();
            }
            catch(...) { cout << "exception :-("; }
        }
    }
    system("pause");
    return 0;
}
