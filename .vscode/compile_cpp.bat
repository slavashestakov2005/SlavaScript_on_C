set FileName=%1
if not exist build_cpp mkdir build_cpp
if not exist build_cpp\\obj mkdir build_cpp\\obj
if not exist build_cpp\\obj\\Compiler mkdir build_cpp\\obj\\Compiler
if not exist build_cpp\\obj\\Exception mkdir build_cpp\\obj\\Exception
if not exist build_cpp\\obj\\Expression mkdir build_cpp\\obj\\Expression
if not exist build_cpp\\obj\\Lib mkdir build_cpp\\obj\\Lib
if not exist build_cpp\\obj\\Modules mkdir build_cpp\\obj\\Modules
if not exist build_cpp\\obj\\Parser mkdir build_cpp\\obj\\Parser
if not exist build_cpp\\obj\\Run mkdir build_cpp\\obj\\Run
if not exist build_cpp\\obj\\Statement mkdir build_cpp\\obj\\Statement
if not exist build_cpp\\obj\\Value mkdir build_cpp\\obj\\Value
if not exist build_cpp\\obj\\Value\\bignumbers mkdir build_cpp\\obj\\Value\\bignumbers
if not exist build_cpp\\obj\\Visitor mkdir build_cpp\\obj\\Visitor

make run -f .vscode\\Makefile
@REM build_cpp\run.exe -f Examples\\example.x++
