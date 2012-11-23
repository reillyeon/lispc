#include "AST.h"
#include "Parser.h"
#include "Lexer.h"

#include <list>
#include <sstream>
#include <iostream>

using namespace std;
using namespace llvm;

namespace Parser {

AST::Expression *
Parse(const MemoryBuffer &input,
      StringPool &stringPool)
{
   Lexer::Tokenizer tokenizer(input, stringPool);
   Lexer::Token token;
   list<AST::List *> stack;
   AST::Expression *result = NULL;

   while (true) {
      tokenizer.Next(token);

      cout << "Got " << token.ToString() << endl;
      if (!stack.empty()) {
         cout << "Top of stack is " << stack.back()->ToString() << endl;
      } 

      switch (token.GetType()) {
      case Lexer::Token::OpenParen:
         stack.push_back(new AST::List());
         break;
      case Lexer::Token::CloseParen: {
         AST::List *top = stack.back();

         stack.pop_back();
         if (stack.empty()) {
            result = top;
         } else {
            stack.back()->GetElements().push_back(top);
         }
         break;
      }
      case Lexer::Token::Integer: {
         AST::Constant *c = new AST::Constant(token.GetIntValue());

         stack.back()->GetElements().push_back(c);
         break;
      }
      case Lexer::Token::Atom: {
         AST::Atom *a = new AST::Atom(token.GetAtomValue());

         stack.back()->GetElements().push_back(a);
         break;
      }
      case Lexer::Token::Eof:
         return result;
      }
   }
}

}

