DEPS="Lexer.o Main.o Parser.o"
redo-ifchange link $DEPS
. ./link "$3" $DEPS
