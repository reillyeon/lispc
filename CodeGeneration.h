#include "llvm/Support/IRBuilder.h"
#include "llvm/Support/StringPool.h"

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
   Context(llvm::LLVMContext &ctx,
           llvm::StringPool &stringPool);

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
                 llvm::Module *module,
                 llvm::StringPool &stringPool)
      : _ctx(ctx), _module(module), _stringPool(stringPool) {}

   llvm::Function *TranslateFunction(AST::Expression *expr);

private:
   llvm::LLVMContext &_ctx;
   llvm::Module *_module;
   llvm::StringPool &_stringPool;
};

}
