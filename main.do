DEPS="Lexer.o"
redo-ifchange link $DEPS
. ./link "$3" $DEPS
