#include <vector>
#include <istream>

namespace Lexer {

enum TokenType {
   OPEN_PAREN,
   CLOSE_PAREN,
   INTEGER,
   ATOM
};

class Token {
public:
   Token(TokenType type) : _type(type) {}
   
   TokenType GetType() const { return _type; }
   virtual std::string ToString() const;

private:
   TokenType _type;
};

class IntegerToken : public Token {
public:
   IntegerToken(int value) : Token(INTEGER), _value(value) {}

   int GetValue() { return _value; }
   virtual std::string ToString() const;

private:
   int _value;
};

class AtomToken : public Token {
public:
   AtomToken(std::string value) : Token(ATOM), _value(value) {}

   const std::string &GetValue() { return _value; }
   virtual std::string ToString() const;

private:
   std::string _value;
};

typedef std::vector<Token *> TokenVector;

TokenVector Tokenize(std::istream &input);

}
