#include "AST.h"

namespace AST {

std::string
Variable::ToString() const
{
   return *_name;
}

llvm::Value *
Variable::Translate(CodeGeneration::Context &ctx) const
{
   return NULL;
}

}
