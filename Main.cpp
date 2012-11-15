#include "CodeGeneration.h"
#include "Parser.h"

#include <iostream>

#include "llvm/ADT/OwningPtr.h"
#include "llvm/LLVMContext.h"
#include "llvm/Module.h"
#include "llvm/Support/system_error.h"
#include "llvm/Support/MemoryBuffer.h"
#include "llvm/Support/StringPool.h"

using namespace std;
using namespace llvm;

int
main(int argc, char **argv)
{
   OwningPtr<MemoryBuffer> input;
   error_code err = MemoryBuffer::getFile(argv[1], input);

   LLVMContext &ctx = getGlobalContext();
   StringPool stringPool;

   AST::Expression *expr = AST::Parse(*input.get(), stringPool);

   cout << expr->ToString() << endl;

   Module *module = new Module("the module", ctx);

   CodeGeneration::CodeGenerator codeGen(ctx, module, stringPool);

   codeGen.TranslateFunction(expr);

   module->dump();

   delete expr;

   return err.value();
}
