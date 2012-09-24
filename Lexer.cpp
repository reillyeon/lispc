#include "Lexer.h"

#include <sstream>
#include <iostream>

#include "llvm/ADT/OwningPtr.h"
#include "llvm/Support/system_error.h"
#include "llvm/Support/MemoryBuffer.h"

using namespace std;
using namespace llvm;

namespace Lexer {

string
Token::ToString() const
{
   stringstream str;

   switch (_type) {
   case OpenParen:
      str << "OpenParen";
      break;
   case CloseParen:
      str << "CloseParen";
      break;
   case Integer:
      str << "Integer(" << _intValue << ")";
      break;
   case Atom:
      str << "Atom(" << _stringValue << ")";
      break;
   case Eof:
      str << "Eof";
      break;
   }

   return str.str();
}

Tokenizer::Tokenizer(const MemoryBuffer *input)
   : _curPos(input->getBufferStart()), _tmpValue()
{
}

void
Tokenizer::Next(Token &result)
{
   while (true) {
      char c = *_curPos;

      if (c == '(' || c == ')' ||
          c == ' ' || c == '\t' || c == '\n' || c == '\0') {
         if (_tmpValue.length() > 0) {
            bool isInteger = true;

            for (string::iterator i = _tmpValue.begin();
                 i != _tmpValue.end();
                 i++) {
               if (*i < '0' || *i > '9') {
                  isInteger = false;
                  break;
               }
            }

            if (isInteger) {
               result.SetType(Token::Integer);
               result.SetIntValue(atoi(_tmpValue.c_str()));
            } else {
               result.SetType(Token::Atom);
               result.SetStringValue(_tmpValue);
            }

            _tmpValue.clear();
            if (c != '(' && c != ')' && c != '\0') {
               _curPos++;
            }
            return;
         }
      }

      switch (c) {
      case '(':
         result.SetType(Token::OpenParen);
         _curPos++;
         return;
      case ')':
         result.SetType(Token::CloseParen);
         _curPos++;
         return;
      case '\0':
         result.SetType(Token::Eof);
         return;
      case '\t': case '\n': case ' ':
         _curPos++;
         break;
      default:
         _tmpValue.push_back(c);
         _curPos++;
      }
   }
}


}


int main(int argc, char **argv) {
   OwningPtr<MemoryBuffer> input;

   error_code err = MemoryBuffer::getSTDIN(input);

   Lexer::Tokenizer tokenizer(input.get());

   Lexer::Token token;
   do {
      tokenizer.Next(token);

      cout << token.ToString() << endl;
   } while (token.GetType() != Lexer::Token::Eof);

   return err.value();
}
