#include "AST.h"

#include <sstream>

namespace AST {

FunctionCall::~FunctionCall()
{
   for (ExpressionList::iterator i = _args.begin();
        i != _args.end();
        i++) {
      delete *i;
   }
}

std::string
FunctionCall::ToString() const
{
   std::stringstream str;

   str << "(" << *_name;
   for (ExpressionList::const_iterator i = _args.begin();
        i != _args.end();
        i++) {
      str << " " << (*i)->ToString();
   }
   str << ")";

   return str.str();
}

llvm::Value *
FunctionCall::Translate(CodeGeneration::Context &ctx) const
{
   return NULL;
}

}
