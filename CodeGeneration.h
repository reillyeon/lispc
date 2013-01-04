#include "llvm/IRBuilder.h"

namespace llvm {
   class Function;
   class Value;
}

namespace AST {
   class Expression;
}

namespace CodeGeneration {

class Context {
public:
   Context(llvm::LLVMContext &ctx);

   llvm::LLVMContext &GetContext() { return _ctx; }
   llvm::IRBuilder<> &GetBuilder() { return _builder; }

   llvm::PooledStringPtr _opAdd;
   llvm::PooledStringPtr _opSub;
   llvm::PooledStringPtr _opMult;

private:
   llvm::LLVMContext &_ctx;
   llvm::IRBuilder<> _builder;
};

class CodeGenerator {
public:
   CodeGenerator(llvm::LLVMContext &ctx,
                 llvm::Module *module)
      : _ctx(ctx), _module(module) {}

   llvm::Function *TranslateFunction(AST::Expression *expr);

private:
   llvm::LLVMContext &_ctx;
   llvm::Module *_module;
};

}
