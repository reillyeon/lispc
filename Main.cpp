#include "AST.h"
#include "CodeGeneration.h"
#include "Lexer.h"
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

   Lexer::Tokenizer tokenizer(*input.get());
   Parser::Parser parser(tokenizer);
   AST::Expression *expr = parser.NextExpression();

   cout << expr->ToString() << endl;

   Module *module = new Module("the module", ctx);

   CodeGeneration::CodeGenerator codeGen(ctx, module);

   codeGen.TranslateFunction(expr);

   module->dump();

   delete expr;

   return err.value();
}
