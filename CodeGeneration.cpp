#include "CodeGeneration.h"
#include "Parser.h"

#include "llvm/Function.h"

using namespace llvm;
using namespace std;

namespace CodeGeneration {

CodeGenerator::CodeGenerator(LLVMContext &ctx,
                             Module *module,
                             StringPool &stringPool)
   : _ctx(ctx),
     _module(module),
     _builder(ctx)
{
   _opAdd =  stringPool.intern("+");
   _opSub =  stringPool.intern("-");
   _opMult = stringPool.intern("*");
}

Function *
CodeGenerator::TranslateFunction(AST::Expression *expr)
{
   FunctionType *ft = FunctionType::get(Type::getInt64Ty(_ctx),
                                        Type::getVoidTy(_ctx));
   Function *func = Function::Create(ft,
                                     Function::ExternalLinkage,
                                     "entry",
                                     _module);

   BasicBlock *bb = BasicBlock::Create(_ctx, "entry", func);
   _builder.SetInsertPoint(bb);

   Value *ret = TranslateExpression(expr);

   _builder.CreateRet(ret);

   return func;
}

Value *
CodeGenerator::TranslateExpression(AST::Expression *expr)
{
   switch (expr->GetType()) {
   case AST::Expression::List: {
      AST::List *l = static_cast<AST::List *>(expr);
      AST::ExpressionList::const_iterator i = l->GetElements().begin();
      AST::Atom *func = static_cast<AST::Atom *>(*i++);
      Value *result = TranslateExpression(*i++);

      for (; i != l->GetElements().end(); i++) {
         Value *v = TranslateExpression(*i);

         if (func->GetValue() == _opAdd) {
            result = _builder.CreateAdd(result, v);
         } else if (func->GetValue() == _opSub) {
            result = _builder.CreateSub(result, v);
         } else if (func->GetValue() == _opMult) {
            result = _builder.CreateMul(result, v);
         }
      }

      return result;
   }
   case AST::Expression::Atom:
      return NULL;
   case AST::Expression::Constant: {
      AST::Constant *c = static_cast<AST::Constant *>(expr);

      return ConstantInt::get(_ctx, APInt(64, c->GetValue(), true));
   }
   default:
      return NULL;
   }
}

}
