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
      List,
      Atom,
      Constant,
      Variable,
      FunctionCall,
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
   List() : Expression(Expression::List) {}
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

class Variable : public Expression {
public:
   Variable(llvm::PooledStringPtr name)
      : Expression(Expression::Variable), _name(name) {}

   llvm::PooledStringPtr GetName() const { return _name; }

   virtual std::string ToString() const;

private:
   llvm::PooledStringPtr _name;
};

class FunctionCall : public Expression {
   FunctionCall(llvm::PooledStringPtr name)
      : Expression(Expression::FunctionCall), _name(name) {}

   llvm::PooledStringPtr GetName() const { return _name; }
   ExpressionList &GetArguments() { return _args; }

   virtual std::string ToString() const;

private:
   llvm::PooledStringPtr _name;
   ExpressionList _args;
};

Expression *Parse(const llvm::MemoryBuffer &input,
                  llvm::StringPool &stringPool);

}
