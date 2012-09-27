#include <string>
#include <vector>

namespace llvm {
   class MemoryBuffer;
}

namespace AST {

class Expression {
public:
   enum Type {
      FunctionCall,
      Constant
   };

   Expression(Type type) : _type(type) {}
   virtual ~Expression() {}

   Type GetType() const { return _type; }

   virtual std::string ToString() const = 0;

private:
   Type _type;
};

typedef std::vector<Expression *> ExpressionList;

class FunctionCall : public Expression {
public:
   FunctionCall() : Expression(Expression::FunctionCall) {}
   virtual ~FunctionCall();

   void SetFunction(std::string function) { _function = function; }
   const std::string &GetFunction() const { return _function; }
   ExpressionList &GetArguments() { return _args; }

   virtual std::string ToString() const;

private:
   std::string _function;
   ExpressionList _args;
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

Expression *Parse(const llvm::MemoryBuffer *input);

}
