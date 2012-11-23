#include <string>

#include "llvm/Support/StringPool.h"

namespace llvm {
   class MemoryBuffer;
}

namespace Lexer {

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

   llvm::PooledStringPtr GetAtomValue() const { return _atomValue; }
   void SetAtomValue(llvm::PooledStringPtr value) { _atomValue = value; }

   int GetIntValue() const { return _intValue; }
   void SetIntValue(int value) { _intValue = value; }

   std::string ToString() const;

private:
   Type _type;
   int _intValue;
   llvm::PooledStringPtr _atomValue;
};

class Tokenizer {
public:
   Tokenizer(const llvm::MemoryBuffer &input,
             llvm::StringPool &stringPool);

   void Next(Token &result);

private:
   bool ProcessValue(Token &result);

   const char *_curPos;
   llvm::StringPool &_stringPool;
   std::string _tmpValue;
};

}
