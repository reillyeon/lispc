#include "Parser.h"

#include <iostream>

#include "llvm/ADT/OwningPtr.h"
#include "llvm/Support/system_error.h"
#include "llvm/Support/MemoryBuffer.h"

using namespace std;
using namespace llvm;

int
main(int argv, char **argc)
{
   StringRef str = "(+ (+ 1 1))";
   MemoryBuffer *input = MemoryBuffer::getMemBuffer(str, "buffer");

   AST::Expression *expr = AST::Parse(input);

   cout << expr->ToString() << endl;

   delete expr;
   delete input;

   return 0;
}
