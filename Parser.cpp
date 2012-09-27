#include "Parser.h"
#include "Lexer.h"

#include <sstream>
#include <iostream>

using namespace std;
using namespace llvm;

namespace AST {

FunctionCall::~FunctionCall()
{
   for (ExpressionList::iterator i = _args.begin(); i != _args.end(); i++) {
      delete *i;
   }
}

std::string
FunctionCall::ToString() const
{
   stringstream str;

   str << "(" << _function;
   for (ExpressionList::const_iterator i = _args.begin();
        i != _args.end();
        i++) {
      str << " " << (*i)->ToString();
   }
   str << ")";

   return str.str();
}

std::string
Constant::ToString() const
{
   stringstream str;

   str << _value;

   return str.str();
}

Expression *
Parse(const llvm::MemoryBuffer *input)
{
   Lexer::Tokenizer tokenizer(input);
   Lexer::Token token;
   ExpressionList stack;
   Expression *result = NULL;

   while (true) {
      tokenizer.Next(token);

      cout << "Got " << token.ToString() << endl;
      if (!stack.empty()) {
         cout << "Top of stack is " << stack.back()->ToString() << endl;
      } 

      switch (token.GetType()) {
      case Lexer::Token::OpenParen:
         stack.push_back(new FunctionCall());
         break;
      case Lexer::Token::CloseParen: {
         Expression *top = stack.back();

         stack.pop_back();
         if (stack.empty()) {
            result = top;
         } else {
            FunctionCall *func = static_cast<FunctionCall *>(stack.back());

            func->GetArguments().push_back(top);
         }
         break;
      }
      case Lexer::Token::Integer: {
         FunctionCall *func = static_cast<FunctionCall *>(stack.back());

         func->GetArguments().push_back(new Constant(token.GetIntValue()));
         break;
      }
      case Lexer::Token::Atom: {
         FunctionCall *func = static_cast<FunctionCall *>(stack.back());

         func->SetFunction(token.GetStringValue());
         break;
      }
      case Lexer::Token::Eof:
         return result;
      }
   }
}

}

