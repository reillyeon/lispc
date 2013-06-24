#include "AST.h"
#include "CodeGeneration.h"
#include "Global.h"

#include "llvm/IR/Function.h"

using namespace llvm;
using namespace std;

namespace CodeGeneration {

Context::Context(LLVMContext &ctx)
   : _ctx(ctx),
     _builder(ctx)
{
   _opAdd =  Global::StringPool.intern("+");
   _opSub =  Global::StringPool.intern("-");
   _opMult = Global::StringPool.intern("*");
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

   Context ctx(_ctx);
   IRBuilder<> &builder = ctx.GetBuilder();

   builder.SetInsertPoint(bb);

   Value *ret = expr->Translate(ctx);

   builder.CreateRet(ret);

   return func;
}

}
