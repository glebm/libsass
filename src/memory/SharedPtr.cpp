#include "../memory/SharedPtr.hpp"
#include "SharedPtr.hpp"

#ifdef DEBUG_SHARED_PTR
#include <iostream>
#include <typeinfo>
#include "../sass.hpp"
#include "../ast_fwd_decl.hpp"
#include "../debugger.hpp"
#endif

namespace Sass {

  #ifdef DEBUG_SHARED_PTR
  void SharedObj::dumpMemLeaks() {
    if (!all.empty()) {
      std::cerr << "###################################\n";
      std::cerr << "# REPORTING MISSING DEALLOCATIONS #\n";
      std::cerr << "###################################\n";
      for (SharedObj* var : all) {
        if (AST_Node_Ptr ast = dynamic_cast<AST_Node*>(var)) {
          debug_ast(ast);
        } else {
          std::cerr << "LEAKED " << var << "\n";
        }
      }
    }
  }
  std::vector<SharedObj*> SharedObj::all;
  #endif

  bool SharedObj::taint = false;
}
