DEPS="Atom.o CodeGeneration.o Constant.o FunctionCall.o Global.o Lexer.o List.o Main.o Parser.o Variable.o"
redo-ifchange link $DEPS
. ./link "$3" $DEPS
