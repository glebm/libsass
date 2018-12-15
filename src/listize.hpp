#ifndef SASS_LISTIZE_H
#define SASS_LISTIZE_H

#include <iostream>
#include <vector>

#include "ast.hpp"
#include "ast_fwd_decl.hpp"
#include "context.hpp"
#include "environment.hpp"
#include "operation.hpp"

namespace Sass {

  struct Backtrace;

  class Listize : public Operation_CRTP<Expression_Ptr, Listize> {

  public:
    Listize();
    ~Listize() { }

    Expression_Ptr operator()(Selector_List_Ptr);
    Expression_Ptr operator()(Complex_Selector_Ptr);
    Expression_Ptr operator()(Compound_Selector_Ptr);

    // generic fallback
    template <typename U>
    Expression_Ptr fallback(U x)
    { return Cast<Expression>(x); }
  };

}

#endif
