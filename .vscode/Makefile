OBJ = build_cpp/obj
GPP = g++ -Wall -std=c++20
SFML_INCLUDE = -I C:\Users\Public\Plugins\SFML-2.5.1\include
SFML_LIB = -L C:\\Users\Public\Plugins\SFML-2.5.1\lib -lsfml-graphics -lsfml-window -lsfml-system

run: $(OBJ)/main.o $(OBJ)/Compiler/compiler.o $(OBJ)/Compiler/compilervisitor.o $(OBJ)/Exception/exception.o $(OBJ)/Exception/exceptions.o $(OBJ)/Expression/arrayexpression.o $(OBJ)/Expression/assignmentexpression.o $(OBJ)/Expression/binaryexpression.o $(OBJ)/Expression/conditionalexpression.o $(OBJ)/Expression/mapexpression.o $(OBJ)/Expression/operators.o $(OBJ)/Expression/suffixassignmentexpression.o $(OBJ)/Expression/suffixelement.o $(OBJ)/Expression/suffixexpression.o $(OBJ)/Expression/ternaryexpression.o $(OBJ)/Expression/unaryexpression.o $(OBJ)/Expression/valueexpression.o $(OBJ)/Expression/variableexpression.o $(OBJ)/Lib/argument.o $(OBJ)/Lib/arguments.o $(OBJ)/Lib/class.o $(OBJ)/Lib/classes.o $(OBJ)/Lib/filesystem.o $(OBJ)/Lib/function.o $(OBJ)/Lib/functions.o $(OBJ)/Lib/modulefunction.o $(OBJ)/Lib/moduleobject.o $(OBJ)/Lib/names.o $(OBJ)/Lib/userdefinedclass.o $(OBJ)/Lib/userdefinedfunction.o $(OBJ)/Lib/utils.o $(OBJ)/Lib/variables.o $(OBJ)/Modules/chemistry.o $(OBJ)/Modules/draw.o $(OBJ)/Modules/files.o $(OBJ)/Modules/functional.o $(OBJ)/Modules/global.o $(OBJ)/Modules/math.o $(OBJ)/Modules/modules.o $(OBJ)/Modules/std.o $(OBJ)/Modules/types.o $(OBJ)/Parser/lexer.o $(OBJ)/Parser/parseerror.o $(OBJ)/Parser/parseerrors.o $(OBJ)/Parser/parser.o $(OBJ)/Parser/token.o $(OBJ)/Run/callstack.o $(OBJ)/Run/path.o $(OBJ)/Run/repl.o $(OBJ)/Run/start.o $(OBJ)/Statement/blockstatement.o $(OBJ)/Statement/breakstatement.o $(OBJ)/Statement/classdeclarationsstatement.o $(OBJ)/Statement/continuestatement.o $(OBJ)/Statement/dowhilestatement.o $(OBJ)/Statement/exprstatement.o $(OBJ)/Statement/foreacharraystatement.o $(OBJ)/Statement/foreachmapstatement.o $(OBJ)/Statement/forstatement.o $(OBJ)/Statement/functiondefinestatement.o $(OBJ)/Statement/ifstatement.o $(OBJ)/Statement/importstatement.o $(OBJ)/Statement/integrationstatement.o $(OBJ)/Statement/printlnstatement.o $(OBJ)/Statement/printstatement.o $(OBJ)/Statement/returnstatement.o $(OBJ)/Statement/switchstatement.o $(OBJ)/Statement/throwstatement.o $(OBJ)/Statement/trystatement.o $(OBJ)/Statement/whilestatement.o $(OBJ)/Value/arrayvalue.o $(OBJ)/Value/boolvalue.o $(OBJ)/Value/classvalue.o $(OBJ)/Value/functionvalue.o $(OBJ)/Value/integrationvalue.o $(OBJ)/Value/mapvalue.o $(OBJ)/Value/nullvalue.o $(OBJ)/Value/numbervalue.o $(OBJ)/Value/objectvalue.o $(OBJ)/Value/stringvalue.o $(OBJ)/Value/value.o $(OBJ)/Value/values.o $(OBJ)/Value/bignumbers/bignum.o $(OBJ)/Value/bignumbers/smath.o $(OBJ)/Visitor/assignvalidator.o $(OBJ)/Visitor/functionadder.o $(OBJ)/Visitor/importadder.o $(OBJ)/Visitor/variableprinter.o $(OBJ)/Visitor/visitor.o $(OBJ)/icon.res
	$(GPP) -o build_cpp/run $(OBJ)/main.o $(OBJ)/Compiler/compiler.o $(OBJ)/Compiler/compilervisitor.o $(OBJ)/Exception/exception.o $(OBJ)/Exception/exceptions.o $(OBJ)/Expression/arrayexpression.o $(OBJ)/Expression/assignmentexpression.o $(OBJ)/Expression/binaryexpression.o $(OBJ)/Expression/conditionalexpression.o $(OBJ)/Expression/mapexpression.o $(OBJ)/Expression/operators.o $(OBJ)/Expression/suffixassignmentexpression.o $(OBJ)/Expression/suffixelement.o $(OBJ)/Expression/suffixexpression.o $(OBJ)/Expression/ternaryexpression.o $(OBJ)/Expression/unaryexpression.o $(OBJ)/Expression/valueexpression.o $(OBJ)/Expression/variableexpression.o $(OBJ)/Lib/argument.o $(OBJ)/Lib/arguments.o $(OBJ)/Lib/class.o $(OBJ)/Lib/classes.o $(OBJ)/Lib/filesystem.o $(OBJ)/Lib/function.o $(OBJ)/Lib/functions.o $(OBJ)/Lib/modulefunction.o $(OBJ)/Lib/moduleobject.o $(OBJ)/Lib/names.o $(OBJ)/Lib/userdefinedclass.o $(OBJ)/Lib/userdefinedfunction.o $(OBJ)/Lib/utils.o $(OBJ)/Lib/variables.o $(OBJ)/Modules/chemistry.o $(OBJ)/Modules/draw.o $(OBJ)/Modules/files.o $(OBJ)/Modules/functional.o $(OBJ)/Modules/global.o $(OBJ)/Modules/math.o $(OBJ)/Modules/modules.o $(OBJ)/Modules/std.o $(OBJ)/Modules/types.o $(OBJ)/Parser/lexer.o $(OBJ)/Parser/parseerror.o $(OBJ)/Parser/parseerrors.o $(OBJ)/Parser/parser.o $(OBJ)/Parser/token.o $(OBJ)/Run/callstack.o $(OBJ)/Run/path.o $(OBJ)/Run/repl.o $(OBJ)/Run/start.o $(OBJ)/Statement/blockstatement.o $(OBJ)/Statement/breakstatement.o $(OBJ)/Statement/classdeclarationsstatement.o $(OBJ)/Statement/continuestatement.o $(OBJ)/Statement/dowhilestatement.o $(OBJ)/Statement/exprstatement.o $(OBJ)/Statement/foreacharraystatement.o $(OBJ)/Statement/foreachmapstatement.o $(OBJ)/Statement/forstatement.o $(OBJ)/Statement/functiondefinestatement.o $(OBJ)/Statement/ifstatement.o $(OBJ)/Statement/importstatement.o $(OBJ)/Statement/integrationstatement.o $(OBJ)/Statement/printlnstatement.o $(OBJ)/Statement/printstatement.o $(OBJ)/Statement/returnstatement.o $(OBJ)/Statement/switchstatement.o $(OBJ)/Statement/throwstatement.o $(OBJ)/Statement/trystatement.o $(OBJ)/Statement/whilestatement.o $(OBJ)/Value/arrayvalue.o $(OBJ)/Value/boolvalue.o $(OBJ)/Value/classvalue.o $(OBJ)/Value/functionvalue.o $(OBJ)/Value/integrationvalue.o $(OBJ)/Value/mapvalue.o $(OBJ)/Value/nullvalue.o $(OBJ)/Value/numbervalue.o $(OBJ)/Value/objectvalue.o $(OBJ)/Value/stringvalue.o $(OBJ)/Value/value.o $(OBJ)/Value/values.o $(OBJ)/Value/bignumbers/bignum.o $(OBJ)/Value/bignumbers/smath.o $(OBJ)/Visitor/assignvalidator.o $(OBJ)/Visitor/functionadder.o $(OBJ)/Visitor/importadder.o $(OBJ)/Visitor/variableprinter.o $(OBJ)/Visitor/visitor.o $(OBJ)/icon.res $(SFML_LIB)
