namespace llvm {
   class MemoryBuffer;
}

namespace Lexer {
   class Tokenizer;
}

namespace AST {
   class Expression;
}

namespace Parser {

class Parser {
public:
   Parser(Lexer::Tokenizer &tokenizer);

   AST::Expression *NextExpression();

private:
   Lexer::Tokenizer &_tokenizer;
};

}
