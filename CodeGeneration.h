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

class CodeGenerator {
public:
   CodeGenerator(llvm::LLVMContext &ctx,
                 llvm::Module *module,
                 llvm::StringPool &stringPool);

   llvm::Function *TranslateFunction(AST::Expression *expr);
   llvm::Value *TranslateExpression(AST::Expression *expr);

private:
   llvm::LLVMContext &_ctx;
   llvm::Module *_module;
   llvm::IRBuilder<> _builder;

   llvm::PooledStringPtr _opAdd;
   llvm::PooledStringPtr _opSub;
   llvm::PooledStringPtr _opMult;
};

}