$(OBJ)/main.o: main.cpp
	$(GPP) -c -o $(OBJ)/main.o main.cpp
$(OBJ)/Compiler/compiler.o: Compiler/compiler.cpp
	$(GPP) -c -o $(OBJ)/Compiler/compiler.o Compiler/compiler.cpp
$(OBJ)/Compiler/compilervisitor.o: Compiler/compilervisitor.cpp
	$(GPP) -c -o $(OBJ)/Compiler/compilervisitor.o Compiler/compilervisitor.cpp
$(OBJ)/Exception/exception.o: Exception/exception.cpp
	$(GPP) -c -o $(OBJ)/Exception/exception.o Exception/exception.cpp
$(OBJ)/Exception/exceptions.o: Exception/exceptions.cpp
	$(GPP) -c -o $(OBJ)/Exception/exceptions.o Exception/exceptions.cpp
$(OBJ)/Expression/arrayexpression.o: Expression/arrayexpression.cpp
	$(GPP) -c -o $(OBJ)/Expression/arrayexpression.o Expression/arrayexpression.cpp
$(OBJ)/Expression/assignmentexpression.o: Expression/assignmentexpression.cpp
	$(GPP) -c -o $(OBJ)/Expression/assignmentexpression.o Expression/assignmentexpression.cpp
