#include "AST.h"
#include "CodeGeneration.h"
#include "Parser.h"

#include "llvm/Function.h"

using namespace llvm;
using namespace std;

namespace CodeGeneration {

Context::Context(LLVMContext &ctx,
                 StringPool &stringPool)
   : _ctx(ctx),
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

   Context ctx(_ctx, _stringPool);
   IRBuilder<> &builder = ctx.GetBuilder();

   builder.SetInsertPoint(bb);

   Value *ret = expr->Translate(ctx);

   builder.CreateRet(ret);

   return func;
}

}
