#include <iostream>
#include <vector>
#include "Run/start.h"
#include "Run/repl.h"
#include "Run/path.h"
#include "Compiler/compiler.h"

using namespace std;
using namespace SlavaScript::lang;

/**
    1.  Все import происходят перед запуском интерпритатора
    2.  При нахождение импортированной константы или функции выбрасывается исключение
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
            if (argc != 2) cout << "Неизвестный синтаксис для входа в динамический режим" << endl;
            else Repl::start();
        }
        else if(his){
            if (argc != 2) cout << "Неизвестный синтаксис для входа в режим истории" << endl;
            else{
                cout << endl << endl;
                cout << "Вы вошли в режим истории языка SlavaScript" << endl;
                cout << "    В период с 30 декабря 2019 по 11 января 2020 SlavaScript динамично развивался" << endl;
                cout << "    Начиналось всё с обратно польской нотации..." << endl;
                cout << "    Появился SlavaScript синтаксис для Notepad++" << endl;
                cout << "    5 января:" << endl;
                cout << "\t1. Когда появилось желание добавить функции первый вариант стал непригоден" << endl;
                cout << "\t2. SlavaScript начал писаться с начала" << endl;
                cout << "    Началось переписывание языка с нуля..." << endl;
                cout << "\t1. Код интерпретатора стал более логичным" << endl;
                cout << "\t2. Всё-таки была добавлена работа с функциями" << endl;
                cout << "\t3. Были добавлены массивы" << endl;
                cout << "\t4. Был внедрён шаблон проектирования Visitor" << endl;
                cout << "\t5. Появились модули std, draw и math" << endl;
                cout << "    11 января:" << endl;
                cout << "\t1. Вышел этот анализатор" << endl;
                cout << "\t2. У приложения появилась иконка" << endl;
                cout << "\t3. Приложение начало открывать s++ файлы" << endl;
                cout << "\t4. Язык получил версию 1.0.0" << endl;
                cout << "    12 января:" << endl;
                cout << "\t1. Добавлены function и map для хранения в переменных" << endl;
                cout << "\t2. Для записи return можно использовать =" << endl;
                cout << "\t3. Началось создание этого раздела" << endl;
                cout << "\t4. Язык получил версию 1.1.0" << endl;
                cout << "    14 января:" << endl;
                cout << "\t1. В модуль std добавлен foreach" << endl;
                cout << "    16 января:" << endl;
                cout << "\t1. Олимпиада по информатике - такая Олимпиада )" << endl;
                cout << "    17 января:" << endl;
                cout << "\t1. Добавлен foreach по array и map" << endl;
                cout << "\t2. Добавлен модуль types" << endl;
                cout << "    22 января:" << endl;
                cout << "\t1. Добавленны классы исключений" << endl;
                cout << "\t2. Добавлена функция len в модуль std" << endl;
                cout << "\t3. Тест на вложенные map-ы не прошёл" << endl;
                cout << "    29 января:" << endl;
                cout << "\t1. Исправлена работа map, и теперь они работают" << endl;
                cout << "\t2. Добавлен println" << endl;
                cout << "    31 января:" << endl;
                cout << "\t1. Добавлен модуль functional" << endl;
                cout << "\t2. Теоретически появился доступ к map через точку, но он мне не нравится" << endl;
                cout << "\t3. Была плпытка добавить вызов элемента array или map, но неудачная" << endl;
                cout << "    1 февраля:" << endl;
                cout << "\t1. В модуль functional добавлена функция flatmap" << endl;
                cout << "\t2. Была попытка фиксинг вчерашней ошибки. В итоге откат назад." << endl;
                cout << "    2 февраля:" << endl;
                cout << "\t1. Добавлен модуль chemistry" << endl;
                cout << "\t2. Добавлены std::sort и functional::sortby" << endl;
                cout << "\t3. Добавлены функции для работы со строками" << endl;
                cout << "\t4. SlavaScript стал настоящим языком - в нём появился input()" << endl;
                cout << "    3 февраля:" << endl;
                cout << "\t1. Прошёл первый тур математики, у меня на мой взгляд решено 3 из 5" << endl;
                cout << "\t2. Было начато написание документации по языку" << endl;
                cout << "    9 февраля:" << endl;
                cout << "\t1. Сегодня удалось добавить аргументы функций по умолчанию" << endl;
                cout << "    11 февраля:" << endl;
                cout << "\t1. Присваивание теперь стало expression" << endl;
                cout << "\t2. Кучу раз исправлено excepted на expected" << endl;
                cout << "\t3. Появился вывод всех найденных ошибок" << endl;
                cout << "    13 февраля:" << endl;
                cout << "\t1. Сегодня началась оптимизация памяти. Спасибо Станиславу Сергеевичу)" << endl;
                cout << "\t   Если использовать для очистки масива swap с пустым множеством, то расход для 10000 элементов - 1215 Мб,\n\t      иначе 11,7 Мб. В предудущих версиях этот код тратил 1666 Мб" << endl;
                cout << "\t   Мне кажется, что такой способ добавления элемента в array - нерационален. Это долго по времени." << endl;
                cout << "    15 февраля:" << endl;
                cout << "\t1. Тип Double был удалён. Теперь вместо него используется Bignum" << endl;
                cout << "\t2. Теперь имена переменных и функций могут буть длинными и с пробелами" << endl;
                cout << "\t3. С помощью добавления 2 теперь стало возможно переопределение операторов" << endl;
                cout << "\t4. Добавлен вывод времени работы программы" << endl;
                cout << "\t5. Добавлено подключение файлов с исходным кодом друг в друга" << endl;
                cout << "    16 февраля:" << endl;
                cout << "\t1. Вызов функции из элемента массива" << endl;
                cout << "\t2. Обращение ко вложенным контейнерам" << endl;
                cout << "    17 февраля:" << endl;
                cout << "\t1. Проект почищен на 10 файлов" << endl;
                cout << "    21 февраля:" << endl;
                cout << "\t1. Добавлена рекурсия" << endl;
                cout << "\t2. Добавлен ++ и -- в обоих версиях для всех типов данных" << endl;
                cout << "\t3. Востановлена работа модуля math" << endl;
                cout << "    22 февраля:" << endl;
                cout << "\t1. Обращение к несуществующиму элементу map возвращает 0" << endl;
                cout << "\t2. Добавлен модуль files, но он ужасен" << endl;
                cout << "\t3. Добавлен REPL" << endl;
                cout << "\t4. Добавлен functional::chain()" << endl;
                cout << "\t5. std::try и сапёр скинуты, улучшен вывод АСД, цель = оптимизаторы, посмотреть на два рефакторинга и со страницы будет всё" << endl;
                cout << "    23 февраля:" << endl;
                cout << "\t1. Добавлен тип данных Null" << endl;
                cout << "    26 февраля:" << endl;
                cout << "\t1. Исправлено чуть-чуть ошибок" << endl;
                cout << "    27 февраля:" << endl;
                cout << "\t1. Есть новая версия модуля draw, она тоже не работает" << endl;
                cout << "    29 февраля:" << endl;
                cout << "\t1. Добавлены try, catch, throw" << endl;
                cout << "    2 марта:" << endl;
                cout << "\t1. Добавлены vars, funcs, source, help в REPL" << endl;
                cout << "    26 января 2021:" << endl;
                cout << "\t1. Создан новый репозиторий на GitHub";
                cout << "   Нужно добавить :" << endl;
                cout << "\t1.   +\tВызов функции из элемента массива" << endl;
                cout << "\t2.   +\tОбращение ко вложенным контейнерам" << endl;
                cout << "\t3.   -\tМожно подумать над превращением некоторых statement в expression" << endl;
                cout << "\t4.   -\tВозможно добавить новый синтаксис (реструктуризующие присваивание)" << endl;
                cout << "\t5. Можно подабавлять модули (date, files)" << endl;
                cout << "\t6. По мнению ACMP класс Bignum неправильно делит" << endl;
                cout << "\t7. Добавить модуль files, работа с файлами" << endl;
                cout << "\t8.   +\tФункции для работы с array" << endl;
                cout << "\t9.   +\tПеределать модули. Добавить ++" << endl;
                cout << "\t10. Добавить что-то для роботов" << endl;
                cout << "\t11.  +\tДобавление элемента в map через =" << endl;
                cout << "\t12. Добавить beautify" << endl;
                cout << "\t12. Добавить help in modules (name.__doc__ ? )" << endl;
                cout << "\t12. Модуль math должен содержать все функции и правильные (тестить atan2)" << endl;
                cout << "\t13. Если никто не откажется от SFML, то нужно добавить все функции" << endl;
                cout << "\t14.  +\tУлучшить REPL" << endl;
                cout << "\t15. Добавить перевод в разных системах счисления" << endl;
                cout << "\t16. Расскрасить консоль" << endl;
                cout << "    Хочется верить, что язык в дальнейшем будет развиваться" << endl;
            }
        }
        else{
            bool a = false, t = false, time = false;
            std::string path;
            for(int i = 1; i < argc; ++i){
                if (argv[i] == "-a" || argv[i] == "--ahowast"){
                    if (a){
                        cout << "Более одного тэга для показа AST" << endl;
                        return 0;
                    }
                    a = true;
                }
                else if (argv[i] == "-t" || argv[i] == "--ahowtokens"){
                    if (t){
                        cout << "Более одного тэга для показа токенов" << endl;
                        return 0;
                    }
                    t = true;
                }
                else if (argv[i] == "-f" || argv[i] == "--file"){
                    if (i == argc - 1){
                        cout << "Нет входного файла" << endl;
                        return 0;
                    }
                    bool found = false;
                    ++i;
                    for(int j = 0; !found && j < N; ++j){
                        if (mas[j] == argv[i]) found = true;
                    }
                    if (found){
                        cout << "Для имени файла использован тэг" << endl;
                        return 0;
                    }
                    else if (path != ""){
                        cout << "Больше одного входного файла";
                        return 0;
                    }
                    path = argv[i];
                }
                else if (argv[i] == "-m" || argv[i] == "--showtime"){
                    if (time){
                        cout << "Более одного тэга для показа времени работы" << endl;
                        return 0;
                    }
                    time = true;
                }
                else if (i == 1) path = argv[i];
                else{
                    cout << "Неизвестный синтаксис";
                    return 0;
                }
            }
            try{
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
