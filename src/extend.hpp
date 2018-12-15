#ifndef SASS_EXTEND_H
#define SASS_EXTEND_H

#include <set>
#include <string>
#include <unordered_map>

#include "ast.hpp"
#include "ast_fwd_decl.hpp"
#include "ast_selectors.hpp"
#include "eval.hpp"
#include "node.hpp"
#include "operation.hpp"
#include "subset_map.hpp"

namespace Sass {

class Eval;
class Subset_Map;

  Node subweave(Node& one, Node& two);

  class Extend : public Operation_CRTP<void, Extend> {

    Subset_Map& subset_map;
    Eval* eval;

  private:

    std::unordered_map<
      Selector_List_Obj, // key
      Selector_List_Obj, // value
      HashNodes, // hasher
      CompareNodes // compare
    > memoizeList;

    std::unordered_map<
      Complex_Selector_Obj, // key
      Node, // value
      HashNodes, // hasher
      CompareNodes // compare
    > memoizeComplex;

    /* this turned out to be too much overhead
       re-evaluate once we store an ast selector
    std::unordered_map<
      Compound_Selector_Obj, // key
      Node, // value
      HashNodes, // hasher
      CompareNodes // compare
    > memoizeCompound;
    */

    void extendObjectWithSelectorAndBlock(Ruleset_Ptr pObject);
    Node extendComplexSelector(Complex_Selector_Ptr sel, CompoundSelectorSet& seen, bool isReplace, bool isOriginal);
    Node extendCompoundSelector(Compound_Selector_Ptr sel, CompoundSelectorSet& seen, bool isReplace);
    bool complexSelectorHasExtension(Complex_Selector_Ptr selector, CompoundSelectorSet& seen);
    Node trim(Node& seqses, bool isReplace);
    Node weave(Node& path);

  public:
    void setEval(Eval& eval);
    Selector_List_Ptr extendSelectorList(Selector_List_Obj pSelectorList, bool isReplace, bool& extendedSomething, CompoundSelectorSet& seen);
    Selector_List_Ptr extendSelectorList(Selector_List_Obj pSelectorList, bool isReplace = false) {
      bool extendedSomething = false;
      CompoundSelectorSet seen;
      return extendSelectorList(pSelectorList, isReplace, extendedSomething, seen);
    }
    Selector_List_Ptr extendSelectorList(Selector_List_Obj pSelectorList, CompoundSelectorSet& seen) {
      bool isReplace = false;
      bool extendedSomething = false;
      return extendSelectorList(pSelectorList, isReplace, extendedSomething, seen);
    }
    Extend(Subset_Map&);
    ~Extend() { }

    void operator()(Block_Ptr);
    void operator()(Ruleset_Ptr);
    void operator()(Supports_Block_Ptr);
    void operator()(Media_Block_Ptr);
    void operator()(Directive_Ptr);

    // ignore missed types
    template <typename U>
    void fallback(U x) {}

  };

}

#endif
