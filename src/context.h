#ifndef CONTEXT_H
#define CONTEXT_H

#include "symbol.h"

#include <vector>
#include <set>

struct ImpactContext {
    std::vector<Symbol> symbols;
    std::set<Symbol> modifiedSymbols;
};

#endif