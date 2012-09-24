#include <vector>
#include <string>

namespace llvm {
   class MemoryBuffer;
}

namespace Lexer {

enum TokenType {
};

class Token {
public:
   enum Type {
      OpenParen,
      CloseParen,
      Integer,
      Atom,
      Eof,
   };

   Token() : _type(Eof) {}
   
   Type GetType() const { return _type; }
   void SetType(Type type) { _type = type; }

   const std::string &GetStringValue() const { return _stringValue; }
   void SetStringValue(std::string &value) { _stringValue = value; }

   int GetIntValue() const { return _intValue; }
   void SetIntValue(int value) { _intValue = value; }

   std::string ToString() const;

private:
   Type _type;
   int _intValue;
   std::string _stringValue;
};

class Tokenizer {
public:
   Tokenizer(const llvm::MemoryBuffer *input);

   void Next(Token &result);

private:
   const char *_curPos;
   std::string _tmpValue;
};

}
