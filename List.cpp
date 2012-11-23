#include "AST.h"
#include "CodeGeneration.h"

#include <sstream>

namespace AST {

List::~List()
{
   for (ExpressionList::iterator i = _elements.begin();
        i != _elements.end();
        i++) {
      delete *i;
   }
}

std::string
List::ToString() const
{
   std::stringstream str;
   bool first = true;

   str << "(";
   for (ExpressionList::const_iterator i = _elements.begin();
        i != _elements.end();
        i++) {
      if (!first) {
         str << " ";
      }
      first = false;
      str << (*i)->ToString();
   }
   str << ")";

   return str.str();
}

llvm::Value *
List::Translate(CodeGeneration::Context &ctx) const
{
   llvm::IRBuilder<> &builder = ctx.GetBuilder();
   ExpressionList::const_iterator i = _elements.begin();
   AST::Atom *func = static_cast<AST::Atom *>(*i++);
   llvm::Value *result = (*i++)->Translate(ctx);

   for (; i != _elements.end(); i++) {
      llvm::Value *v = (*i)->Translate(ctx);

      if (func->GetValue() == ctx._opAdd) {
         result = builder.CreateAdd(result, v);
      } else if (func->GetValue() == ctx._opSub) {
         result = builder.CreateSub(result, v);
      } else if (func->GetValue() == ctx._opMult) {
         result = builder.CreateMul(result, v);
      }
   }

   return result;
}

}