$(OBJ)/Expression/binaryexpression.o: Expression/binaryexpression.cpp
	$(GPP) -c -o $(OBJ)/Expression/binaryexpression.o Expression/binaryexpression.cpp
$(OBJ)/Expression/conditionalexpression.o: Expression/conditionalexpression.cpp
	$(GPP) -c -o $(OBJ)/Expression/conditionalexpression.o Expression/conditionalexpression.cpp
$(OBJ)/Expression/mapexpression.o: Expression/mapexpression.cpp
	$(GPP) -c -o $(OBJ)/Expression/mapexpression.o Expression/mapexpression.cpp
$(OBJ)/Expression/operators.o: Expression/operators.cpp
	$(GPP) -c -o $(OBJ)/Expression/operators.o Expression/operators.cpp
$(OBJ)/Expression/suffixassignmentexpression.o: Expression/suffixassignmentexpression.cpp
	$(GPP) -c -o $(OBJ)/Expression/suffixassignmentexpression.o Expression/suffixassignmentexpression.cpp
$(OBJ)/Expression/suffixelement.o: Expression/suffixelement.cpp
	$(GPP) -c -o $(OBJ)/Expression/suffixelement.o Expression/suffixelement.cpp
$(OBJ)/Expression/suffixexpression.o: Expression/suffixexpression.cpp
	$(GPP) -c -o $(OBJ)/Expression/suffixexpression.o Expression/suffixexpression.cpp
$(OBJ)/Expression/ternaryexpression.o: Expression/ternaryexpression.cpp
	$(GPP) -c -o $(OBJ)/Expression/ternaryexpression.o Expression/ternaryexpression.cpp
$(OBJ)/Expression/unaryexpression.o: Expression/unaryexpression.cpp
	$(GPP) -c -o $(OBJ)/Expression/unaryexpression.o Expression/unaryexpression.cpp
$(OBJ)/Expression/valueexpression.o: Expression/valueexpression.cpp
	$(GPP) -c -o $(OBJ)/Expression/valueexpression.o Expression/valueexpression.cpp
$(OBJ)/Expression/variableexpression.o: Expression/variableexpression.cpp
	$(GPP) -c -o $(OBJ)/Expression/variableexpression.o Expression/variableexpression.cpp
$(OBJ)/Lib/argument.o: Lib/argument.cpp
	$(GPP) -c -o $(OBJ)/Lib/argument.o Lib/argument.cpp
$(OBJ)/Lib/arguments.o: Lib/arguments.cpp
	$(GPP) -c -o $(OBJ)/Lib/arguments.o Lib/arguments.cpp
$(OBJ)/Lib/class.o: Lib/class.cpp
	$(GPP) -c -o $(OBJ)/Lib/class.o Lib/class.cpp
