#include "Lexer.h"

#include <sstream>
#include <iostream>

using namespace std;

namespace Lexer {

string
Token::ToString() const
{
   switch (_type) {
   case OPEN_PAREN:
      return "OpenParen";
   case CLOSE_PAREN:
      return "CloseParen";
   default:
      return "<invalid>";
   }
}

string
IntegerToken::ToString() const
{
   stringstream str;

   str << "Integer(" << _value << ")";

   return str.str();
}

string
AtomToken::ToString() const
{
   stringstream str;

   str << "Atom(" << _value << ")";

   return str.str();
}

TokenVector
Tokenize(istream &input)
{
   TokenVector tokens;
   string tmp;
   bool isInteger = true;

   while (input.good()) {
      char c = input.get();

      if (c == '(' || c == ')' || c == ' ' || c == '\t' || c == '\n' ||
          input.eof()) {
         if (tmp.length() > 0) {
            bool isInteger = true;

            for (int i = 0; i < tmp.length(); i++) {
               if (tmp[i] < '0' || tmp[i] > '9') {
                  isInteger = false;
                  break;
               }
            }

            if (isInteger) {
               tokens.push_back(new IntegerToken(atoi(tmp.c_str())));
            } else {
               tokens.push_back(new AtomToken(tmp));
            }
         }

         tmp.clear();

         if (c == '(') {
            tokens.push_back(new Token(OPEN_PAREN));
         } else if (c == ')') {
            tokens.push_back(new Token(CLOSE_PAREN));
         }
      } else {
         tmp.push_back(c);
      }
   }

   return tokens;
}


}

int
main(int argc, char **argv)
{
   Lexer::TokenVector tokens;

   tokens = Lexer::Tokenize(cin);

   for (Lexer::TokenVector::iterator i = tokens.begin(); i != tokens.end(); i++) {
      cout << (*i)->ToString() << endl;
   }

   return 0;
}
