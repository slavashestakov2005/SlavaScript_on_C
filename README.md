# SlavaScript
SlavaScript — интерпретируемый, динамически типизированный язык программирования общего назначения.  
У языка имеется небольшая стандартная библиотека, написанная на C++.  
Подсветка синтаксиса языка поддерживается в `Notepad++`, также язык поддерживается на телефонах с помощью [версии](https://github.com/slavashestakov2005/SlavaScript) на Java.  
Автором языка является Шестаков Вячеслав, редактором текстов является Вахитова Екатерина Юрьевна.

## Описание
Это версия SlavaScript на C++.  
Предыдущий репозиторий, редактируемый вручную, располагается по [адресу](https://github.com/slavashestakov2005/Version_on_C).  
Документацию к языку можно посмотреть [здесь](https://drive.google.com/file/d/1JXeZC6GDskKCiZNyj6zwlt4cYiHpMhEf/view?usp=sharing).

## Сборка
Графическая библиотека SlavaScript требует установку [SFML](https://www.sfml-dev.org/). Если вы хотите собрать SlavaScript самостоятельно, то:
+ Скачайте библиотеку `SFML` версии [2.5.1](https://www.sfml-dev.org/files/SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit.zip) и распакуйте архив в папку `C:\Users\Public\Plugins`.
+ Используйте `VisualStudioCode` и `g++ 11.2.0`, тогда после запуска вам понадобятся только `*.dll` файлы из папки `dlls-11.2.0`.

Текущая версия SlavaScript написана на C++20.

## Синтаксис
Описание синтаксиса языка в формате схожим с EBNF можно посмотреть в файле `info/syntax.ebnf`.  
Файл `info/Syntax for Notepad++.xml` обеспечивает подсветку синтаксиса в `Notepad++`.
