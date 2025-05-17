cmake_minimum_required(VERSION 3.18)
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_STANDARD 20)

set(SFML_FOLDER "C:/Users/Public/Plugins/SFML-2.5.1")
include_directories(${SFML_FOLDER}/include)
link_directories(${SFML_FOLDER}/lib)

project(SlavaScript)
include_directories(.)


set(ICON_ICO ${CMAKE_CURRENT_SOURCE_DIR}/icon.ico)
set(ICON_RC ${CMAKE_CURRENT_SOURCE_DIR}/icon.rc)
set(ICON_RES ${CMAKE_CURRENT_BINARY_DIR}/icon.res)

add_custom_command(
    OUTPUT ${ICON_RES}
    COMMAND windres ${ICON_RC} -I${CMAKE_CURRENT_SOURCE_DIR} -O coff -o ${ICON_RES}
    DEPENDS ${ICON_RC} ${ICON_ICO}
    COMMENT "Compiling icon"
)


set(SOURCE_COMPILER
    Compiler/compiler.cpp
    Compiler/compilervisitor.cpp
)

set(SOURCE_EXCEPTION
    Exception/exception.cpp
    Exception/exceptions.cpp
)

set(SOURCE_EXPRESSION
    Expression/arrayexpression.cpp
    Expression/assignmentexpression.cpp
    Expression/binaryexpression.cpp
    Expression/conditionalexpression.cpp
    Expression/mapexpression.cpp
    Expression/operators.cpp
    Expression/suffixassignmentexpression.cpp
    Expression/suffixelement.cpp
    Expression/suffixexpression.cpp
    Expression/ternaryexpression.cpp
    Expression/unaryexpression.cpp
    Expression/valueexpression.cpp
    Expression/variableexpression.cpp
)

set(SOURCE_LIB
    Lib/argument.cpp
    Lib/arguments.cpp
    Lib/class.cpp
    Lib/classes.cpp
    Lib/filesystem.cpp
    Lib/function.cpp
    Lib/functions.cpp
    Lib/modulefunction.cpp
    Lib/moduleobject.cpp
    Lib/names.cpp
    Lib/userdefinedclass.cpp
    Lib/userdefinedfunction.cpp
    Lib/utils.cpp
    Lib/variables.cpp
)

set(SOURCE_MODULES
    Modules/chemistry.cpp
    Modules/draw.cpp
    Modules/files.cpp
    Modules/functional.cpp
    Modules/global.cpp
    Modules/math.cpp
    Modules/modules.cpp
    Modules/std.cpp
    Modules/types.cpp
)

set(SOURCE_PARSER
    Parser/lexer.cpp
    Parser/parseerror.cpp
    Parser/parseerrors.cpp
    Parser/parser.cpp
    Parser/token.cpp
)

set(SOURCE_RUN
    Run/callstack.cpp
    Run/path.cpp
    Run/repl.cpp
    Run/start.cpp
)

set(SOURCE_STATEMENT
    Statement/blockstatement.cpp
    Statement/breakstatement.cpp
    Statement/classdeclarationsstatement.cpp
    Statement/continuestatement.cpp
    Statement/dowhilestatement.cpp
    Statement/exprstatement.cpp
    Statement/foreacharraystatement.cpp
    Statement/foreachmapstatement.cpp
    Statement/forstatement.cpp
    Statement/functiondefinestatement.cpp
    Statement/ifstatement.cpp
    Statement/importstatement.cpp
    Statement/integrationstatement.cpp
    Statement/printlnstatement.cpp
    Statement/printstatement.cpp
    Statement/returnstatement.cpp
    Statement/switchstatement.cpp
    Statement/throwstatement.cpp
    Statement/trystatement.cpp
    Statement/whilestatement.cpp
)

set(SOURCE_VALUE
    Value/bignumbers/bignum.cpp
    Value/bignumbers/smath.cpp
    Value/arrayvalue.cpp
    Value/boolvalue.cpp
    Value/classvalue.cpp
    Value/functionvalue.cpp
    Value/integrationvalue.cpp
    Value/mapvalue.cpp
    Value/nullvalue.cpp
    Value/numbervalue.cpp
    Value/objectvalue.cpp
    Value/stringvalue.cpp
    Value/value.cpp
    Value/values.cpp
)

set(SOURCE_VISITOR
    Visitor/assignvalidator.cpp
    Visitor/functionadder.cpp
    Visitor/importadder.cpp
    Visitor/variableprinter.cpp
    Visitor/visitor.cpp
)

add_executable(run
    main.cpp
    ${SOURCE_COMPILER}
    ${SOURCE_EXCEPTION}
    ${SOURCE_EXPRESSION}
    ${SOURCE_LIB}
    ${SOURCE_MODULES}
    ${SOURCE_PARSER}
    ${SOURCE_RUN}
    ${SOURCE_STATEMENT}
    ${SOURCE_VALUE}
    ${SOURCE_VISITOR}
    icon.res
)

add_definitions(-Wall)
target_link_libraries(run sfml-system sfml-window sfml-graphics)

if(MINGW)
    target_link_options(run PRIVATE ${ICON_RES})
endif()
