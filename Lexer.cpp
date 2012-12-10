#include "Lexer.h"
#include "Global.h"

#include <sstream>

#include "llvm/Support/MemoryBuffer.h"

namespace Lexer {

std::string
Token::ToString() const
{
   std::stringstream str;

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

Tokenizer::Tokenizer(const llvm::MemoryBuffer &input)
   : _curPos(input.getBufferStart()),
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

   for (std::string::iterator i = _tmpValue.begin();
        i != _tmpValue.end(); i++) {
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
      result.SetAtomValue(Global::StringPool.intern(_tmpValue));
   }

   _tmpValue.clear();
   return true;
}

}
