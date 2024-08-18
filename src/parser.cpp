#include "parser.h"

#include <iostream>
#include <string>
#include <stdexcept>

ImpactParser::ImpactParser(const Args &args) : args(args)
{
    lineCount = 1;
    braceCount = 0;

    in.open(args.getFileName());

    if (!in) {
        throw std::runtime_error("File does not exist or cannot be opened: " + args.getFileName());
    }
}

ImpactParser::~ImpactParser()
{
    in.close();
}

ImpactContext ImpactParser::parse()
{
    in.seekg(0, in.beg);

    char ch;
    std::string token = "";

    while (in.get(ch)) {
        switch (ch) {
            case '\n':
                incrementLineCount();
            case ' ':
            case '\t':
                parseToken(token);
                token.clear();
            break;
            case '{':
                incrementBraceCount();
            break;
            case '}':
                populateSymbolTable();
            break;
            default:
                token += ch;
        }
    }

    return context;
}

void ImpactParser::incrementLineCount()
{
    lineCount++;
}

void ImpactParser::incrementBraceCount()
{
    braceCount++;
}

void ImpactParser::decrementBraceCount()
{
    braceCount--;
}

void ImpactParser::parseToken(const std::string &token)
{
    if (token.empty()) {
        return;
    }
 
    if ("class" == token) {
        parseClass();
    } else if ("function" == token) {
        parseFunction();
    } else if (token.starts_with("/*")) {
        parseDocComments();
    } else if (token.starts_with("//")) { 
        ignoreLine();
    }
}

void ImpactParser::populateSymbolTable()
{ 
    if (
        !scopeStack.empty()
        && scopeStack.size() == braceCount
    ) {
        scopeStack.top().endLine = lineCount;
        context.symbols.push_back(scopeStack.top());
    
        for (auto line : args.getLines()) {
            if (line >= scopeStack.top().startLine && line <= scopeStack.top().endLine) {
                context.modifiedSymbols.insert(scopeStack.top());
            }
        }
    
        scopeStack.pop();
    }

    decrementBraceCount();
}

void ImpactParser::ignoreLine()
{
    char ch;
    std::string line = "";

    while (in.get(ch)) {
        if (ch == '\n') {
            incrementLineCount();
            break;
        }
    }
}

void ImpactParser::parseDocComments()
{
    char ch;
    std::string token = "";

    while (in.get(ch)) {
        if (ch == ' ' || ch == '\n') {
            if (ch == '\n')
                incrementLineCount();

            if (token.ends_with("*/"))
                break;

            if (token == "@impact") {
                std::string description = "";

                while (in.get(ch)) {
                    if (ch == '\n') {
                        incrementLineCount();
                        break;
                    }

                    description += ch;
                }

                scopeComments.push_back(description);
            
                if (description.ends_with("*/"))
                    break;
            }
            
            token.clear();
        } else {
            token += ch;
        }
    }
}

void ImpactParser::parseFunction()
{
    static const std::unordered_set<char> endChars = {'{', '('};
    parseScope(endChars);
}

void ImpactParser::parseClass()
{
    static const std::unordered_set<char> endChars = {'{'};
    parseScope(endChars);
}

void ImpactParser::parseScope(const std::unordered_set<char>& endChars)
{
    char ch;
    std::string token = "";
    int startLine = lineCount;

    while (in.get(ch)) {
        if (ch == '\n')
            incrementLineCount();
        
        if (endChars.find(ch) != endChars.end())
            break;

        if (!token.empty() && (ch == ' ' || ch == '\n')) {
            break;
        }

        token += ch;
    }

    while (ch != '{' && in.get(ch)) {
        if (ch == '\n')
            incrementLineCount();
    }

    incrementBraceCount();

    scopeStack.push(Symbol(token, startLine, scopeComments));
    scopeComments.clear();

}