$(OBJ)/Lib/classes.o: Lib/classes.cpp
	$(GPP) -c -o $(OBJ)/Lib/classes.o Lib/classes.cpp
$(OBJ)/Lib/filesystem.o: Lib/filesystem.cpp
	$(GPP) -c -o $(OBJ)/Lib/filesystem.o Lib/filesystem.cpp
$(OBJ)/Lib/function.o: Lib/function.cpp
	$(GPP) -c -o $(OBJ)/Lib/function.o Lib/function.cpp
$(OBJ)/Lib/functions.o: Lib/functions.cpp
	$(GPP) -c -o $(OBJ)/Lib/functions.o Lib/functions.cpp
$(OBJ)/Lib/modulefunction.o: Lib/modulefunction.cpp
	$(GPP) -c -o $(OBJ)/Lib/modulefunction.o Lib/modulefunction.cpp
$(OBJ)/Lib/moduleobject.o: Lib/moduleobject.cpp
	$(GPP) -c -o $(OBJ)/Lib/moduleobject.o Lib/moduleobject.cpp
$(OBJ)/Lib/names.o: Lib/names.cpp
	$(GPP) -c -o $(OBJ)/Lib/names.o Lib/names.cpp
$(OBJ)/Lib/userdefinedclass.o: Lib/userdefinedclass.cpp
	$(GPP) -c -o $(OBJ)/Lib/userdefinedclass.o Lib/userdefinedclass.cpp
$(OBJ)/Lib/userdefinedfunction.o: Lib/userdefinedfunction.cpp
	$(GPP) -c -o $(OBJ)/Lib/userdefinedfunction.o Lib/userdefinedfunction.cpp
$(OBJ)/Lib/utils.o: Lib/utils.cpp
	$(GPP) -c -o $(OBJ)/Lib/utils.o Lib/utils.cpp
$(OBJ)/Lib/variables.o: Lib/variables.cpp
	$(GPP) -c -o $(OBJ)/Lib/variables.o Lib/variables.cpp
$(OBJ)/Modules/chemistry.o: Modules/chemistry.cpp
	$(GPP) -c -o $(OBJ)/Modules/chemistry.o Modules/chemistry.cpp
$(OBJ)/Modules/draw.o: Modules/draw.cpp
	$(GPP) -c -o $(OBJ)/Modules/draw.o Modules/draw.cpp $(SFML_INCLUDE)
$(OBJ)/Modules/files.o: Modules/files.cpp
	$(GPP) -c -o $(OBJ)/Modules/files.o Modules/files.cpp
$(OBJ)/Modules/functional.o: Modules/functional.cpp
	$(GPP) -c -o $(OBJ)/Modules/functional.o Modules/functional.cpp
$(OBJ)/Modules/global.o: Modules/global.cpp
	$(GPP) -c -o $(OBJ)/Modules/global.o Modules/global.cpp
$(OBJ)/Modules/math.o: Modules/math.cpp
	$(GPP) -c -o $(OBJ)/Modules/math.o Modules/math.cpp
$(OBJ)/Modules/modules.o: Modules/modules.cpp
	$(GPP) -c -o $(OBJ)/Modules/modules.o Modules/modules.cpp
$(OBJ)/Modules/std.o: Modules/std.cpp
	$(GPP) -c -o $(OBJ)/Modules/std.o Modules/std.cpp
$(OBJ)/Modules/types.o: Modules/types.cpp
	$(GPP) -c -o $(OBJ)/Modules/types.o Modules/types.cpp
$(OBJ)/Parser/lexer.o: Parser/lexer.cpp
	$(GPP) -c -o $(OBJ)/Parser/lexer.o Parser/lexer.cpp
$(OBJ)/Parser/parseerror.o: Parser/parseerror.cpp
	$(GPP) -c -o $(OBJ)/Parser/parseerror.o Parser/parseerror.cpp
$(OBJ)/Parser/parseerrors.o: Parser/parseerrors.cpp
	$(GPP) -c -o $(OBJ)/Parser/parseerrors.o Parser/parseerrors.cpp
$(OBJ)/Parser/parser.o: Parser/parser.cpp
	$(GPP) -c -o $(OBJ)/Parser/parser.o Parser/parser.cpp
$(OBJ)/Parser/token.o: Parser/token.cpp
	$(GPP) -c -o $(OBJ)/Parser/token.o Parser/token.cpp
