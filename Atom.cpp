#include "AST.h"

namespace AST {

std::string
Atom::ToString() const
{
   return *_value;
}

llvm::Value *
Atom::Translate(CodeGeneration::Context &ctx) const
{
   return NULL;
}

};
