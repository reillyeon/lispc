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
      str << "Atom(" << *_atomValue << ")";
      break;
   case Eof:
      str << "Eof";
      break;
   }

   return str.str();
}

Tokenizer::Tokenizer(const MemoryBuffer *input,
                     StringPool *stringPool)
   : _curPos(input->getBufferStart()),
     _stringPool(stringPool),
     _tmpValue()
{
}

void
Tokenizer::Next(Token &result)
{
   while (true) {
      char c = *_curPos;

      switch (c) {
      case '(':
         if (!ProcessValue(result)) {
            result.SetType(Token::OpenParen);
            _curPos++;
         }
         return;
      case ')':
         if (!ProcessValue(result)) {
            result.SetType(Token::CloseParen);
            _curPos++;
         }
         return;
      case '\0':
         if (!ProcessValue(result)) {
            result.SetType(Token::Eof);
         }
         return;
      case '\t': case '\n': case ' ':
         _curPos++;
         if (ProcessValue(result)) {
            return;
         }
         break;
      default:
         _tmpValue.push_back(c);
         _curPos++;
      }
   }
}

bool
Tokenizer::ProcessValue(Token &result)
{
   bool isInteger = true;

   if (_tmpValue.length() == 0) {
      return false;
   }

   for (string::iterator i = _tmpValue.begin(); i != _tmpValue.end(); i++) {
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
      result.SetAtomValue(_stringPool->intern(_tmpValue));
   }

   _tmpValue.clear();
   return true;
}

}


#if 0
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
#endif
