#include <string>
#include <vector>

#include "llvm/Support/StringPool.h"

namespace llvm {
   class MemoryBuffer;
}

namespace AST {

class Expression {
public:
   enum Type {
      Sexp,
      Atom,
      Constant,
   };

   Expression(Type type) : _type(type) {}
   virtual ~Expression() {}

   Type GetType() const { return _type; }

   virtual std::string ToString() const = 0;

private:
   Type _type;
};

typedef std::vector<Expression *> ExpressionList;

class List : public Expression {
public:
   List() : Expression(Expression::Sexp) {}
   virtual ~List();

   ExpressionList &GetElements() { return _elements; }

   virtual std::string ToString() const;

private:
   ExpressionList _elements;
};

class Atom : public Expression {
public:
   Atom(llvm::PooledStringPtr value)
      : Expression(Expression::Atom), _value(value) {}

   llvm::PooledStringPtr GetValue() const { return _value; }

   virtual std::string ToString() const;

private:
   llvm::PooledStringPtr _value;
};

class Constant : public Expression {
public:
   Constant(int value)
      : Expression(Expression::Constant), _value(value) {}

   int GetValue() const { return _value; }

   virtual std::string ToString() const;

private:
   int _value;
};

Expression *Parse(const llvm::MemoryBuffer &input,
                  llvm::StringPool &stringPool);

}
