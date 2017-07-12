#ifndef COMPILER_BUILD_TABLES_PARSE_ITEM_SET_BUILDER_H_
#define COMPILER_BUILD_TABLES_PARSE_ITEM_SET_BUILDER_H_

#include "compiler/build_tables/parse_item.h"
#include "compiler/rule.h"
#include <map>
#include <vector>

namespace tree_sitter {

struct SyntaxGrammar;
struct LexicalGrammar;

namespace build_tables {

class ParseItemSetBuilder {
  struct ParseItemSetComponent {
    ParseItem item;
    LookaheadSet lookaheads;
    bool propagates_lookaheads;

    inline bool operator==(const ParseItemSetComponent &other) {
      return item == other.item &&
        lookaheads == other.lookaheads &&
        propagates_lookaheads == other.propagates_lookaheads;
    }
  };

  const SyntaxGrammar &grammar;
  std::map<rules::Symbol, LookaheadSet> first_sets;
  std::map<rules::Symbol, LookaheadSet> last_sets;
  std::map<rules::Symbol::Index, std::vector<ParseItemSetComponent>> component_cache;
  std::map<ParseItem, std::vector<Production>> inlined_productions_by_original_production;

 public:
  ParseItemSetBuilder(const SyntaxGrammar &, const LexicalGrammar &);
  void apply_transitive_closure(ParseItemSet *);
  LookaheadSet get_first_set(const rules::Symbol &) const;
  LookaheadSet get_last_set(const rules::Symbol &) const;
};

}  // namespace build_tables
}  // namespace tree_sitter

#endif  // COMPILER_BUILD_TABLES_PARSE_ITEM_SET_BUILDER_H_