$(OBJ)/Run/callstack.o: Run/callstack.cpp
	$(GPP) -c -o $(OBJ)/Run/callstack.o Run/callstack.cpp
$(OBJ)/Run/path.o: Run/path.cpp
	$(GPP) -c -o $(OBJ)/Run/path.o Run/path.cpp
$(OBJ)/Run/repl.o: Run/repl.cpp
	$(GPP) -c -o $(OBJ)/Run/repl.o Run/repl.cpp
$(OBJ)/Run/start.o: Run/start.cpp
	$(GPP) -c -o $(OBJ)/Run/start.o Run/start.cpp
$(OBJ)/Statement/blockstatement.o: Statement/blockstatement.cpp
	$(GPP) -c -o $(OBJ)/Statement/blockstatement.o Statement/blockstatement.cpp
$(OBJ)/Statement/breakstatement.o: Statement/breakstatement.cpp
	$(GPP) -c -o $(OBJ)/Statement/breakstatement.o Statement/breakstatement.cpp
$(OBJ)/Statement/classdeclarationsstatement.o: Statement/classdeclarationsstatement.cpp
	$(GPP) -c -o $(OBJ)/Statement/classdeclarationsstatement.o Statement/classdeclarationsstatement.cpp
$(OBJ)/Statement/continuestatement.o: Statement/continuestatement.cpp
	$(GPP) -c -o $(OBJ)/Statement/continuestatement.o Statement/continuestatement.cpp
$(OBJ)/Statement/dowhilestatement.o: Statement/dowhilestatement.cpp
	$(GPP) -c -o $(OBJ)/Statement/dowhilestatement.o Statement/dowhilestatement.cpp
$(OBJ)/Statement/exprstatement.o: Statement/exprstatement.cpp
	$(GPP) -c -o $(OBJ)/Statement/exprstatement.o Statement/exprstatement.cpp
$(OBJ)/Statement/foreacharraystatement.o: Statement/foreacharraystatement.cpp
	$(GPP) -c -o $(OBJ)/Statement/foreacharraystatement.o Statement/foreacharraystatement.cpp
$(OBJ)/Statement/foreachmapstatement.o: Statement/foreachmapstatement.cpp
	$(GPP) -c -o $(OBJ)/Statement/foreachmapstatement.o Statement/foreachmapstatement.cpp
$(OBJ)/Statement/forstatement.o: Statement/forstatement.cpp
	$(GPP) -c -o $(OBJ)/Statement/forstatement.o Statement/forstatement.cpp
$(OBJ)/Statement/functiondefinestatement.o: Statement/functiondefinestatement.cpp
	$(GPP) -c -o $(OBJ)/Statement/functiondefinestatement.o Statement/functiondefinestatement.cpp
$(OBJ)/Statement/ifstatement.o: Statement/ifstatement.cpp
	$(GPP) -c -o $(OBJ)/Statement/ifstatement.o Statement/ifstatement.cpp
$(OBJ)/Statement/importstatement.o: Statement/importstatement.cpp
	$(GPP) -c -o $(OBJ)/Statement/importstatement.o Statement/importstatement.cpp
$(OBJ)/Statement/integrationstatement.o: Statement/integrationstatement.cpp
	$(GPP) -c -o $(OBJ)/Statement/integrationstatement.o Statement/integrationstatement.cpp
$(OBJ)/Statement/printlnstatement.o: Statement/printlnstatement.cpp
	$(GPP) -c -o $(OBJ)/Statement/printlnstatement.o Statement/printlnstatement.cpp
$(OBJ)/Statement/printstatement.o: Statement/printstatement.cpp
	$(GPP) -c -o $(OBJ)/Statement/printstatement.o Statement/printstatement.cpp
$(OBJ)/Statement/returnstatement.o: Statement/returnstatement.cpp
	$(GPP) -c -o $(OBJ)/Statement/returnstatement.o Statement/returnstatement.cpp
$(OBJ)/Statement/switchstatement.o: Statement/switchstatement.cpp
	$(GPP) -c -o $(OBJ)/Statement/switchstatement.o Statement/switchstatement.cpp
