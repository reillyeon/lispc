#include "llvm/Support/IRBuilder.h"
#include "llvm/Support/StringPool.h"

namespace llvm {
   class Value;
}

namespace AST {
   class Expression;
}

namespace CodeGeneration {

class CodeGenerator {
public:
   CodeGenerator(llvm::LLVMContext &ctx,
                 llvm::StringPool &stringPool);

   llvm::Value *TranslateExpression(AST::Expression *expr);

private:
   llvm::LLVMContext &_ctx;
   llvm::IRBuilder<> _builder;

   llvm::PooledStringPtr _opAdd;
   llvm::PooledStringPtr _opSub;
   llvm::PooledStringPtr _opMult;
};

}
