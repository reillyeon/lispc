#include "Parser.h"

#include <iostream>

#include "llvm/ADT/OwningPtr.h"
#include "llvm/Support/system_error.h"
#include "llvm/Support/MemoryBuffer.h"
#include "llvm/Support/StringPool.h"

using namespace std;
using namespace llvm;

int
main(int argv, char **argc)
{
   StringRef str = "(+ (+ 1 1))";
   MemoryBuffer *input = MemoryBuffer::getMemBuffer(str, "buffer");
   StringPool stringPool;

   AST::Expression *expr = AST::Parse(input, &stringPool);

   cout << expr->ToString() << endl;

   delete expr;
   delete input;

   return 0;
}
