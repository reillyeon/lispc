#include "CodeGeneration.h"
#include "Parser.h"

using namespace llvm;
using namespace std;

namespace CodeGeneration {

CodeGenerator::CodeGenerator(LLVMContext &ctx,
                             StringPool &stringPool)
   : _ctx(ctx),
     _builder(ctx)
{
   _opAdd =  stringPool.intern("+");
   _opSub =  stringPool.intern("-");
   _opMult = stringPool.intern("*");
}

Value *
CodeGenerator::TranslateExpression(AST::Expression *expr)
{
   switch (expr->GetType()) {
   case AST::Expression::Sexp: {
      AST::List *l = static_cast<AST::List *>(expr);
      AST::ExpressionList::const_iterator i = l->GetElements().begin();
      i++;
      Value *result = TranslateExpression(*i++);

      for (; i != l->GetElements().end(); i++) {
         result = _builder.CreateAdd(result, TranslateExpression(*i));
      }

      return NULL;
   }
   case AST::Expression::Atom:
      return NULL;
   case AST::Expression::Constant: {
      AST::Constant *c = static_cast<AST::Constant *>(expr);

      return ConstantInt::get(_ctx, APInt(64, c->GetValue(), true));
   }
   }
}

}
