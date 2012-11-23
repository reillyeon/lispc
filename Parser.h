#include "llvm/Support/StringPool.h"

namespace llvm {
   class MemoryBuffer;
}

namespace AST {
   class Expression;
}

namespace Parser {

AST::Expression *Parse(const llvm::MemoryBuffer &input,
                       llvm::StringPool &stringPool);

}
