#include "Parser.h"
#include "Lexer.h"

#include <list>
#include <sstream>
#include <iostream>

using namespace std;
using namespace llvm;

namespace AST {

List::~List()
{
   for (ExpressionList::iterator i = _elements.begin();
        i != _elements.end();
        i++) {
      delete *i;
   }
}

std::string
List::ToString() const
{
   stringstream str;
   bool first = true;

   str << "(";
   for (ExpressionList::const_iterator i = _elements.begin();
        i != _elements.end();
        i++) {
      if (!first) {
         str << " ";
      }
      first = false;
      str << (*i)->ToString();
   }
   str << ")";

   return str.str();
}

std::string
Atom::ToString() const
{
   return *_value;
}

std::string
Constant::ToString() const
{
   stringstream str;

   str << _value;

   return str.str();
}

std::string
Variable::ToString() const
{
   return *_name;
}

std::string
FunctionCall::ToString() const
{
   stringstream str;

   str << "(" << *_name;
   for (ExpressionList::const_iterator i = _args.begin();
        i != _args.end();
        i++) {
      str << " " << (*i)->ToString();
   }
   str << ")";

   return str.str();
}

Expression *
Parse(const MemoryBuffer &input,
      StringPool &stringPool)
{
   Lexer::Tokenizer tokenizer(input, stringPool);
   Lexer::Token token;
   list<List *> stack;
   Expression *result = NULL;

   while (true) {
      tokenizer.Next(token);

      cout << "Got " << token.ToString() << endl;
      if (!stack.empty()) {
         cout << "Top of stack is " << stack.back()->ToString() << endl;
      } 

      switch (token.GetType()) {
      case Lexer::Token::OpenParen:
         stack.push_back(new List());
         break;
      case Lexer::Token::CloseParen: {
         List *top = stack.back();

         stack.pop_back();
         if (stack.empty()) {
            result = top;
         } else {
            stack.back()->GetElements().push_back(top);
         }
         break;
      }
      case Lexer::Token::Integer: {
         Constant *c = new Constant(token.GetIntValue());

         stack.back()->GetElements().push_back(c);
         break;
      }
      case Lexer::Token::Atom: {
         Atom *a = new Atom(token.GetAtomValue());

         stack.back()->GetElements().push_back(a);
         break;
      }
      case Lexer::Token::Eof:
         return result;
      }
   }
}

}

