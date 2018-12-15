#ifndef SASS_BIND_H
#define SASS_BIND_H

#include <string>

#include "ast_fwd_decl.hpp"
#include "backtrace.hpp"
#include "environment.hpp"

namespace Sass {

class Eval;

  void bind(std::string type, std::string name, Parameters_Obj, Arguments_Obj, Env*, Eval*, Backtraces& traces);

}

#endif