$(OBJ)/Statement/throwstatement.o: Statement/throwstatement.cpp
	$(GPP) -c -o $(OBJ)/Statement/throwstatement.o Statement/throwstatement.cpp
$(OBJ)/Statement/trystatement.o: Statement/trystatement.cpp
	$(GPP) -c -o $(OBJ)/Statement/trystatement.o Statement/trystatement.cpp
$(OBJ)/Statement/whilestatement.o: Statement/whilestatement.cpp
	$(GPP) -c -o $(OBJ)/Statement/whilestatement.o Statement/whilestatement.cpp
$(OBJ)/Value/arrayvalue.o: Value/arrayvalue.cpp
	$(GPP) -c -o $(OBJ)/Value/arrayvalue.o Value/arrayvalue.cpp
$(OBJ)/Value/boolvalue.o: Value/boolvalue.cpp
	$(GPP) -c -o $(OBJ)/Value/boolvalue.o Value/boolvalue.cpp
$(OBJ)/Value/classvalue.o: Value/classvalue.cpp
	$(GPP) -c -o $(OBJ)/Value/classvalue.o Value/classvalue.cpp
$(OBJ)/Value/functionvalue.o: Value/functionvalue.cpp
	$(GPP) -c -o $(OBJ)/Value/functionvalue.o Value/functionvalue.cpp
$(OBJ)/Value/integrationvalue.o: Value/integrationvalue.cpp
	$(GPP) -c -o $(OBJ)/Value/integrationvalue.o Value/integrationvalue.cpp
$(OBJ)/Value/mapvalue.o: Value/mapvalue.cpp
	$(GPP) -c -o $(OBJ)/Value/mapvalue.o Value/mapvalue.cpp
$(OBJ)/Value/nullvalue.o: Value/nullvalue.cpp
	$(GPP) -c -o $(OBJ)/Value/nullvalue.o Value/nullvalue.cpp
$(OBJ)/Value/numbervalue.o: Value/numbervalue.cpp
	$(GPP) -c -o $(OBJ)/Value/numbervalue.o Value/numbervalue.cpp
$(OBJ)/Value/objectvalue.o: Value/objectvalue.cpp
	$(GPP) -c -o $(OBJ)/Value/objectvalue.o Value/objectvalue.cpp
$(OBJ)/Value/stringvalue.o: Value/stringvalue.cpp
	$(GPP) -c -o $(OBJ)/Value/stringvalue.o Value/stringvalue.cpp
$(OBJ)/Value/value.o: Value/value.cpp
	$(GPP) -c -o $(OBJ)/Value/value.o Value/value.cpp
$(OBJ)/Value/values.o: Value/values.cpp
	$(GPP) -c -o $(OBJ)/Value/values.o Value/values.cpp
$(OBJ)/Value/bignumbers/bignum.o: Value/bignumbers/bignum.cpp
	$(GPP) -c -o $(OBJ)/Value/bignumbers/bignum.o Value/bignumbers/bignum.cpp
$(OBJ)/Value/bignumbers/smath.o: Value/bignumbers/smath.cpp
	$(GPP) -c -o $(OBJ)/Value/bignumbers/smath.o Value/bignumbers/smath.cpp
$(OBJ)/Visitor/assignvalidator.o: Visitor/assignvalidator.cpp
	$(GPP) -c -o $(OBJ)/Visitor/assignvalidator.o Visitor/assignvalidator.cpp
$(OBJ)/Visitor/functionadder.o: Visitor/functionadder.cpp
	$(GPP) -c -o $(OBJ)/Visitor/functionadder.o Visitor/functionadder.cpp
$(OBJ)/Visitor/importadder.o: Visitor/importadder.cpp
	$(GPP) -c -o $(OBJ)/Visitor/importadder.o Visitor/importadder.cpp
$(OBJ)/Visitor/variableprinter.o: Visitor/variableprinter.cpp
	$(GPP) -c -o $(OBJ)/Visitor/variableprinter.o Visitor/variableprinter.cpp
$(OBJ)/Visitor/visitor.o: Visitor/visitor.cpp
	$(GPP) -c -o $(OBJ)/Visitor/visitor.o Visitor/visitor.cpp
$(OBJ)/icon.res: icon.ico icon.rc
	windres icon.rc -O coff -o $(OBJ)/icon.res
