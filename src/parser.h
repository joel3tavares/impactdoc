#ifndef PARSER_H
#define PARSER_H

#include "args.h"
#include "context.h"
#include "symbol.h"

#include <fstream>
#include <stack>
#include <vector>
#include <unordered_set> 

struct ImpactParser
{
    private:
        Args args;

        std::ifstream in;

        unsigned int lineCount;
        unsigned int braceCount;

        std::stack<Symbol> scopeStack;
        std::vector<std::string> scopeComments;

        ImpactContext context;

        void incrementLineCount();
        void incrementBraceCount();
        void decrementBraceCount();
        void parseToken(const std::string &token);
        void populateSymbolTable();
        void ignoreLine();
        void parseDocComments();
        void parseFunction();
        void parseClass();
        void parseScope(const std::unordered_set<char>& endChars);

    public:
        ImpactParser(const Args &args);
        ~ImpactParser();
        ImpactContext parse();
        
};

#endif