#include "AST.h"
#include "CodeGeneration.h"

#include <sstream>

namespace AST {

std::string
Constant::ToString() const
{
   std::stringstream str;

   str << _value;

   return str.str();
}

llvm::Value *
Constant::Translate(CodeGeneration::Context &ctx) const
{
   return llvm::ConstantInt::get(ctx.GetContext(),
                                 llvm::APInt(64, _value, true));
}

}
